#include "engineph.h"
#include "Model.h"

namespace Kuro
{
	Model::Model(std::string path)
	{
		LoadModel(path);
	}

	Model::~Model()
	{
		delete mesh;
	}

	void Model::LoadModel(std::string path)
	{
		KURO_CORE_TRACE("Model::LoadModel");
		KURO_CORE_TRACE(path);
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_PreTransformVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			KURO_CORE_ERROR("EROR::ASSIMP:: {}", import.GetErrorString());
			KURO_CORE_ASSERT(false, "");
		}

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		KURO_CORE_TRACE("Model::ProcessNode");

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(aimesh, scene);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		KURO_CORE_TRACE("Model::ProcessMesh");
		std::vector<VertexData> vertices;
		std::vector<unsigned int> indices;		

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			VertexData vertex;
			glm::vec3 vector;

			// Positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			// Normals
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}

			// Texture Coordinate
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;

				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;

				// Tangent
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.Tangent = vector;

				// Bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vector;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		this->mesh = new Mesh(vertices, indices);
	}
}

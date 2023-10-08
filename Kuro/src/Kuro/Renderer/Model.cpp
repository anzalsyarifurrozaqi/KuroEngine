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
		Assimp::Importer import;
		//const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_PreTransformVertices);

		//if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		//{
		//	KURO_CORE_ERROR("EROR::ASSIMP:: {}", import.GetErrorString());
		//	KURO_CORE_ASSERT(false, "");
		//}

		//ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		KURO_CORE_TRACE("Model::ProcessNode");
	}

	void Model::ProcessMesh(aiNode* mesh, const aiScene* scene)
	{
		KURO_CORE_TRACE("Model::ProcessMesh");
	}
}

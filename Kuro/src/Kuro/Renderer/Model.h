#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Kuro
{
	class Model
	{
	public:
		Model(std::string path);
		~Model();

		Mesh* GetMesh() { return mesh; }

	private:
		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		Mesh* mesh;
	};
}


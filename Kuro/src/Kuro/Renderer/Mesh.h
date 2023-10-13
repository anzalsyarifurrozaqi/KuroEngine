#pragma once

namespace Kuro
{
	typedef struct VertexData
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;

	};
	class Mesh
	{
	public:

		Mesh(std::vector<VertexData> vetices, std::vector<uint32_t> indices);
		
		std::vector<VertexData> GetVertices() { return vertices; }
		std::vector<uint32_t> GetIndices() { return indices; }

	private:
		std::vector<VertexData> vertices;
		std::vector<uint32_t> indices;
	};
}


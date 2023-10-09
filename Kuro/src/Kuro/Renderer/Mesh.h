#pragma once

namespace Kuro
{
	typedef struct Vertex
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

		Mesh(std::vector<Vertex> vetices, std::vector<uint32_t> indices);
		
		std::vector<Vertex> GetVertices() { return vertices; }
		std::vector<uint32_t> GetIndices() { return indices; }

	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}


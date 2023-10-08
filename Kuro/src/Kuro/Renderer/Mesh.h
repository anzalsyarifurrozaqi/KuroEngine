#pragma once

namespace Kuro
{
	typedef struct Vertex
	{
		glm::vec3 Position;

	};
	class Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		Mesh(std::vector<Vertex> vetices, std::vector<unsigned int> indices);
	};
}


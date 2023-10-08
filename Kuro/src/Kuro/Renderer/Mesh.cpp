#include "engineph.h"
#include "Mesh.h"

namespace Kuro
{
	Mesh::Mesh(std::vector<Vertex> vetices, std::vector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}
}

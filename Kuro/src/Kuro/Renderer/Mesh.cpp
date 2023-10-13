#include "engineph.h"
#include "Mesh.h"

namespace Kuro
{
	Mesh::Mesh(std::vector<VertexData> vertices, std::vector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}
}

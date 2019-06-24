#include "Render.h"
#include "..\Geometry\BaseGeometry.h"
#include "..\Math\Vertex.h"

void DrawCall(BaseGeometry * mesh)
{
	Vertex *vOut = new Vertex[mesh->vertexCount];

	for (int i = 0; i < mesh->vertexCount; ++i)
	{
		vOut = VertexShader[mesh->vertices[i]];
	}
}

Vertex VertexShader(Vertex v)
{
	Vertex out;
}
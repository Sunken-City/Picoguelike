#include "Engine/Renderer/Vertex.hpp"

void Vertex_PCUTB::Copy(const Vertex_Master& source, byte* destination)
{
	Vertex_PCUTB* pctub = (Vertex_PCUTB*)(destination);
	pctub->pos = source.position;
	pctub->color = source.color;
	pctub->texCoords = source.uv0;
	pctub->tangent = source.tangent;
	pctub->bitangent = source.bitangent;
}

void Vertex_PCT::Copy(const Vertex_Master& source, byte* destination)
{
	Vertex_PCT* pct = (Vertex_PCT*)(destination);
	pct->pos = source.position;
	pct->color = source.color;
	pct->texCoords = source.uv0;
}

#pragma once

#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "MarchingCubesLookUpTable.h"
#include <algorithm>



class MarchingCubesIso
{
public:
	template<class V>
	static IndexedTriangleList<V> Make(bool func(float x, float y, float z), float sizex, float sizey, float sizez, float tes)
	{

		std::vector<unsigned short> indices;
		std::vector<DirectX::XMFLOAT3> vertices;
		int offset = 0;

		for (float xi = -sizex; xi < sizex; xi+= 2*tes)
		{
			for (float yi = -sizex; yi < sizey; yi+=2*tes)
			{
				for (float zi = -sizex; zi < sizez; zi+=2*tes)
				{

					DirectX::XMFLOAT3 edgesToVertices[77];
					edgesToVertices[01] = { xi,yi - tes,zi - tes };
					edgesToVertices[10] = { xi,yi - tes,zi - tes };
					edgesToVertices[02] = { xi - tes,yi - tes, zi };
					edgesToVertices[20] = { xi - tes,yi - tes, zi };
					edgesToVertices[13] = { xi + tes,yi - tes,zi };
					edgesToVertices[31] = { xi + tes,yi - tes,zi };
					edgesToVertices[32] = { xi,yi - tes,zi + tes };
					edgesToVertices[23] = { xi,yi - tes,zi + tes };

					edgesToVertices[15] = { xi + tes,yi,zi - tes };
					edgesToVertices[51] = { xi + tes,yi,zi - tes };
					edgesToVertices[37] = { xi + tes ,yi,zi + tes };
					edgesToVertices[73] = { xi + tes ,yi,zi + tes };
					edgesToVertices[26] = { xi - tes ,yi, zi + tes };
					edgesToVertices[62] = { xi - tes ,yi, zi + tes };
					edgesToVertices[04] = { xi - tes ,yi, zi - tes };
					edgesToVertices[40] = { xi - tes ,yi, zi - tes };

					edgesToVertices[45] = { xi ,yi +tes, zi - tes };
					edgesToVertices[54] = { xi ,yi + tes, zi - tes };
					edgesToVertices[57] = { xi + tes , yi + tes, zi };
					edgesToVertices[75] = { xi + tes , yi + tes, zi };
					edgesToVertices[67] = { xi,yi + tes, zi + tes };
					edgesToVertices[76] = { xi,yi + tes, zi + tes };
					edgesToVertices[46] = { xi - tes ,yi + tes, zi};
					edgesToVertices[64] = { xi - tes ,yi + tes, zi };

					int cubeIndex = 0;

					cubeIndex |= func(xi - tes, yi - tes, zi - tes) << 0;
					cubeIndex |= func(xi + tes, yi - tes, zi - tes) << 1;
					cubeIndex |= func(xi - tes, yi - tes, zi + tes) << 2;
					cubeIndex |= func(xi + tes, yi - tes, zi + tes) << 3;
					cubeIndex |= func(xi - tes, yi + tes, zi - tes) << 4;
					cubeIndex |= func(xi + tes, yi + tes, zi - tes) << 5;
					cubeIndex |= func(xi - tes, yi + tes, zi + tes) << 6;
					cubeIndex |= func(xi + tes, yi + tes, zi + tes) << 7;

					//add vertices to vertex list	
					for (int i = 0; i < regularCellData[regularCellClass[cubeIndex]].GetVertexCount(); i++)
					{
						unsigned short edgedata = regularVertexData[cubeIndex][i];
						unsigned short twoEdges = edgedata & 0xFF;
						int edge1 = twoEdges / 16;
						int edge2 = twoEdges % 16;

						vertices.push_back(edgesToVertices[edge1 * 10 + edge2]);
					}

					//add indices to index list
					RegularCellData cell = regularCellData[regularCellClass[cubeIndex]];
					std::vector<unsigned short> cellIndices;
					std::transform(cell.vertexIndex, cell.vertexIndex + cell.GetTriangleCount() * 3, std::back_inserter(cellIndices), [&offset](int value) {return value + offset;});

					indices.insert(indices.end(), cellIndices.begin(), cellIndices.end());
					offset += cell.GetVertexCount();


				}
			}
		}

		std::vector<V> verts(vertices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verts[i].pos = vertices[i];
		}

		return{ std::move(verts),indices };

	}
};
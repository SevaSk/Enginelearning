#pragma once

#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "MarchingCubesLookUpTable.h"
#include <algorithm>

class MarchingCubesIso
{
public:
	template<class V>
	static IndexedTriangleList<V> Make(float func(float x, float y, float z), float sizex, float sizey, float sizez, float tes)
	{

		std::vector<unsigned short> indices;
		std::vector<DirectX::XMFLOAT3> vertices;
		int offset = 0;

		for (float xi = -sizex; xi < sizex; xi += 2 * tes)
		{
			for (float yi = -sizex; yi < sizey; yi += 2 * tes)
			{
				for (float zi = -sizex; zi < sizez; zi += 2 * tes)
				{
					cubeVertData cubeData[8];
					int cubeIndex = 0;

					cubeData[0].x = xi - tes;
					cubeData[0].y = yi - tes;
					cubeData[0].z = zi - tes;
					cubeData[0].value = func(xi - tes, yi - tes, zi - tes);
					cubeIndex |= (cubeData[0].value < 1.0f) << 0;

					cubeData[1].x = xi + tes;
					cubeData[1].y = yi - tes;
					cubeData[1].z = zi - tes;
					cubeData[1].value = func(xi + tes, yi - tes, zi - tes);
					cubeIndex |= (cubeData[1].value < 1.0f) << 1;

					cubeData[2].x = xi - tes;
					cubeData[2].y = yi - tes;
					cubeData[2].z = zi + tes;
					cubeData[2].value = func(xi - tes, yi - tes, zi + tes);
					cubeIndex |= (cubeData[2].value < 1.0f) << 2;

					cubeData[3].x = xi + tes;
					cubeData[3].y = yi - tes;
					cubeData[3].z = zi + tes;
					cubeData[3].value = func(xi + tes, yi - tes, zi + tes);
					cubeIndex |= (cubeData[3].value < 1.0f) << 3;

					cubeData[4].x = xi - tes;
					cubeData[4].y = yi + tes;
					cubeData[4].z = zi - tes;
					cubeData[4].value = func(xi - tes, yi + tes, zi - tes);
					cubeIndex |= (cubeData[4].value < 1.0f) << 4;

					cubeData[5].x = xi + tes;
					cubeData[5].y = yi + tes;
					cubeData[5].z = zi - tes;
					cubeData[5].value = func(xi + tes, yi + tes, zi - tes);
					cubeIndex |= (cubeData[5].value < 1.0f) << 5;

					cubeData[6].x = xi - tes;
					cubeData[6].y = yi + tes;
					cubeData[6].z = zi + tes;
					cubeData[6].value = func(xi - tes, yi + tes, zi + tes);
					cubeIndex |= (cubeData[6].value < 1.0f) << 6;

					cubeData[7].x = xi + tes;
					cubeData[7].y = yi + tes;
					cubeData[7].z = zi + tes;
					cubeData[7].value = func(xi + tes, yi + tes, zi + tes);
					cubeIndex |= (cubeData[7].value < 1.0f) << 7;

					//add vertices to vertex list	
					for (int i = 0; i < regularCellData[regularCellClass[cubeIndex]].GetVertexCount(); i++)
					{
						unsigned short edgedata = regularVertexData[cubeIndex][i];
						unsigned short twoverts = edgedata & 0xFF;
						switch (twoverts)
						{
						case 0x01:
						{
							float inter = (cubeData[0].value + cubeData[1].value)*0.5f;
							vertices.emplace_back(cubeData[0].x + inter*tes, cubeData[0].y, cubeData[0].z);
							break;
						}
						case 0x02:
						{
							float inter = (cubeData[0].value + cubeData[2].value)*0.5f;
							vertices.emplace_back(cubeData[0].x, cubeData[0].y, cubeData[0].z + inter*tes);
							break;
						}
						case 0x13:
						{
							float inter = (cubeData[1].value + cubeData[3].value)*0.5f;
							vertices.emplace_back(cubeData[1].x, cubeData[1].y, cubeData[1].z + inter*tes);
							break;
						}
						case 0x23:
						{
							float inter = (cubeData[2].value + cubeData[3].value)*0.5f;
							vertices.emplace_back(cubeData[2].x + inter*tes, cubeData[2].y, cubeData[2].z);
							break; 
						}
						case 0x15:
						{
							float inter = (cubeData[1].value + cubeData[5].value)*0.5f;
							vertices.emplace_back(cubeData[1].x, cubeData[1].y + inter*tes, cubeData[1].z);
							break; 
						}
						case 0x37:
						{
							float inter = (cubeData[3].value + cubeData[7].value)*0.5f;
							vertices.emplace_back(cubeData[3].x, cubeData[3].y + inter*tes, cubeData[3].z);
							break; 
						}
						case 0x26:
						{
							float inter = (cubeData[2].value + cubeData[6].value)*0.5f;
							vertices.emplace_back(cubeData[2].x, cubeData[2].y + inter*tes, cubeData[2].z);
							break;
						}
						case 0x04:
						{

							float inter = (cubeData[0].value + cubeData[4].value)*0.5f;
							vertices.emplace_back(cubeData[0].x, cubeData[0].y + inter*tes, cubeData[0].z);
							break;
						}
						case 0x45:
						{
							float inter = (cubeData[4].value + cubeData[5].value)*0.5f;
							vertices.emplace_back(cubeData[4].x + inter*tes ,cubeData[4].y, cubeData[4].z );
							break;
						}
						case 0x57:
						{
							float inter = (cubeData[5].value + cubeData[7].value)*0.5f;
							vertices.emplace_back(cubeData[5].x,cubeData[5].y, cubeData[5].z + inter*tes);
							break;
						}
						case 0x67:
						{
							float inter = (cubeData[6].value + cubeData[7].value)*0.5f;
							vertices.emplace_back(cubeData[6].x + inter * tes, cubeData[6].y, cubeData[6].z);
							break;
						}
						case 0x46:
						{
							float inter = (cubeData[4].value + cubeData[6].value)*0.5f;
							vertices.emplace_back(cubeData[4].x, cubeData[4].y, cubeData[4].z + inter * tes);
							break;
						}
						default:
							break;
						}
					}

					//add indices to index list
					RegularCellData cell = regularCellData[regularCellClass[cubeIndex]];
					std::vector<unsigned short> cellIndices;
					std::transform(cell.vertexIndex, cell.vertexIndex + cell.GetTriangleCount() * 3, std::back_inserter(cellIndices), [&offset](int value) {return value + offset; });

					indices.insert(indices.end(), cellIndices.begin(), cellIndices.end());
					offset += cell.GetVertexCount();
				}
			}
		}

		std::vector<V> verts(vertices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verts[i].pos = vertices[i];
			verts[i].n = DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f };
		}
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			DirectX::XMVECTOR v1 = DirectX::XMLoadFloat3(&vertices[indices[i]]);
			DirectX::XMVECTOR v2 = DirectX::XMLoadFloat3(&vertices[indices[i + 1]]);
			DirectX::XMVECTOR v3 = DirectX::XMLoadFloat3(&vertices[indices[i + 2]]);

			DirectX::XMVECTOR normal = DirectX::XMVector3Normalize(
				DirectX::XMVector3Cross(
				DirectX::XMVectorSubtract(v2, v1), DirectX::XMVectorSubtract(v3, v1)));
			for (size_t j = 0; j < 3; j++)
			{
				DirectX::XMFLOAT3 n;
				DirectX::XMVECTOR currentn = DirectX::XMLoadFloat3(&(verts[indices[i+j]].n));
				DirectX::XMVECTOR newn = DirectX::XMVector3Normalize(DirectX::XMVectorAdd(normal, currentn));
				DirectX::XMStoreFloat3(&n, newn);
				verts[indices[i+j]].n = n;
			}
		}

		return{ std::move(verts),indices };

	}
	private:
		struct cubeVertData
		{
			float value;
			float x;
			float y;
			float z;
		};
};
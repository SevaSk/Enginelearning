#pragma once

#include "IndexedTriangleList.h"
#include <DirectXMath.h>

class Mandlebulb
{
private:
	static bool conv(DirectX::XMFLOAT3 vect);
public:
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		constexpr float side = 2.0f;
		std::vector<DirectX::XMFLOAT3> vertices;
		for (float x = -2; x < 2; x+= side)
		{
			for (float y = -2; y < 2; y+= side)
			{
				for (float z = -2; z < 2; z+= side)
				{
					if (true)
					{

						vertices.emplace_back( x-side, y-side, z-side); // 0
						vertices.emplace_back( x+side, y-side, z-side); // 1
						vertices.emplace_back( x-side, y+side, z-side); // 2
						vertices.emplace_back( x+side, y+side, z-side); // 3
						vertices.emplace_back( x-side, y-side, z+side); // 4
						vertices.emplace_back( x+side, y-side, z+side); // 5
						vertices.emplace_back( x-side, y+side, z+side); // 6
						vertices.emplace_back( x+side, y+side, z+side); // 7
					}												 
				}
			}
		}

		std::vector<V> verts(vertices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verts[i].pos = vertices[i];
			verts[i].color = { i * 17 % 255, i * 19 % 255, i * 7 % 255 };
		}
		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < verts.size(); i += 8)
		{
			unsigned short arr[36] = {  0 + i, 2 + i, 1 + i, 2 + i, 3 + i, 1 + i,
					1 + i, 3 + i, 5 + i, 3 + i, 7 + i, 5 + i,
					2 + i, 6 + i, 3 + i, 3 + i, 6 + i, 7 + i,
					4 + i, 5 + i, 7 + i, 4 + i, 7 + i, 6 + i,
					0 + i, 4 + i, 2 + i, 2 + i, 4 + i, 6 + i,
					0 + i, 1 + i, 4 + i, 1 + i, 5 + i, 4 + i };
			indices.insert(indices.end(), arr,std::end(arr));
		}

		return { std::move(verts), indices };
	}

};

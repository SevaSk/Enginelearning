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
		constexpr float side = 0.03f;
		std::vector<DirectX::XMFLOAT3> vertices;
		for (float x = -5; x < 5; x+= 2*side)
		{
			for (float y = -5; y < 5; y+= 2*side)
			{
				for (float z = -5; z < 5; z+= 2*side)
				{
					if (conv({x,y,z}))
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
			if (i % 4 == 0)
			{
				verts[i].n = { 0.0f,-1.0f,0.0f };
			}
			else if (i % 4 == 1)
			{
				verts[i].n = { 1.0f,0.0f,0.0f };
			}
			else if (i % 4 == 2)
			{
				verts[i].n = { 0.0f,1.0f,0.0f };
			}
			else if (i % 4 == 3)
			{
				verts[i].n = { 0.0f,0.0f,-1.0f };
			}
		}
		std::vector<unsigned short> indices;
		for (unsigned short i = 0; i < verts.size(); i += 8)
		{
			unsigned short arr[36] = {  0u + i, 2u + i, 1u + i, 2u + i, 3u + i, 1u + i,
					1u + i, 3u + i, 5u + i, 3u + i, 7u + i, 5u + i,
					2u + i, 6u + i, 3u + i, 3u + i, 6u + i, 7u + i,
					4u + i, 5u + i, 7u + i, 4u + i, 7u + i, 6u + i,
					0u + i, 4u + i, 2u + i, 2u + i, 4u + i, 6u + i,
					0u + i, 1u + i, 4u + i, 1u + i, 5u + i, 4u + i };
			indices.insert(indices.end(), arr,std::end(arr));
		}

		return { std::move(verts), indices };
	}

};

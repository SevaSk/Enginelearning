#pragma once
#include "IndexedTriangleList.h"
#include <DirectXMath.h>

class Plane
{
public:
	template<class V>
	static IndexedTriangleList<V> MakeTesselated(int divisions_x,int divisions_y)
	{
		namespace dx = DirectX;
		assert(divisions_x >= 1);
		assert(divisions_y >= 1);

		const float height = 2.0f;
		const float width = 2.0f;

		dx::XMFLOAT3 bottomleft { -1.0f,-1.0f,0.0f };

		std::vector<dx::XMFLOAT3> vertices;
		for (auto y = 0; y <= divisions_y; y++)
		{
			for (auto x = 0; x <= divisions_x; x++)
			{
				vertices.emplace_back(
					bottomleft.x + ((float)x * (width / (float)divisions_x)),
					bottomleft.y + ((float)y * (height / (float)divisions_y)),
					0.0f);
			}
		}

		std::vector<V> verts(vertices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verts[i].pos = vertices[i];
		}


		std::vector<unsigned short> indices;

		for (auto  y = 0; y < divisions_y; y++)
		{
			for (auto x = 0; x < divisions_x; x++) 
			{
				indices.push_back(x + (y*(divisions_x + 1)));
				indices.push_back(x + ((y + 1) * (divisions_x + 1)));
				indices.push_back(x + 1 + (y * (divisions_x + 1)));
				indices.push_back(x + 1 + (y * (divisions_x + 1)));
				indices.push_back(x + ((y + 1) * (divisions_x + 1)));
				indices.push_back(x + 1 + ((y + 1) * (divisions_x + 1)));
			}
		}
		return{ std::move(verts),indices };
	}
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		return  MakeTesselated<V>(1, 1);
	}
};




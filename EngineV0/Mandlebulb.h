#pragma once

#include "TriangleStrip.h"
#include <DirectXMath.h>

class Mandlebulb
{
private:
	static bool conv(DirectX::XMFLOAT3 vect);
public:
	template<class V>
	static TriangleStrip<V> Make()
	{
		std::vector<DirectX::XMFLOAT3> vertices;
		for (float x = -2; x < 2; x+= 0.1f)
		{
			for (float y = -2; y < 2; y+= 0.1f)
			{
				for (float z = -2; z < 2; z+= 0.1f)
				{
					if (conv(DirectX::XMFLOAT3{x,y,z}))
					{
						vertices.emplace_back(x,y,z);
					}
				}
			}
		}
		std::vector<V> verts(vertices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verts[i].pos = vertices[i];
		}

		return {std::move(verts)};
	}

};

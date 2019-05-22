#pragma once
#include <vector>
#include <DirectXMath.h>

template<class T>
class TriangleStrip
{
public:
	TriangleStrip() = default;
	TriangleStrip(std::vector<T> verts_in)
		:
		vertices(std::move(verts_in))
	{
		assert(vertices.size() > 2);
	}
	void Transform(DirectX::FXMMATRIX matrix)
	{
		for (auto& v : vertices)
		{
			const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);
			DirectX::XMStoreFloat3(
				&v.pos,
				DirectX::XMVector3Transform(pos, matrix)
			);
		}
	}

public:
	std::vector<T> vertices;
};


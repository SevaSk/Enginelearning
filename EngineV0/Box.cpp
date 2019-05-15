#include "Box.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"


Box::Box(Graphics& gfx,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	std::uniform_real_distribution<float>& bdist)
	:
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng))
{
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		};
	};

	const std::vector<Vertex> vertices =
	{
		{-1.0f,-1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f},
		{-1.0f,1.0f,-1.0f},
		{1.0f,1.0f,-1.0f},
		{-1.0f,-1.0f,1.0f},
		{1.0f,-1.0f,1.0f},
		{-1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	AddBind(std::make_unique<VertexBuffer>(gfx, vertices));
	auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
	auto pvsbc = pvs->GetBytecode();

	AddBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

	const std::vector<unsigned short> indices = 
	{
		0,2,1,   2,3,1,
		1,3,5,   3,7,5,
		2,6,3,   3,6,7,
		4,5,7,   4,7,6,
		0,4,2,   2,4,6,
		0,1,4,   1,5,4,
	};

	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));


	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_color[6];
	};

	ConstantBuffer2 cb2 = {
	{
		{1.0f,0.0f,1.0f,1.0f},
		{1.0f,0.0f,0.0f,1.0f},
		{0.0f,1.0f,0.0f,1.0f},
		{0.0f,0.0f,1.0f,1.0f},
		{1.0f,1.0f,0.0f,1.0f},
		{0.0f,1.0f,1.0f,1.0f},
	}
	};

	AddBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	AddBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

}


void Box::Update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&mt) *
		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		dx::XMMatrixTranslation(r, 0.0f, 0.0f) *
		dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}
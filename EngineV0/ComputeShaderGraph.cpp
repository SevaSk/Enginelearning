#include "ComputeShaderGraph.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"


ComputeShaderGraph::ComputeShaderGraph(Graphics& gfx)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		auto pvs = std::make_unique<VertexShader>(gfx, L"ComputeShaderVS.cso");

		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ComputeShaderPS.cso"));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddStaticComputeShader(std::make_unique<ComputeShader>(gfx, L"Path"));

	}
	else
	{
		SetIndexFromStatic();
	}


	dx::XMStoreFloat3x3(&mt,
		dx::XMMatrixScaling(3.0f, 3.0f, 3.0f)
	);

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

}

void ComputeShaderGraph::Update(float dt) noexcept
{
	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}


DirectX::XMMATRIX ComputeShaderGraph::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return 
		DirectX::XMLoadFloat3x3(&mt)*
		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		dx::XMMatrixTranslation(r, 0.0f, 0.0f) *
		dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}

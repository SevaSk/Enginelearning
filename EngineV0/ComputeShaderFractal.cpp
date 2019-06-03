#include "ComputeShaderFractal.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "MarchingCubesIso.h"


ComputeShaderFractal::ComputeShaderFractal(Graphics& gfx, float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{

		// AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));
		auto pvs = std::make_unique<VertexShader>(gfx, L"ComputeShaderVS.cso");

		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongBinnPS.cso"));

		std::vector<unsigned int> indices;
		indices.reserve(12*373248);
		for (unsigned int i = 0; i < 12* 373248; i++)
		{
			indices.push_back(i);
		}
		
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx,indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
		};
		
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddStaticBind(std::make_unique<ComputeShader>(gfx, L"Path"));

	}
	else
	{
		SetIndexFromStatic();
	}


	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

}

void ComputeShaderFractal::Update(float dt) noexcept
{

}


DirectX::XMMATRIX ComputeShaderFractal::GetTransformXM() const noexcept
{
	return
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f)*
		DirectX::XMMatrixTranslation(x, y, z)*
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
}

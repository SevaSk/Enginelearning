#include "Fractals.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Mandlebulb.h"

Fractals::Fractals(Graphics & gfx)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			dx::XMFLOAT3 n;
		};

		auto model = Mandlebulb::Make<Vertex>();
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		auto pvs = std::make_unique<VertexShader>(gfx, L"PhongBinnVS.cso");

		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongBinnPS.cso"));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

}

void Fractals::Update(float dt) noexcept
{

}

DirectX::XMMATRIX Fractals::GetTransformXM() const noexcept
{
	return
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f)*
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)*
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
}

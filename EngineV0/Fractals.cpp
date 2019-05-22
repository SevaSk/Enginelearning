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
		};

		TriangleStrip<Vertex> model = Mandlebulb::Make<Vertex>();
		AddStaticVertexBuffer(std::make_unique<VertexBuffer>(gfx, model.vertices));
		auto pvs = std::make_unique<VertexShader>(gfx, L"ColorIndexVS.cso");

		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorIndexPS.cso"));

		struct PixelShaderConstants
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[8];
		};
		const PixelShaderConstants cb2 =
		{
			{
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f }
			}
		};
		AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP));
	}
	else
	{
		SetVertexFromStatic();
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

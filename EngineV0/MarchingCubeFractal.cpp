#include "MarchingCubeFractal.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "MarchingCubesIso.h"
#include "ConvergenceFuncs.h"

MarchingCubeFractal::MarchingCubeFractal(Graphics& gfx, float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
		};

		auto model = MarchingCubesIso::Make<Vertex>(convn4,3,3,3,1.0f/16.0f);
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		auto pvs = std::make_unique<VertexShader>(gfx, L"ColorIndexVS.cso");

		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorIndexPS.cso"));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

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
				{ 0.7f,0.7f,0.7f },
				{ 0.7f,0.7f,0.7f },
				{ 0.7f,0.7f,0.7f },
				{ 0.7f,0.7f,0.7f },
				{ 0.7f,0.7f,0.7f },
				{ 0.7f,0.7f,0.7f },
				{ 0.7f,0.7f,0.7f },
				{ 0.7f,0.7f,0.7f },
			}
		};
		AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
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

void MarchingCubeFractal::Update(float dt) noexcept
{

}


DirectX::XMMATRIX MarchingCubeFractal::GetTransformXM() const noexcept
{
	return
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f)*
		DirectX::XMMatrixTranslation(x, y, z)*
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
}

#include "Fractal.h"
#include "GraphicsThrowMacros.h"

Fractal::Fractal(Graphics& gfx)
{
	for (float x = -2; x < 2; x+= 1.0f/1.0f)
	{
		voxels.push_back(std::make_unique<Voxel>(gfx,x,0.0f,0.0f));
	}

}

void Fractal::Update(float dt) noexcept
{
	for (auto& b : voxels)
	{
		b->Update(dt);
	}
}

void Fractal::Draw(Graphics& gfx) const noexcept(!IS_DEBUG)
{
	for (auto& b : voxels)
	{
		b->Draw(gfx);
	}

}

DirectX::XMMATRIX Fractal::GetTransformXM() const noexcept
{
	return
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
}

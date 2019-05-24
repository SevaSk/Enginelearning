#include "Fractal.h"
#include "GraphicsThrowMacros.h"
#include "ConvergenceFuncs.h"

Fractal::Fractal(Graphics& gfx)
{
	constexpr float voxLen = 1.0f / 4.0f;
	for (float x = 0; x < 5; x+= voxLen)
	{
		for (float y = 0; y < 5; y+= voxLen)
		{
			for (float z = 0; z < 5; z+= voxLen)
			{
				if (true)
				{
				voxels.push_back(std::make_unique<Voxel>(gfx,x,y,z));
				}
			}
		}
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

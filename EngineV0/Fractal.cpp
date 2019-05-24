#include "Fractal.h"
#include "GraphicsThrowMacros.h"
#include "ConvergenceFuncs.h"

Fractal::Fractal(Graphics& gfx)
{
	constexpr float voxLen = 1.0f / 8.0f;
	for (float x = -3; x < 3; x+= voxLen)
	{
		for (float y = -3; y < 3; y+= voxLen)
		{
			for (float z = -3; z < 3; z+= voxLen)
			{
				if (convn4(DirectX::XMFLOAT3(x,y,z)))
				{
				voxels.push_back(std::make_unique<Voxel>(gfx,4*x,4*y,4*z));
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

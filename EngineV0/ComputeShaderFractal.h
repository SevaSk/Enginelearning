#pragma once

#include "DrawableBase.h"
#include "ConvergenceFuncs.h"

class ComputeShaderFractal : public DrawableBase<ComputeShaderFractal>
{
public:
	ComputeShaderFractal(Graphics& gfx, float x, float y, float z);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	float x;
	float y;
	float z;
};




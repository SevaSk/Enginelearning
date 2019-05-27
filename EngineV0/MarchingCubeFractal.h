#pragma once

#include "DrawableBase.h"

class MarchingCubeFractal : public DrawableBase<MarchingCubeFractal>
{
public:
	MarchingCubeFractal(Graphics& gfx, float x, float y, float z);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	float x;
	float y;
	float z;
};


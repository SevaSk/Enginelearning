#pragma once

#include "DrawableBase.h"
#include "ConvergenceFuncs.h"

class ComputeShaderFractal : public DrawableBase<ComputeShaderFractal>
{
public:
	ComputeShaderFractal(Graphics& gfx);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	float r = 0.0;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	float chi = 0.0f;
	// speed (delta/s)
	float droll = 0.0f;
	float dpitch = 0.0f;
	float dyaw = 0.0f;
	float dtheta = 0.0f;
	float dphi = 1.0f;
	float dchi = 0.0f;
	// model transform
	DirectX::XMFLOAT3X3 mt;
};




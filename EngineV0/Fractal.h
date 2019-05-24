#pragma once

#include "Voxel.h"

class Fractal
{
public:
	Fractal(Graphics& gfx);
	void Update(float dt) noexcept;
	void Draw(Graphics& gfx) const noexcept(!IS_DEBUG);
	DirectX::XMMATRIX GetTransformXM() const noexcept;

private:
	std::vector<std::unique_ptr<class Voxel>> voxels;

};



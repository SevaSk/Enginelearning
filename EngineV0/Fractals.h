#pragma once

#include "DrawableBase.h"

class Fractals : public DrawableBase<Fractals>
{
public:
	Fractals(Graphics& gfx);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	
};


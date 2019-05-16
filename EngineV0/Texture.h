#pragma once

#include "Bindable.h"

class Texture : public Bindable
{
public:
	Texture(Graphics& gfx);
	void Bind(Graphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
};



#pragma once

#include "Graphics.h"

class ComputeShader 
{
public:
	ComputeShader(Graphics& gfx, const LPCWSTR path);
protected:
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> pComputeShader;
	static DxgiInfoManager& GetInfoManager(Graphics& gfx) noexcept(!IS_DEBUG);
};


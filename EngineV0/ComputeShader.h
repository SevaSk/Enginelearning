#pragma once

#include "Bindable.h"

class ComputeShader : public Bindable
{
public:
	ComputeShader(Graphics& gfx, const LPCWSTR path);
	void Bind(Graphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> pComputeShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>  pStructuredBuffer;
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> pStructuredBufferUAV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pStructuredBufferSRV;
	Microsoft::WRL::ComPtr<ID3D11Buffer>  pConstantBuffer;
};


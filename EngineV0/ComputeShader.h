#pragma once

#include "Bindable.h"

class ComputeShader : public Bindable
{
public:
	ComputeShader(Graphics& gfx, const LPCWSTR path);
	void Bind(Graphics& gfx) noexcept override;
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetArgsBuffer() const noexcept;
protected:
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> pComputeShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>  pStructuredBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>  pArgsBuffer;
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> pStructuredBufferUAV;
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> pArgsBufferUAV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pStructuredBufferSRV;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer2;
};


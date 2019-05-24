#include "ComputeShader.h"
#include "GraphicsThrowMacros.h"

ComputeShader::ComputeShader(Graphics& gfx, const LPCWSTR path)
{
	INFOMAN(gfx);
	LPCSTR profile = (gfx.pDevice.Get()->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob;

	GFX_THROW_INFO(D3DCompileFromFile(
		L"ComputeShader.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"CSMain",
		profile,
		D3DCOMPILE_PARTIAL_PRECISION || D3DCOMPILE_ENABLE_STRICTNESS,
		0,
		&pBlob,
		&pErrorBlob));

	GFX_THROW_INFO(gfx.pDevice.Get()->CreateComputeShader(pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		nullptr,
		&pComputeShader));

}

DxgiInfoManager & ComputeShader::GetInfoManager(Graphics & gfx) noexcept(!IS_DEBUG)
{
#ifndef NDEBUG
	return gfx.infoManager;
#else
	throw std::logic_error("tried to access gfx.infoManager in Release config");
#endif
}

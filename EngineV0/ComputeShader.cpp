#include "ComputeShader.h"
#include "GraphicsThrowMacros.h"

ComputeShader::ComputeShader(Graphics& gfx, const LPCWSTR path)
{
	unsigned int THREAD_GRID_SIZE_X = 400;
	unsigned int THREAD_GRID_SIZE_Y = 400;

	INFOMAN(gfx);

	//creating structered buffer
	struct BufferStruct
	{
		struct
		{
			UINT r;
			UINT g;
			UINT b;
			UINT a;
		}color;
	};

	D3D11_BUFFER_DESC sbDesc = {};
	sbDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	sbDesc.CPUAccessFlags = 0;
	sbDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	sbDesc.StructureByteStride = sizeof(BufferStruct);
	sbDesc.ByteWidth = sizeof(BufferStruct) * THREAD_GRID_SIZE_X * THREAD_GRID_SIZE_Y;
	sbDesc.Usage = D3D11_USAGE_DEFAULT;
	
	Microsoft::WRL::ComPtr<ID3D11Buffer>  pStructuredBuffer;
	GFX_THROW_INFO(gfx.pDevice.Get()->CreateBuffer(&sbDesc, nullptr, &pStructuredBuffer));

	//creating UAV
	D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;
	sbUAVDesc.Buffer.FirstElement = 0;
	sbUAVDesc.Buffer.Flags = 0;
	sbUAVDesc.Buffer.NumElements = THREAD_GRID_SIZE_X * THREAD_GRID_SIZE_Y;
	sbUAVDesc.Format = DXGI_FORMAT_UNKNOWN;
	sbUAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> pStructuredBufferUAV;
	GFX_THROW_INFO(gfx.pDevice.Get()->CreateUnorderedAccessView(pStructuredBuffer.Get(), &sbUAVDesc, &pStructuredBufferUAV));

	//creating Shader Resource View
	D3D11_SHADER_RESOURCE_VIEW_DESC sbSRVDesc;
	sbSRVDesc.Buffer.ElementOffset = 0;
	sbSRVDesc.Buffer.ElementWidth = sizeof(BufferStruct);
	sbSRVDesc.Buffer.FirstElement = 0;
	sbSRVDesc.Buffer.NumElements = THREAD_GRID_SIZE_X * THREAD_GRID_SIZE_Y;
	sbSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	sbSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pStructuredBufferSRV;
	GFX_THROW_INFO(gfx.pDevice.Get()->CreateShaderResourceView(pStructuredBuffer.Get(), &sbSRVDesc, &pStructuredBufferSRV));


	//compile and create the compute shader
	LPCSTR profile = (gfx.pDevice.Get()->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob;

	GFX_THROW_INFO(D3DCompileFromFile(L"ComputeShader.hlsl", NULL, NULL,"main", profile, 0, 0, &pBlob, &pErrorBlob));
	GFX_THROW_INFO(gfx.pDevice.Get()->CreateComputeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pComputeShader));


	//dispatch threads
	UINT initCounts = 0;
	gfx.pContext.Get()->CSSetUnorderedAccessViews(0, 1, pStructuredBufferUAV.GetAddressOf(),&initCounts);
	gfx.pContext.Get()->CSSetShader(pComputeShader.Get(), NULL, 0);
	gfx.pContext.Get()->Dispatch(20,20,1);
	ID3D11UnorderedAccessView* pNullUAV = NULL;
	gfx.pContext.Get()->CSSetUnorderedAccessViews(0, 1, &pNullUAV, &initCounts);

}









DxgiInfoManager & ComputeShader::GetInfoManager(Graphics & gfx) noexcept(!IS_DEBUG)
{
#ifndef NDEBUG
	return gfx.infoManager;
#else
	throw std::logic_error("tried to access gfx.infoManager in Release config");
#endif
}

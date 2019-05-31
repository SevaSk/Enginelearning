#include "ComputeShader.h"
#include "GraphicsThrowMacros.h"

ComputeShader::ComputeShader(Graphics& gfx, const LPCWSTR path)
{
	unsigned int THREAD_GRID_SIZE_X = 441;
	unsigned int THREAD_GRID_SIZE_Y = 441;

	INFOMAN(gfx);

	//creating structered buffer
	struct BufferStruct
	{
		float x;
		float y;
		float z;
	};

	D3D11_BUFFER_DESC sbDesc = {};
	sbDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	sbDesc.CPUAccessFlags = 0;
	sbDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	sbDesc.StructureByteStride = sizeof(BufferStruct);
	sbDesc.ByteWidth = sizeof(BufferStruct) * THREAD_GRID_SIZE_X * THREAD_GRID_SIZE_Y;
	sbDesc.Usage = D3D11_USAGE_DEFAULT;
	
	GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&sbDesc, nullptr, &pStructuredBuffer));

	//creating UAV
	D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;
	sbUAVDesc.Buffer.FirstElement = 0;
	sbUAVDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
	sbUAVDesc.Buffer.NumElements = THREAD_GRID_SIZE_X * THREAD_GRID_SIZE_Y;
	sbUAVDesc.Format = DXGI_FORMAT_UNKNOWN;
	sbUAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

	GFX_THROW_INFO(GetDevice(gfx)->CreateUnorderedAccessView(pStructuredBuffer.Get(), &sbUAVDesc, &pStructuredBufferUAV));

	//creating SRV
	D3D11_SHADER_RESOURCE_VIEW_DESC sbSRVDesc;
	sbSRVDesc.Buffer.ElementOffset = 0;
	sbSRVDesc.Buffer.ElementWidth = sizeof(BufferStruct);
	sbSRVDesc.Buffer.FirstElement = 0;
	sbSRVDesc.Buffer.NumElements = THREAD_GRID_SIZE_X * THREAD_GRID_SIZE_Y;
	sbSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	sbSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

	GFX_THROW_INFO(GetDevice(gfx)->CreateShaderResourceView(pStructuredBuffer.Get(), &sbSRVDesc, &pStructuredBufferSRV));


	//compile and create the compute shader
	LPCSTR profile = (GetDevice(gfx)->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob;

	GFX_THROW_INFO(D3DCompileFromFile(L"ComputeShader.hlsl", NULL, NULL,"main", profile, 0, 0, &pBlob, &pErrorBlob));
	GFX_THROW_INFO(GetDevice(gfx)->CreateComputeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &pComputeShader));

	//dispatch threads
	UINT initCounts = 0;
	GetContext(gfx)->CSSetUnorderedAccessViews(0, 1, pStructuredBufferUAV.GetAddressOf(), &initCounts);
	GetContext(gfx)->CSSetShader(pComputeShader.Get(), NULL, 0);
	GetContext(gfx)->Dispatch(21, 21, 1);


	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> pNullUAV = NULL;
	GetContext(gfx)->CSSetUnorderedAccessViews(0, 1, &pNullUAV, &initCounts);

}

void ComputeShader::Bind(Graphics& gfx) noexcept
{
	//bind to vertex shader
	GetContext(gfx)->VSSetShaderResources(0, 1, pStructuredBufferSRV.GetAddressOf());
}


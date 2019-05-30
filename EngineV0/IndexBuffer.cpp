#include "IndexBuffer.h"
#include "GraphicsThrowMacros.h"

IndexBuffer::IndexBuffer(Graphics & gfx, const std::vector<unsigned int> indices):
	count((UINT)std::size(indices))
{
	INFOMAN(gfx);

	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = UINT(count * sizeof(unsigned int));
	ibd.StructureByteStride = sizeof(unsigned int);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&ibd, &isd, &pIndexBuffer));
}

void IndexBuffer::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}

UINT IndexBuffer::GetCount() const noexcept
{
	return count;
}
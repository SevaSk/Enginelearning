#include "Texture.h"
#include "GraphicsThrowMacros.h"
#include "WICTextureLoader.h"



namespace wrl = Microsoft::WRL;

Texture::Texture(Graphics& gfx, const wchar_t* file)
{
	INFOMAN(gfx);

	wrl::ComPtr<ID3D11Texture2D>  pTexture;

	wrl::ComPtr<ID3D11Resource> pResource;

	GFX_THROW_INFO(CreateWICTextureFromFile(GetDevice(gfx), GetContext(gfx), file, &pResource, &pTextureView));

}

void Texture::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}
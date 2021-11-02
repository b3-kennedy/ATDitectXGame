#include "PixelShader.h"

PixelShader::PixelShader(Graphics& gfx, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	D3DReadFileToBlob(path.c_str(), &blob);
	GetDevice(gfx)->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
}

void PixelShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pixelShader.Get(), nullptr, 0u);
}

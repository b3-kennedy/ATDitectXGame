#include "VertexShader.h"


VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	D3DReadFileToBlob(path.c_str(), &blob);
	GetDevice(gfx)->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
}

void VertexShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(vertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return blob.Get();
}
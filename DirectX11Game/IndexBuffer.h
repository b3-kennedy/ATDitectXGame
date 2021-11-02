#pragma once
#include "Bindable.h"
#include <vector>

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);
	void Bind(Graphics& gfx) noexcept override;
	UINT GetCount() const noexcept;
protected:
	UINT indexCount;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
};
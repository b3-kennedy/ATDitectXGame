#pragma once
#include "Graphics.h"
#include <DirectXMath.h>
#include <vector>
#include <memory>


class Bindable;

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual DirectX::XMMATRIX GetTransformMatrix() const noexcept = 0;
	void Draw(Graphics& gfx) const noexcept;
	virtual void Update(float deltaTime) noexcept = 0;
	void AddBind(std::unique_ptr<Bindable> bind) noexcept;
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> indexBuffer) noexcept;
	virtual ~Drawable() = default;
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;
};


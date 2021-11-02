#include "TransformBuffer.h"

TransformBuffer::TransformBuffer(Graphics& gfx, const Drawable& parent)
	:
	vcbuf(gfx),
	parent(parent)
{}

void TransformBuffer::Bind(Graphics& gfx) noexcept
{
	vcbuf.Update(gfx,
		DirectX::XMMatrixTranspose(
			parent.GetTransformMatrix() * gfx.GetProjection()
		)
	);
	vcbuf.Bind(gfx);
}
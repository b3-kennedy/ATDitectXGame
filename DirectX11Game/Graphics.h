#pragma once
#include "WindowInclude.h"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

class Graphics
{
public:
	Graphics( HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept
	{
		const float colour[] = { r,g,b,1.0f };
		pContext->ClearRenderTargetView(pTarget, colour);
	}
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};

#pragma once
#include "WindowInclude.h"
#include <d3d11.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")

class Graphics
{
public:
	Graphics( HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept
	{
		const float colour[] = { r,g,b,1.0f };
		pContext->ClearRenderTargetView(pTarget.Get(), colour);
	}
	void DrawTriangle();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr < IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr < ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr < ID3D11RenderTargetView> pTarget;
};


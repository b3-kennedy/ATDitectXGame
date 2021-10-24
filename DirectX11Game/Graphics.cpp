#include "Graphics.h"
#include <d3dcompiler.h>
#include <array>
#include <cmath>
#include <DirectXMath.h>

#pragma comment(lib, "D3DCompiler.lib")


Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = FALSE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &pSwap, &pDevice, nullptr, &pContext);

	
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget);

	pBackBuffer->Release();
}

//Graphics::~Graphics()
//{
//	if(pDevice != nullptr)
//	{
//		pDevice->Release();
//	}
//	if (pSwap != nullptr)
//	{
//		pSwap->Release();
//	}
//	if (pContext != nullptr)
//	{
//		pContext->Release();
//	}
//	if (pTarget != nullptr)
//	{
//		pTarget->Release();
//	}
//}

void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);
}

void Graphics::DrawTriangle(float angle)
{
	

	struct Vertex
	{
		struct 
		{
			float x;
			float y;
		}pos;
		struct 
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		}colour;
	};

	const Vertex vertices[] =
	{
		{0.0f,0.5f,255,0,0,0},
		{0.5f,-0.5f,0.0f,255,0,0},
		{-0.5f,-0.5f,0.0f,0,255,0},

		//{0.5f,1.0f},
		//{1.0f,0.5f},
		//{0.5f,0.5f},
	};

	const unsigned short indices[] =
	{
		0,1,2
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.CPUAccessFlags = 0u;
	vertexBufferDesc.MiscFlags = 0u;
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.StructureByteStride = sizeof(Vertex);
	
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;

	pDevice->CreateBuffer(&vertexBufferDesc, &sd, &pVertexBuffer);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u,1u, pVertexBuffer.GetAddressOf(), &stride, &offset);


	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.ByteWidth = sizeof(indices);
	indexBufferDesc.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	pDevice->CreateBuffer(&indexBufferDesc, &isd, &indexBuffer);

	pContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	struct ConstantBuffer
	{
		struct 
		{
			float element[4][4];
		}transformation;
	};

	const ConstantBuffer constantBufferData =
	{
		{
			0.5625f * std::cos(angle), std::sin(angle),0.0f,0.0f,
			0.5625f  * -std::sin(angle), std::cos(angle),0.0f,0.0f,
			0.0,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f
		}
	};


	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0u;
	constantBufferDesc.ByteWidth = sizeof(constantBufferData);
	constantBufferDesc.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &constantBufferData;
	pDevice->CreateBuffer(&constantBufferDesc, &csd, &constantBuffer);

	pContext->VSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	D3DReadFileToBlob(L"PixelShader.cso", &blob);
	pDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
	pContext->PSSetShader(pixelShader.Get(), nullptr, 0u);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &blob);
	pDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
	pContext->VSSetShader(vertexShader.Get(), nullptr, 0);




	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	const D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOUR",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,8u,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	pDevice->CreateInputLayout(inputDesc, (UINT)std::size(inputDesc), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);

	pContext->IASetInputLayout(inputLayout.Get());

	


	

	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);

	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	viewport.Width = 1920;
	viewport.Height = 1080;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	pContext->RSSetViewports(1u, &viewport);

	//pContext->Draw(std::size(vertices), 0u);
	pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
}

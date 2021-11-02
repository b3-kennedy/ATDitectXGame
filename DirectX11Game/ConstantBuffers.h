#pragma once
#include "Bindable.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	void Update(Graphics& gfx, const C& consts)
	{
		D3D11_MAPPED_SUBRESOURCE subresource;
		GetContext(gfx)->Map(
			constantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&subresource
		);
		memcpy(subresource.pData, &consts, sizeof(consts));
		GetContext(gfx)->Unmap(constantBuffer.Get(), 0u);
	}
	ConstantBuffer(Graphics& gfx, const C& consts)
	{

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0u;
		bufferDesc.ByteWidth = sizeof(consts);
		bufferDesc.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = &consts;
		GetDevice(gfx)->CreateBuffer(&bufferDesc, &subresourceData, &constantBuffer);
	}
	ConstantBuffer(Graphics& gfx)
	{

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0u;
		bufferDesc.ByteWidth = sizeof(C);
		bufferDesc.StructureByteStride = 0u;
		GetDevice(gfx)->CreateBuffer(&bufferDesc, nullptr, &constantBuffer);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::constantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) noexcept override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::constantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) noexcept override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
	}
};











//#pragma once
//#include "Bindable.h"
//
//template<typename C> 
//class ConstantBuffer : public Bindable
//{
//public:
//	void Update(Graphics& gfx, const C& consts)
//	{
//		D3D11_MAPPED_SUBRESOURCE subresource;
//		GetContext(gfx)->Map(
//			constantBuffer.Get(), 0u,
//			D3D11_MAP_WRITE_DISCARD, 0u,
//			&subresource
//		);
//		memcpy(subresource.pData, &consts, sizeof(consts));
//		GetContext(gfx)->Unmap(constantBuffer.Get(), 0u);
//	}
//	ConstantBuffer(Graphics& gfx, const C& consts)
//	{
//		D3D11_BUFFER_DESC constBufferDesc;
//		constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//		constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
//		constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//		constBufferDesc.MiscFlags = 0u;
//		constBufferDesc.ByteWidth = sizeof(consts);
//		constBufferDesc.StructureByteStride = 0u;
//
//		D3D11_SUBRESOURCE_DATA subresourceData = {};
//		subresourceData.pSysMem = &consts;
//		GetDevice(gfx)->CreateBuffer(&constBufferDesc, &subresourceData, &constantBuffer);
//	}
//
//	ConstantBuffer(Graphics& gfx)
//	{
//
//		D3D11_BUFFER_DESC constBufferDesc;
//		constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//		constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
//		constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//		constBufferDesc.MiscFlags = 0u;
//		constBufferDesc.ByteWidth = sizeof(C);
//		constBufferDesc.StructureByteStride = 0u;
//		GetDevice(gfx)->CreateBuffer(&constBufferDesc, nullptr, &constantBuffer);
//	}
//protected:
//	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
//
//	template<typename C>
//	class VertexConstantBuffer : public ConstantBuffer<C>
//	{
//		using ConstantBuffer<C>::constantBuffer;
//		using Bindable::GetContext;
//	public:
//		using ConstantBuffer<C>::ConstantBuffer;
//		void Bind(Graphics& gfx) noexcept override
//		{
//			GetContext(gfx)->VSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
//		}
//	};
//
//	template<typename C>
//	class PixelConstantBuffer : public ConstantBuffer<C>
//	{
//		using ConstantBuffer<C>::constantBuffer;
//		using Bindable::GetContext;
//	public:
//		using ConstantBuffer<C>::ConstantBuffer;
//		void Bind(Graphics& gfx) noexcept override
//		{
//			GetContext(gfx)->PSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
//		}
//	};
//
//};


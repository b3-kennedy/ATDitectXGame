#pragma once

#include "Cube.h"
#include "ConstantBuffers.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "Topology.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "TransformBuffer.h"

Cube::Cube(Graphics& gfx, float width, float height, float depth)
{

	std::vector<Vertex> vertices =
	{
		{ -width,-height,-depth },
		{ width,-height,-depth },
		{ -width,height,-depth },
		{ width,height,-depth },
		{ -width,-height,depth },
		{ width,-height,depth },
		{ -width,height,depth },
		{ width,height,depth },
	};


	AddBind(std::make_unique<VertexBuffer>(gfx, vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};
	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	const ConstantBuffer2 cb2 =
	{
		{
			{ 1.0f,0.0f,1.0f },
			{ 1.0f,0.0f,0.0f },
			{ 0.0f,1.0f,0.0f },
			{ 0.0f,0.0f,1.0f },
			{ 1.0f,1.0f,0.0f },
			{ 0.0f,1.0f,1.0f },
		}
	};
	AddBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	AddBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformBuffer>(gfx, *this));


}


void Cube::Update(float dt) noexcept
{
	//roll += deltaRoll * dt;
	//pitch += deltaPitch * dt;
	//yaw += deltaYaw * dt;
	//theta += deltaTheta * dt;
	//phi += deltaPhi * dt;
	//chi += deltaChi * dt;
	

	

}

DirectX::XMMATRIX Cube::GetTransformMatrix() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixTranslation(0, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//return DirectX::XMMatrixTranslation(position.x, position.y, position.z);
}

void Cube::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}














bool Cube::OnCollision(DirectX::XMFLOAT3 point)
{		
	return (point.x >= this->GetPosition().x - 2.5f && point.x <= this->GetPosition().x + 2)
			&& (point.z >= this->GetPosition().z - 2 && point.z <= this->GetPosition().z + 2)
			&& (point.y >= this->GetPosition().y && point.y <= this->GetPosition().y + 10.0f);
}















bool Cube::OnCollisionExit(Camera* cam)
{
	if(cam->Colliding())
	{
		if(!OnCollision(cam->GetPosition()))
		{
			cam->IsColliding(false);
			return true;
		}
	}

	return false;
}

void Cube::SetActive(bool value)
{
	canDraw = value;
}

bool Cube::IsActive()
{
	return canDraw;
}


Vector3 Cube::GetPosition()
{
	return position;
}

#include "Camera.h"
#include <string>
#include <directxmath.h>


DirectX::XMMATRIX Camera::GetMatrix() noexcept
{
	//const auto pos = DirectX::XMVector3Transform(DirectX::XMVectorSet(position.x, position.y, -r, 0.0f), DirectX::XMMatrixRotationRollPitchYaw(phi,-theta,0.0f));

	//return DirectX::XMMatrixLookAtLH(pos, DirectX::XMVectorZero(), 
	//	DirectX::XMVectorSet(0.0f,1.0f,0.0f,0.0f)) * DirectX::XMMatrixRotationRollPitchYaw(pitch, -yaw, roll);
	//return DirectX::XMMatrixTranslation(-position.x, -position.y, -position.z) * DirectX::XMMatrixRotationRollPitchYaw(-pitch, -yaw, 0.0f);
	DirectX::XMVECTOR forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR lookDirection = DirectX::XMVector3Transform(forward, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f));
	DirectX::XMStoreFloat3(&lookDir, lookDirection);
	const auto camPos = DirectX::XMLoadFloat3(&position);
	const auto camTarget =  DirectX::XMVectorAdd(camPos, lookDirection);
	return DirectX::XMMatrixLookAtLH(camPos, camTarget, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}


void Camera::Reset() noexcept
{
	position = { 0.0f,0.0f,0.0f };
	pitch = 0.0f;
	yaw = 0.0f;
}

void Camera::Rotate(float deltaX, float deltaY) noexcept
{
	yaw = wrap_angle(yaw + deltaX * rotSpeed);
	pitch = std::clamp(pitch + deltaY * rotSpeed, (-PI / 2.0f) * 0.995f, (PI / 2.0f) * 0.995f);
}

DirectX::XMFLOAT3 Camera::GetPosition() noexcept
{
	return position;
}

void Camera::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::SetSpeed(float speed)
{
	moveSpeed = speed;
}

void Camera::IsColliding(bool value)
{
	colliding = value;
}

bool Camera::Colliding() const
{
	return colliding;
}


float Camera::GetSpeed()
{
	return moveSpeed;
}


void Camera::Translate(DirectX::XMFLOAT3 translation) noexcept
{
	DirectX::XMStoreFloat3(&translation, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&translation),
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f) * DirectX::XMMatrixScaling(moveSpeed, moveSpeed, moveSpeed)));

	DirectX::XMVECTOR t = DirectX::XMVectorSet(translation.x, translation.y, translation.z, 0.0f);
	t = DirectX::XMVector3Normalize(t);
	DirectX::XMStoreFloat3(&trans, t);
	position.y = -5.0f;
	position = { position.x + trans.x/10, position.y + trans.y/100, position.z + trans.z/10};


}


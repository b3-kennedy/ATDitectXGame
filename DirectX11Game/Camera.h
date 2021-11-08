#pragma once
#include "Graphics.h"
#include "Vector3.h"
#include <math.h>
#include "RawDelta.h"


class Camera
{
public:
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void Reset() noexcept;
	void Rotate(float deltaX, float deltaY) noexcept;
	DirectX::XMFLOAT3 GetPosition() noexcept;
	void SetPosition(float x, float y, float z);
	void SetSpeed(float speed);
	void IsColliding(bool value);

	float GetSpeed();
	void Translate(DirectX::XMFLOAT3 translation) noexcept;
private:
	DirectX::XMFLOAT3 position = {0.0f,0.0f,0.0f};
	float pitch;
	float yaw;
	float moveSpeed = 12.0f;
	bool colliding = false;
	DirectX::XMVECTOR lookDir = { 0,0,0 };
	static constexpr float rotSpeed = 0.004f;

};


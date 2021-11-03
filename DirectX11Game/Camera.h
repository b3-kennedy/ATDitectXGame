#pragma once
#include "Graphics.h"
#include "Vector3.h"

class Camera
{
public:
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void ChangeZ(float z);
	void Reset() noexcept;
private:
	Vector3 position = {0.0f,0.0f,0.0f};
	float r = 20.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

};


#pragma once
#include "Drawable.h"
#include "Vector3.h"
#include <random>

class Cube : public Drawable
{
public:
	Cube(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformMatrix() const noexcept override;
	void SetPosition(float x, float y, float z);
	Vector3 GetPosition();
private:

	Vector3 position;
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	float deltaRoll;
	float deltaPitch;
	float deltaYaw;
	float deltaTheta;
	float deltaPhi;
	float deltaChi;
	float move;
};
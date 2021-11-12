#pragma once
#include "Drawable.h"
#include "Vector3.h"
#include <random>
#include "Camera.h"
#include "Vertex.h"

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
	bool OnCollision(Camera* cam);
	bool OnCollisionExit(Camera* cam);
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



	const std::vector<Vertex> vertices =
	{
		{ -1.0f,-10.0f,-1.0f },
		{ 1.0f,-10.0f,-1.0f },
		{ -1.0f,10.0f,-1.0f },
		{ 1.0f,10.0f,-1.0f },
		{ -1.0f,-10.0f,1.0f },
		{ 1.0f,-10.0f,1.0f },
		{ -1.0f,10.0f,1.0f },
		{ 1.0f,10.0f,1.0f },
	};
};
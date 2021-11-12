#pragma once
#include "Drawable.h"
#include "Vector3.h"
#include <random>
#include "Camera.h"
#include "Vertex.h"

class Cube : public Drawable
{

public:
	Cube(Graphics& gfx, float width, float height, float depth);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformMatrix() const noexcept override;
	void SetPosition(float x, float y, float z);
	bool OnCollision(DirectX::XMFLOAT3 point);
	bool OnCollisionExit(Camera* cam);
	void SetActive(bool value);
	bool IsActive();
	Vector3 GetPosition();
	std::string tag;
	void setVelocity(DirectX::XMFLOAT3 vel);
	DirectX::XMFLOAT3 getVelocity();

private:
	DirectX::XMFLOAT3 velocity = {0.0f,0.0f,0.0f};
	Vector3 position;
	bool canDraw;
	//float r;
	//float roll = 0.0f;
	//float pitch = 0.0f;
	//float yaw = 0.0f;
	//float theta;
	//float phi;
	//float chi;
	//float deltaRoll;
	//float deltaPitch;
	//float deltaYaw;
	//float deltaTheta;
	//float deltaPhi;
	//float deltaChi;
	//float move;

};
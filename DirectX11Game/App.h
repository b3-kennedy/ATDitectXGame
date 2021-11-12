#pragma once
#include "Window.h"
#include "Timer.h"
#include "LevelLoader.h"
#include "Camera.h"
#include "RawDelta.h"

class App
{
public:
	App();
	int Go();
	~App();
private:
	void DoFrame(float deltaTime);
	void Input(float deltaTime);
	void MovePlayer(float deltaTime);
	void Shoot(float deltaTime);
private:
	Window window;
	Timer timer;
	std::vector<std::unique_ptr<class Cube>> cubes;
	std::vector<std::unique_ptr<class Cube>> bullets;
	LevelLoader levelLoader;
	std::unique_ptr<Camera> cam = std::make_unique<Camera>();
	const int NUMBER_OF_CUBES = 900;
	const int NUMBER_OF_BULLETS = 5;
	bool canMove = true;
	DirectX::XMFLOAT3 vel = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 currentLookDir = { 0.0f, 0.0f, 0.0f };
	int bulletNum = 0;
	Cube* cube = nullptr;
	bool canInput = true;
	bool mousePressed = false;
	float shootCooldown = 0.0f;
};


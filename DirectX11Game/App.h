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
private:
	Window window;
	Timer timer;
	std::vector<std::unique_ptr<class Cube>> cubes;
	std::unique_ptr<class Cube> singleCube;
	LevelLoader levelLoader;
	std::unique_ptr<Camera> cam = std::make_unique<Camera>();
	const int NUMBER_OF_CUBES = 900;
	bool canMove = true;
	DirectX::XMFLOAT3 vel = { 0.0f,0.0f,0.0f };
	Cube* cube = nullptr;
	bool canInput = true;
};


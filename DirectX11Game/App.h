#pragma once
#include "Window.h"
#include "Timer.h"
#include "LevelLoader.h"
#include "Camera.h"

class App
{
public:
	App();
	int Go();
	~App();
private:
	void DoFrame();
private:
	Window window;
	Timer timer;
	std::vector<std::unique_ptr<class Cube>> cubes;
	std::unique_ptr<class Cube> singleCube;
	LevelLoader levelLoader;
	Camera cam;
};


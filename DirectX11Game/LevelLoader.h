#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Window.h"
#include "Cube.h"
#include <list>

class LevelLoader
{
public:
	LevelLoader() = default;
	~LevelLoader() = default;

	bool ReadFile(std::string path);
	bool ConstructLevel(Cube* cube);
	void PositionEnemies(Cube* cube, int index);
	std::string fileContents;
	int numberOfCharacters = 0;
	std::vector<DirectX::XMFLOAT3> enemyPositions;
	int index = 0;
private:
	std::list<std::pair<int,std::string>> fileLines;
	int lineNumber = 0;
	

};


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
	std::string fileContents;
private:
	std::list<std::pair<int,std::string>> fileLines;
	int lineNumber = 0;

};


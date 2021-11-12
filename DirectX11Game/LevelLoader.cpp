#include "LevelLoader.h"

bool LevelLoader::ReadFile(std::string path)
{
    std::fstream file;
    file.open(path, std::ios::in);
    if(file.is_open())
    {
        std::string string;
        while(std::getline(file, string))
        {
            fileContents = string;
            fileLines.push_back({lineNumber, string});
            lineNumber++;
        }
        file.close();
        return true;
    }

    return false;
}

bool LevelLoader::ConstructLevel(Cube* cube)
{
    for(auto& elem : fileLines)
    {
        for (size_t i = 0; i < elem.second.size(); i++)
        {
            if(elem.second[i] == '#')
            {
                cube->SetPosition(i * 2, -10.0f, elem.first * 2);
                elem.second[i] = ' ';
                return true;
                
            }
            if(elem.second[i] == '/')
            {
                cube->SetPosition(i * 2, -20.0f, elem.first * 2);
                elem.second[i] = ' ';
                return true;
            }
            if(elem.second[i] == 'X')
            {
                std::vector<Cube*> cubes;
                if(cubes.size() < 2)
                {
                    cubes.push_back(cube);
                }
                else
                {
                    OutputDebugString("LOL");
                }
            }
            
        }
        

    }
    return false;
}

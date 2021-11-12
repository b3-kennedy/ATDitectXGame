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
            for (size_t i = 0; i < string.size(); i++)
            {
                if (string[i] == 'X')
                {
                    numberOfCharacters += 2;
                }
                else
                {
                    numberOfCharacters += 1;
                }
            }
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
                enemyPositions.push_back({ (float)i * 2, -10.0f, (float)elem.first * 2 });
                cube->SetPosition(i * 2, -20.0f, elem.first * 2);
                elem.second[i] = ' ';
                return true;
            }
            if (elem.second[i] == 'E')
            {
                return false;
            }
            
        }
        

    }
    return false;
}

void LevelLoader::PositionEnemies(Cube* cube, int index)
{
    cube->tag = "enemy";
    cube->SetPosition(enemyPositions[index].x, enemyPositions[index].y, enemyPositions[index].z);
}

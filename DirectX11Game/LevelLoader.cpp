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
            if(elem.second[i] == '#' && elem.first != 99)
            {
                cube->SetPosition(i * 2, elem.first * 2, 20);
                elem.second[i] = ' ';
                return true;

            }
        }
        

    }
    return false;
}

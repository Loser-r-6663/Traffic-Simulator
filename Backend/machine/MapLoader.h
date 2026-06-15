#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>

class MapLoader
{
public:
    static bool loadMap(const std::string &filePath);
};

#endif /*MAPLOADER_H*/
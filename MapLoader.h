#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
using namespace std;

#include "Map.h"

class MapLoader
{
    public:
        static Map* load(string& fname);
};

#endif

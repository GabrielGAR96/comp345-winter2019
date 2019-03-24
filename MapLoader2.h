#ifndef MAP_LOADER2_H
#define MAP_LOADER2_H

#include <string>
using namespace std;

#include "Map.h"

class MapLoader2
{
    public:
        static Map* load(string& fname);
};

class BadMap : public logic_error
{
    public:
        BadMap(string msg);
};

#endif

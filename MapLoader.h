#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
using namespace std;

#include "Map.h"

class MapLoader
{
    public:
        // Helper function to read text file and parse as map
        // NOTE: Expects the following format
        // --CITIES--
        // string(name):int(region)
        // ...
        // --CITIES--
        // --CONNECTIONS--
        // string(source):string(dest):int(cost)
        // ...
        // --CONNECTIONS--
        //
        // Anything else is invalid and NOTE: All sections must be present
        // even if empty
        //
        // Also maps with disconnected grids are considered invalid even if
        // syntax is correct
        static Map* load(string& fname);
};

class BadMap : public logic_error
{
    public:
        BadMap(string msg);
};

#endif

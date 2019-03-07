#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Map.h"
#include "MapLoader.h"

// Wrapper around MapLoader::Load that checks for validity explicitly
void loadAndCheck(string fname);

int main(int argc, char *argv[])
{
    // Files that have a valid map, a disconnected map and a garbage file
    // respectively
    string goodFile = "map.txt";
    string disconnectedFile = "disconnected_map.txt";
    string badFile = "badmap.txt";

    loadAndCheck(goodFile);
    loadAndCheck(disconnectedFile);
    loadAndCheck(badFile);
    return 0;
}

void loadAndCheck(string fname)
{
    cout << "##Checking " << fname << "##" << endl;
    Map* g = MapLoader::load(fname);
    if(g == nullptr) {
        // Getting NULL means that we couldn't read the file
        cout << "Invalid map" << endl;
    } else {
        // We read the file successfully but is it connected?
        cout << *g << endl;
        cout << (g->isValid() ? "valid connected map file" : "well formatted but disconnected") << endl;
    }
    cout << endl;

    // Cleanup
    delete g;
}


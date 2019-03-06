#include <iostream>
#include <string>
using namespace std;

#include "Map.h"
#include "MapLoader.h"

void loadAndCheck(string fname);

int main(int argc, char *argv[])
{
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
        cout << "Invalid map" << endl;
    } else {
        cout << *g << endl;
        cout << (g->isValid() ? "valid connected map file" : "well formatted but disconnected") << endl;
    }
    cout << endl;
    delete g;
}


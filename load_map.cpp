#include <iostream>
#include <unordered_set>
#include <vector>
#include <deque>
using namespace std;

#include "MapLoader.h"

int main(int argc, char *argv[])
{
    string map_file = "map2.txt";
    Map* g = MapLoader::load(map_file);
    if(g == nullptr) {
        cout << "Invalid map" << endl;
    } else {
        cout << g->printMap() << endl;
        cout << (g->isValid() ? "valid connected map file" : "well formatted but disconnected") << endl;
    }
    delete g;
    return 0;
}

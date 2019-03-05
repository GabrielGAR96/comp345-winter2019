#include <iostream>
#include <unordered_set>
#include <vector>
#include <deque>
using namespace std;

#include "Graph.h"
#include "MapLoader.h"
#include "City.h"

int main(int argc, char *argv[])
{
    string map_file = "map2.txt";
    UndirectedGraph<City>* g = MapLoader::load(map_file);
    cout << *g << (Graph<City>::isConnected(*g) ? " connected" : " disconnected") << endl;
    delete g;
    return 0;
}

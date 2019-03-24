#include <iostream>
#include <string>
using namespace std;

#include "MapLoader2.h"
#include "Map.h"

int main(int argc, char *argv[])
{
    string file = argv[1];
    Map* powergrid;
    try {
        powergrid = MapLoader2::load(file);
    } catch(BadMap& ex) {
        cout << ex.what() << endl;
        cout << "Ending..." << endl;
        return - 1;
    }
    cout << powergrid->printMap() << endl;
    delete powergrid;
    return 0;
}

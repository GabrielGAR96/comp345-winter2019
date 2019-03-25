#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#include <boost/filesystem.hpp>

#include "MapLoader2.h"
#include "Map.h"

struct pathLeafString
{
    pair<int, string> operator()(const boost::filesystem::directory_entry& entry) const
    {
        static int i = 1;
        return make_pair(i++, entry.path().leaf().string());
    }
};

void readDirectory(const string& name, map<int, string>& files)
{
    boost::filesystem::path p(name);
    boost::filesystem::directory_iterator start(p);
    boost::filesystem::directory_iterator end;
    transform(start, end, inserter(files, files.end()), pathLeafString());
}

int main(int argc, char *argv[])
{
    map<int, string> files;
    readDirectory("./maps/", files);
    cout << "Available maps:" << endl;
    for(auto file : files)
    {
        cout << file.first << ". " << file.second << endl;
    }
    int selection;
    cout << endl << "select by entering #: ";
    cin >> selection;
    string file = "./maps/" + files[selection];
    cout << endl << "loading " << file << endl;
    Map* powergrid;
    try {
        powergrid = MapLoader2::load(file);
    } catch(BadMap& ex) {
        cout << ex.what() << endl;
        cout << "Ending..." << endl;
        return - 1;
    }
    int region;
    int i = 1;
    while(i < 3)
    {
        cout << "Player " << i << " select a region for play: ";
        cin >> region;
        powergrid->useRegion(region);
        i++;
    }
    if(powergrid->test()) {
        powergrid->finalize();
    } else {
        cout << "regions are not connected" << endl;
        return -1;
    }
    cout << *powergrid << endl;
    delete powergrid;
    return 0;
}

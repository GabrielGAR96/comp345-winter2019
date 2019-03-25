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
    Map* powergrid;
    bool loaded = false;
    do {
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
        try {
            powergrid = MapLoader2::load(file);
            loaded = true;
        } catch(BadMap& ex) {
            cout << ex.what() << endl << endl;
        }
    } while(!loaded);
    int numPlayers;
    do {
        cout << "How many players are there (2-6): ";
        cin >> numPlayers;
        if(numPlayers < 2 || numPlayers > 6) {
            cout << "Invalid number of players (" << numPlayers << ") selected" << endl << endl;
        }
    } while(numPlayers < 2 || numPlayers > 6);
    int region;
    bool validRegionsSelected = false;
    if(numPlayers < 6) {
        do {
            int i = 1;
            powergrid->clearRegions();
            while(i <= numPlayers)
            {
                cout << "Player " << i << " select a region for play: ";
                cin >> region;
                if(powergrid->getRegions().find(region) != powergrid->getRegions().end()) {
                    powergrid->useRegion(region);
                    i++;
                } else {
                    cout << "Region " << region << " has already been selected" << endl << endl;
                }
            }
            validRegionsSelected = powergrid->test();
            if(!validRegionsSelected) {
                cout << "Selected regions are not adjactent. Please try again" << endl << endl;
            }
        } while(!validRegionsSelected);
    } else {
        for(int i = 1; i <= 6; i++) {
            powergrid->useRegion(i);
        }
    }
    powergrid->finalize();
    cout << *powergrid << endl;
    delete powergrid;
    return 0;
}

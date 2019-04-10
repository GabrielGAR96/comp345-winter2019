#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

/* #include <boost/archive/text_oarchive.hpp> */

#include "Map.h"
#include "City.h"
#include "Graph.h"

void printCities(unordered_map<int, City> cities);

int main(int argc, char *argv[])
{
    UndirectedGraph<City> grid;

    string line;
    string name;
    int region;
    int i = 1;
    unordered_map<int, City> cities;
    cout << "input city names (blank line ends): " << endl;
    while(getline(cin, line) && !line.empty()) {
        int delim = line.find(":");
        name = line.substr(0, delim);
        region = stoi(line.substr(delim + 1, line.length()));
        City city(name, region);
        grid.addVertex(city);
        cities[i++] = city;
    }


    int source;
    int dest;
    double cost;
    while(true) {
        cout << "add connection" << endl;
        cout << "enter as [city_id1 city_id2 cost] (enter l to list cities and empty to end): ";
        getline(cin, line);
        if(line.empty()) break;
        if(line == "l") {
            printCities(cities);
        } else {
            int endSource = line.find(" ");
            source = stoi(line.substr(0, endSource));
            int endDest = line.find(" ", endSource + 1);
            dest = stoi(line.substr(endSource + 1, endDest));
            cost = stod(line.substr(endDest + 1, line.length()));
            grid.addEdge(cities[source], cities[dest], cost);
        }
    }

    Map powergrid(grid);

    string fname;
    cout << "enter filename for map: ";
    cin >> fname;

    ofstream output(fname);

    {
        boost::archive::text_oarchive ar(output);
        ar & powergrid;
    }
    return 0;
}

void printCities(unordered_map<int, City> cities)
{
    for(auto it = cities.begin(); it != cities.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
}

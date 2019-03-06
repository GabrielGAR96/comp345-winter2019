#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
using namespace std;

#include "Graph.h"
#include "Resource.h"
#include "City.h"
#include "Elektro.h"

class Map
{
    private:
        UndirectedGraph<City> powerGridMap;
        vector<Resource> resourcePool;
        Resource resourceMarket[14];
        int marketSize = 0;
        Elektro bank = 0;
    public:
        Map(UndirectedGraph<City> cities);
        void addElektroToBank(int amount);
        void addResourceToPool(Resource r);
        void addResourceToMarket(Resource r);
        void buyCity(City city, House house);
        unordered_set<City> getCities() const;
        bool isValid() const;
        string printMap() const;

    friend ostream& operator<<(ostream& out, const Map& m);
};

#endif

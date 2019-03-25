#ifndef MAP_H
#define MAP_H

#include <string>
using namespace std;

#include <boost/serialization/set.hpp>
using namespace boost::serialization;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Graph.h"
#include "Resource.h"
#include "ResourcePool.h"
#include "ResourceMarket.h"
#include "City.h"
#include "Elektro.h"

class Map
{
    private:
        // Data members

        UndirectedGraph<City> powergrid;
        ResourcePool pool;
        ResourceMarket market;
        Elektro bank = 0;

        set<int> activeRegions;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & powergrid;
            ar & pool;
            ar & market;
            ar & bank;
            /* ar & activeRegions; */
        }
    public:
        // Constructors

        Map();
        Map(UndirectedGraph<City> cities);

        // A map includes markets and pools we need to add tokens to these
        // areas
        void addElektroToBank(int amount);
        void addResourceToPool(Resource r, int n);
        void restockMarket(int numPlayers, int step);

        void useRegion(int region);
        set<int> getRegions() const;
        void clearRegions();
        bool test();
        void finalize();

        // We need to build Houses on cities
        // NOTE: Implementation might need some work
        // See: Note in UndirectedGraph<T> in Graph.h
        void buyCity(City city, House house);

        // Return cities that are on the board for use with purchasing
        unordered_set<City> getCities() const;
        // Wrapper around Graph::isConnected() see Graph.h for details
        bool isValid() const;
        // Return a string suitable for writing to save file
        string printMap() const;

    friend ostream& operator<<(ostream& out, const Map& m);
};

#endif

#ifndef MAP_H
#define MAP_H

/* #include <vector> */
#include <string>
using namespace std;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/vector.hpp>
/* using namespace boost::serialization; */

#include "Graph.h"
#include "Resource.h"
#include "City.h"
#include "Elektro.h"

class Map
{
    private:
        // Data members

        UndirectedGraph<City> powerGridMap;
        vector<Resource> resourcePool;
        Resource resourceMarket[14];
        int marketSize = 0;
        Elektro bank = 0;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & powerGridMap;
            ar & resourcePool;
            ar & resourceMarket;
            ar & marketSize;
            ar & bank;
        }
    public:
        // Constructors

        Map();
        Map(UndirectedGraph<City> cities);

        // A map includes markets and pools we need to add tokens to these
        // areas
        void addElektroToBank(int amount);
        void addResourceToPool(Resource r);
        void addResourceToMarket(Resource r);

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

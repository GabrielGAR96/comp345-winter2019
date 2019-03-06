#ifndef CITY_H
#define CITY_H

#include <string>
#include <ostream>
#include <functional>
#include <vector>
using namespace std;

#include "House.h"

// Forward declaration so we can hash
class City;

// Forward declaration for hash<> specialization
namespace std {
    template <> struct hash<City>
    {
        size_t operator()(const City& city) const;
    };
}

class City
{
    private:
        // Data memebers

        string name;
        int region=0;
        int numOccupants = 0;
        int buildingCost = 10;
        House houses[3];

    public:
        // Constructors

        City();
        City(const string& name, int region);

        // Accessor and mutator methods

        // return name
        string getName() const;
        // set name
        void setName(const string& name);
        // return region
        int getRegion() const;
        // set region
        void setRegion(const int region);
        // return all houses as a string for writing to file
        string getHouses() const;
        // build a House object and increase numOccupants and buildingCost
        bool build(House house);

        // Operators

        // Need theses for hashing
        bool operator<(const City& rhs) const;
        bool operator==(const City& rhs) const;

        // output Name and region
        friend ostream& operator<<(ostream& out, const City& rhs);
};

#endif

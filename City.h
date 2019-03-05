#ifndef CITY_H
#define CITY_H

#include <string>
#include <ostream>
#include <functional>
#include <vector>
using namespace std;

#include "House.h"

class City;
namespace std {
    template <> struct hash<City>
    {
        size_t operator()(const City& city) const;
    };
}

class City
{
    private:
        string name;
        int region=0;
        int numOccupants = 0;
        int buildingCost = 10;
        House houses[3];
    public:
        City();
        City(const string& name, int region);
        string getName() const;
        void setName(const string& name);
        int getRegion() const;
        void setRegion(const int region);
        bool build(House house);
        bool operator<(const City& rhs) const;
        bool operator==(const City& rhs) const;

        friend ostream& operator<<(ostream& out, const City& rhs);
};

#endif

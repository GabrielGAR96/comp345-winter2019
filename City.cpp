#include <string>
#include <ostream>
#include <functional>
using namespace std;

#include "City.h"
#include "HouseColor.h"
#include "House.h"
#include "Player.h"

City::City()
{
}

City::City(const string& name, int region)
    : name(name)
{
    setRegion(region);
}

string City::getName() const
{
    return name;
}

void City::setName(const string& name)
{
    this->name = name;
}

int City::getRegion() const
{
    return region;
}

void City::setRegion(int region)
{
    if(region < 1 || region > 6) return;
    this->region = region;
}

string City::getHouses() const
{
    string result = "";
    for(int i = 0; i < numOccupants; i++)
    {
        result.append("test");
    }
    return result;
}

bool City::build(House house)
{
    if(numOccupants < 3) {
        buildingCost += 5;
        houses[numOccupants++] = house;
        return true;
    }
    return false;
}

bool City::operator<(const City & rhs) const
{
    return this->name < rhs.name;
}

bool City::operator==(const City & rhs) const
{
    return this->name == rhs.name;
}

ostream& operator<<(ostream& out, const City & rhs)
{
    out << rhs.getName() << " " << rhs.getRegion() << " ";
    out << rhs.getHouses();
    return out;
}

namespace std {
    size_t hash<City>::operator()(const City & city) const
    {
        return hash<string>()(city.getName());
    }
}

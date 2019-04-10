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
    // There are a maximum of 6 regions on a map
    // TODO: Make this more robust (maybe return bool)
    if(region < 1 || region > 6) return;
    this->region = region;
}

string City::getHouses() const
{
    string result = "";
    // Loop over all Houses and append them to result
    for(int i = 0; i < numOccupants; i++)
    {
        // functions defined in Resource.h and House.h
        result.append(getHouseColorName(houses[i].getHouseColor()) + ":");
    }
    return result;
}

bool City::build(House house)
{
    // Only build if there are less than 3 occupants currently
    // Increase buildingCost by 5 when a House is built
    if(numOccupants < 3) {
        buildingCost += 5;
        houses[numOccupants++] = house;
        return true;
    }
    // Let us know if we can even do this if not we can indicate in caller
    return false;
}

int City::getNumOccupants() const
{
    return numOccupants;
}

int City::getPrice() const
{
    return buildingCost;
}

// City objects with the same name are equal
// Region doesn't matter as all names are unique
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

// Hash objects by there name
namespace std {
    size_t hash<City>::operator()(const City & city) const
    {
        return hash<string>()(city.getName());
    }
}

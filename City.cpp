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

bool City::build(Player player)
{
    if(numOccupants < 3) {
        buildingCost += 5;
        houses[numOccupants++] = House(getHouseColorByName(player.getColor()));
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
    out << rhs.getName();
    return out;
}

namespace std {
    size_t hash<City>::operator()(const City & city) const
    {
        return hash<string>()(city.getName());
    }
}

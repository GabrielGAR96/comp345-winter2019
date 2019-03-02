#include <iostream>
#include <string>
using namespace std;

#include "Resource.h"
#include "PowerplantCard.h"

PowerplantCard::PowerplantCard()
    : Card(CardType::POWERPLANT)
{
}

PowerplantCard::PowerplantCard(int name, int powerable, int needed)
    : Card(CardType::POWERPLANT), name(name), powerable(powerable), needed(needed)
{
}

PowerplantCard::PowerplantCard(int name, int powerable, int needed, Resource first)
    : PowerplantCard(name, powerable, needed)
{
    resourceTypes[0] = first;
    resourceTypesSize = 1;
}

PowerplantCard::PowerplantCard(int name, int powerable, int needed, Resource first, Resource second)
    : PowerplantCard(name, powerable, needed)
{
    resourceTypes[0] = first;
    resourceTypes[1] = second;
    resourceTypesSize = 2;
}

int PowerplantCard::getName() const
{
    return name;
}

int PowerplantCard::getPowerable() const
{
    return powerable;
}

bool PowerplantCard::store(const Resource r)
{
    if(!isValidToStore(r)) return false;
    resources.push_back(r);
    currentStored++;
    return true;
}

string PowerplantCard::getResources() const
{
    string res = "";
    for(Resource r : resources)
    {
        res.append(RESOURCE_NAMES.at(r) + " ");
    }

    return res;
}

string PowerplantCard::info() const
{
    string info = "";
    info.append("#: " + to_string(name) + "\n");
    if(needed)
    {
        info.append("uses: ");
        for(int i = 0; i < resourceTypesSize; i++)
        {
            info.append(RESOURCE_NAMES.at(resourceTypes[i]) + " ");
        }
        info.append("\n");
    } else {
        info.append("ecological\n");
    }
    info.append("stored: " + getResources() + "\n");
    info.append("req: " + to_string(needed) + "\n");
    info.append("cities: " + to_string(powerable));

    return info;
}

bool PowerplantCard::isValidToStore(const Resource r) const
{
    bool useable = false;
    for(int i = 0; i < resourceTypesSize; i++)
    {
        if(r == resourceTypes[i]) {
            useable = true;
            break;
        }
    }
    if(!useable) return false;
    if((currentStored + 1) > (needed * 2)) return false;
    return true;
}

bool PowerplantCard::operator==(const PowerplantCard& rhs) const
{
    return this->name == rhs.name;
}

ostream& operator<<(ostream& out, const PowerplantCard& c)
{
    out << c.info();
    return out;
}

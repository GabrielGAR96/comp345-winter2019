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
string PowerplantCard::getResource1(){
  return getResourceName(resourceTypes[0]);
}
string PowerplantCard::getResource2(){
  return getResourceName(resourceTypes[1]);
}
string PowerplantCard::getResources()
{

    string res = "";
    for(int i=0;i<resourceTypesSize;i++)
    {
        res.append(getResourceName(resourceTypes[i])+ " ");

    }

    return res;
}

string PowerplantCard::info() const
{
    string info = "";

    // Put name on its own line
    info.append("#: " + to_string(name) + "\n");

    // Only get useable resource types if a plant not ecological
    if(needed)
    {
        info.append("uses: ");
        for(int i = 0; i < resourceTypesSize; i++)
        {
            info.append(getResourceName(resourceTypes[i]) + " ");
        }
        info.append("\n");
    } else {
        info.append("ecological\n");
    }

    // How many resources are needed to power and number of cities on their own
    // lines
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

// Names are unique so it suffices to check name:int for equality
bool PowerplantCard::operator==(const PowerplantCard& rhs) const
{
  return this->name == rhs.name;
}

ostream& operator<<(ostream& out, const PowerplantCard& c)
{
    out << c.info();
    return out;
}

int PowerplantCard::getNeeded(){
  return this->needed;
}
int PowerplantCard::getCurrentStored(){
  return this->currentStored;
}
int PowerplantCard::getResourceTypeSize(){
  return resourceTypesSize;
}

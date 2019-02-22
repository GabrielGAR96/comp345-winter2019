#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


enum class Resource {COAL, OIL, GARBAGE, URANIUM};
const unordered_map<Resource, string> RESOURCE_NAMES = {{Resource::COAL, "coal"},
                                                        {Resource::OIL, "oil"},
                                                        {Resource::GARBAGE, "garbage"},
                                                        {Resource::URANIUM, "uranium"}};

class card
{
    private:
        int name;
        int powerable;
        int needed;
        int current_stored = 0;
        unordered_map<Resource, int> resources;
        bool validateStorage(Resource r, int amount) const;
    public:
        card(int name, int powerable, int needed);
        int getName() const;
        int getPowerable() const;
        void addResourceType(Resource r);
        bool store(Resource r, int amount);
        string getResources() const;

    friend ostream& operator<<(ostream& out, const card& c);
};

card::card(int name, int powerable, int needed)
    : name(name), powerable(powerable), needed(needed) {}

void card::addResourceType(Resource r)
{
    resources[r];
}

int card::getName() const
{
    return name;
}

int card::getPowerable() const
{
    return powerable;
}

bool card::store(Resource r, int amount)
{
    if(!validateStorage(r, amount)) return false;
    resources[r] += amount;
    current_stored += amount;
    return true;
}

string card::getResources() const
{
    string res = "";
    for(auto r : resources) {
        res.append(RESOURCE_NAMES.at(r.first));
        res.append(": ");
        res.append(to_string(r.second));
    }

    return res;
}

bool card::validateStorage(Resource r, int amount) const
{
    if(resources.find(r) == resources.end()) return false;
    if((current_stored + amount) > (needed * 2)) return false;
    return true;
}

#endif

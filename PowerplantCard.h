#ifndef POWERPLANTCARD_H
#define POWERPLANTCARD_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Card.h"
#include "Resource.h"

class PowerplantCard : public Card
{
    private:
        int name;
        int powerable;
        int needed;
        int currentStored = 0;
        Resource resourceTypes[2];
        int resourceTypesSize = 0;
        vector<Resource> resources;
        bool isValidToStore(const Resource r) const;
    public:
        PowerplantCard();
        PowerplantCard(int name, int powerable, int needed);
        PowerplantCard(int name, int powerable, int needed, Resource first);
        PowerplantCard(int name, int powerable, int needed, Resource first, Resource second);
        int getName() const;
        int getPowerable() const;
        bool store(const Resource r);
        string getResources() const;
        string info() const;

        bool operator==(const PowerplantCard& rhs) const;

    friend ostream& operator<<(ostream& out, const PowerplantCard& c);
};

#endif

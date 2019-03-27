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
        // Data members

        int name;
        int powerable;
        int needed;
        int currentStored = 0;
        Resource resourceTypes[2];
        int resourceTypesSize = 0;
        vector<Resource> resources;
        int R1=0;
        int R2=0;
        bool powering = false;
        // Helper Functions

        // Powerplants can only store certain kinds of resources and specific
        // amounts of them we need. This validates these contraints
        bool isValidToStore(const Resource r) const;
    public:
        // Constructors

        PowerplantCard();
        // Ecological
        PowerplantCard(int name, int powerable, int needed);
        // One resource card
        PowerplantCard(int name, int powerable, int needed, Resource first);
        // Two resource card
        PowerplantCard(int name, int powerable, int needed, Resource first, Resource second);

        // Accessors and mutators
        void setpowering(bool powering);
        bool getPowering();
        int getName() const;
        int getPowerable() const;
        bool store(const Resource r);
        string getResources();
        string getResource1();
        string getResource2();
        // toString() like method
        string info() const;
        int getNeeded();
        int getCurrentStored();
        int getResourceTypeSize();
        bool isPowerable();
        int power();

        void reducecurrentStored();
        bool operator==(const PowerplantCard& rhs) const;
        //friend string Player::getNameFromP();
        friend ostream& operator<<(ostream& out, const PowerplantCard& c);
        int getR1();
        int getR2();
        void reduceR1();
        void reduceR2();

};

#endif

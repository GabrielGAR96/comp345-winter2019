#ifndef DECK_H
#define DECK_H

#include <list>
#include <string>
using namespace std;

#include "Card.h"
#include "PowerplantCard.h"

class Deck
{
    private:
        list<Card*> deck;
        bool step3 = false;

        void shuffle(PowerplantCard deck[], int size);
    public:
        Deck();
        Deck(PowerplantCard deck[], int size, int ecoOnePos);

        Card* draw();
        bool step3Drawn();
        void setStep3Drawn(bool step3);
        string toString() const;
};

#endif

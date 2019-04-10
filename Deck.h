#ifndef DECK_H
#define DECK_H

#include <list>
#include <string>
using namespace std;

#include "Card.h"

class Deck
{
    private:
        list<Card*> deck;
        bool step3 = false;

    public:
        Deck();
        Deck(PowerplantCard deck[], int size, int ecoOnePos);

        void setDeck(PowerplantCard deck[], int size, int ecoOnePos, Step3Card& s3Card);

        Card* draw();
        bool step3Drawn();
        void setStep3Drawn(bool step3);
        string toString() const;

        static void shuffle(PowerplantCard deck[], int size);
};

#endif

#ifndef POWERPLANT_MARKET_H
#define POWERPLANT_MARKET_H

#include <string>
using namespace std;

#include "PowerplantCard.h"
#include "Deck.h"

class PowerplantMarket
{
    private:
        PowerplantCard market[8];

        void arrange();
    public:
        PowerplantMarket();
        PowerplantMarket(const PowerplantCard market[8]);

        PowerplantCard buy(const int index, Deck& deck);
        void addTo(const PowerplantCard& card);
        string toString() const;
};

#endif

#ifndef POWERPLANT_MARKET_H
#define POWERPLANT_MARKET_H

#include <string>
using namespace std;

#include "Card.h"
#include "Deck.h"

class PowerplantMarket
{
    private:
        PowerplantCard market[8];
        int currentlyAuctioning = -1;
        int currentBid = -1;

        void arrange();
    public:
        PowerplantMarket();
        PowerplantMarket(const PowerplantCard market[8]);

        void setMarket(const PowerplantCard market[8]);

        void setAuctioningCard(int selection);
        const PowerplantCard& getAuctioningCard() const;
        int getCurrentBid() const;
        void setCurrentBid(int bid);
        PowerplantCard buy(Deck& deck);
        string getActualMarket() const;
        string toString() const;
};

#endif

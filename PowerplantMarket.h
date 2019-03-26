#ifndef POWERPLANT_MARKET_H
#define POWERPLANT_MARKET_H

#include <string>
using namespace std;

#include <boost/serialization/priority_queue.hpp>

#include "PowerplantCard.h"

class PowerplantMarket
{
    private:
        PowerplantCard market[8];

        void arrange();
    public:
        PowerplantMarket();
        PowerplantMarket(const PowerplantCard market[8]);

        PowerplantCard remove(const int index, const Deck& deck);
        void addTo(const PowerplantCard& card);
        string toString() const;
};

#endif

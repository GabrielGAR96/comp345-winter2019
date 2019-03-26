#include <algorithm>
using namespace std;

#include "PowerplantMarket.h"

PowerplantMarket::PowerplantMarket()
{
}

PowerplantMarket::PowerplantMarket(const PowerplantCard market[8])
{
    for(int i = 0; i < 8; i++)
    {
        this->market[i] = market[i];
    }
    arrange();
}

void PowerplantMarket::arrange()
{
    sort(market, market+7);
}

PowerplantCard PowerplantMarket::remove(const int index, const Deck& deck)
{
    PowerplantCard card = market[index];
    market[index] = deck.draw();
    arrange();
    return card;
}

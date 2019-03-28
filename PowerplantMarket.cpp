#include <algorithm>
using namespace std;

#include "Card.h"
#include "PowerplantMarket.h"
#include "Deck.h"

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

PowerplantCard PowerplantMarket::buy(const int index, Deck& deck)
{
    PowerplantCard powerplant = market[index];
    Card* newCard = deck.draw();
    if(newCard->getType() == CardType::STEP3) {
        deck.setStep3Drawn(true);
        newCard = deck.draw();
    }
    PowerplantCard* newPowerplant = dynamic_cast<PowerplantCard*>(newCard);
    market[index] = *newPowerplant;
    arrange();
    return powerplant;
}

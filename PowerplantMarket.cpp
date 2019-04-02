#include <string>
#include <iostream>
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

void PowerplantMarket::setMarket(const PowerplantCard market[8])
{
    for(int i = 0; i < 8; i++)
    {
        this->market[i] = market[i];
    }
    arrange();
}

void PowerplantMarket::setAuctioningCard(int selection)
{
    currentlyAuctioning = selection;
    currentBid = market[selection].getName() - 1;
}

const PowerplantCard& PowerplantMarket::getAuctioningCard() const
{
    if(currentlyAuctioning == -1) {
        throw -1;
    }
    return market[currentlyAuctioning];
}

int PowerplantMarket::getCurrentBid() const
{
    return currentBid;
}

void PowerplantMarket::setCurrentBid(int bid)
{
    currentBid = bid;
}

PowerplantCard PowerplantMarket::buy(Deck& deck)
{
    PowerplantCard powerplant = market[currentlyAuctioning];

    Card* newCard = deck.draw();
    if(newCard->getType() == CardType::STEP3) {
        deck.setStep3Drawn(true);
        newCard = deck.draw();
    }
    PowerplantCard* newPowerplant = dynamic_cast<PowerplantCard*>(newCard);
    market[currentlyAuctioning] = *newPowerplant;
    currentlyAuctioning = -1;
    currentBid = -1;
    arrange();
    return powerplant;
}

string PowerplantMarket::getActualMarket() const
{
    string answer = "";
    for(int i = 0; i < 4; i++) {
        answer += market[i].info() + "\n";
    }
    return answer;
}

string PowerplantMarket::toString() const
{
    string answer = "";
    for(PowerplantCard card : market) {
        answer += card.info() + "\n";
    }
    return answer;
}

void PowerplantMarket::arrange()
{
    sort(market, market+7);
}

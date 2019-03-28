#include <list>
#include <string>
using namespace std;

#include "Card.h"
#include "PowerplantCard.h"
#include "Step3Card.h"
#include "Deck.h"

Deck::Deck()
{
}

Deck::Deck(PowerplantCard deck[], int size, int ecoOnePos)
{
    // First ecological Powerplant goes on top of the deck after shuffling so
    // let's remove it
    PowerplantCard ecoOne = deck[ecoOnePos];
    // The Step 3 card goes on the bottom of the deck after shuffling
    Step3Card s3Card;
    shuffle(deck, size);
    // Create a deck with a linked list
    for(int i = 0; i < size; i++)
    {
        // We actually shuffled card 13 into the deck anyway so don't add it
        // to the real deck
        if(deck[i] == ecoOne) continue;
        this->deck.push_back(&deck[i]);
    }
    // Add special cards to their special places
    this->deck.push_front(&ecoOne);
    this->deck.push_back(&s3Card);
}

void Deck::setDeck(list<Card*> deck)
{
    this->deck = deck;
}

Card* Deck::draw()
{
    Card* answer = deck.front();
    deck.pop_front();
    return answer;
}

bool Deck::step3Drawn()
{
    return step3;
}

void Deck::setStep3Drawn(bool step3)
{
    this->step3 = step3;
}

string Deck::toString() const
{
    string answer = "";
    for(Card* cPtr : deck)
    {
        if(cPtr->getType == CardType::Powerplant)
        answer += cPtr->info() + "\n\n";
    }
    return answer;
}

void Deck::shuffle(PowerplantCard deck[], int size)
{
    // Start at the bottom of the deck and swap cards to random locations
    // skipping positions that have already been swaped FROM
    int max = size - 1;
    while(max > 0) {
        int r = rand() % max ;
        PowerplantCard temp = deck[r];
        deck[r] = deck[max];
        deck[max--] = temp;
    }
}

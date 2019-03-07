#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <list>
using namespace std;

#include "Card.h"
#include "PowerplantCard.h"
#include "SummaryCard.h"
#include "Step3Card.h"
#include "Resource.h"

// Shuffle the deck according to Powergrid rules
void shuffle(PowerplantCard cards[], int size);

int main(int argc, char *argv[])
{
    // Seed randomness for shuffling
    srand(time(NULL));

    const int NUM_POWER_PLANTS = 42;
    const int MARKET_SIZE = 8;

    PowerplantCard cards[NUM_POWER_PLANTS];

    // We will read the definition of the cards from text... This is better than
    // hardcoding here
    fstream input;

    // Info from the text file will be stored here
    int name;
    string resources;
    int powerable;

    input.open("powerplants.txt");

    // Loop over lines of the text file to collect cards
    int i = 0;
    while(input >> name >> resources >> powerable)
    {
        PowerplantCard c;

        int needed = stoi(resources.substr(0, 1));

        // Skip if we read an ecological plant
        if(needed > 0)
        {
            string types[2];
            size_t size = 0;
            size_t start = 2;
            size_t end = resources.find(",");

            // Resources need some special parsing because a plant might use
            // more than one type of resource
            while(end != string::npos)
            {
                // Resource records are stored as:
                // resource1[:resource2]
                types[size++] = resources.substr(start, end - start);
                start = end + 1;
                end = resources.find(",", start);

            }

            types[size++] = resources.substr(start, end);

            // Did we find one resource or two
            if(size == 1) c = PowerplantCard(name, powerable, needed, getResourceByName(types[0]));

            else c = PowerplantCard(name, powerable, needed, getResourceByName(types[0]), getResourceByName(types[1]));

        } else {
            // Ecological card
            c = PowerplantCard(name, powerable, needed);
        }
        // Deck of only Powerplant cards
        cards[i++] = c;
    }

    // We're done
    input.close();

    // First 8 Powerplants get put in fixed size Market
    PowerplantCard market[8] = {cards[0], cards[1], cards[2], cards[3], cards[4], cards[5], cards[6], cards[7]};

    const int FULL_DECK_SIZE = NUM_POWER_PLANTS - MARKET_SIZE;

    // Get the remaining Powerplants for the deck
    PowerplantCard deckCards[FULL_DECK_SIZE];
    for(int i = 0; i < FULL_DECK_SIZE; i++)
    {
        deckCards[i] = cards[i + MARKET_SIZE];
    }

    // First ecological Powerplant goes on top of the deck after shuffling so
    // let's remove it
    PowerplantCard ecoOne = cards[10];

    // The Step 3 card goes on the bottom of the deck after shuffling
    Step3Card s3Card;

    // Shuffle the remaining deck cards
    shuffle(deckCards, FULL_DECK_SIZE);

    // Create a deck with a linked list
    list<Card*> deck;
    for(PowerplantCard& c: deckCards)
    {
        // We actually shuffled card 13 into the deck anyway so don't add it
        // to the real deck
        if(c == ecoOne) continue;
        deck.push_back(&c);
    }

    // Add special cards to their special places
    deck.push_front(&ecoOne);
    deck.push_back(&s3Card);

    // Print Market, Deck and SummaryCard for demonstration
    cout << "MARKET:" << endl;

    for(PowerplantCard& c : market)
    {
        cout << c.info() << endl << endl;
    }

    cout << endl << "DECK:" << endl;

    for(Card* cPtr : deck)
    {
        cout << cPtr->info() << endl << endl;
    }

    cout << endl << "SUMMARY:"<< endl;

    SummaryCard summary;
    cout << summary.info() << endl;

    return 0;
}

void shuffle(PowerplantCard cards[], int size)
{
    // Start at the bottom of the deck and swap cards to random locations
    // skipping positions that have already been swaped FROM
    int max = size - 1;
    while(max > 0) {
        int r = rand() % max ;
        PowerplantCard temp = cards[r];
        cards[r] = cards[max];
        cards[max--] = temp;
    }
}

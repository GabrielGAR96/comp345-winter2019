#include <string>
using namespace std;

#include "Step3Card.h"

Step3Card::Step3Card()
    : Card(CardType::STEP3)
{
}

// The only purpose of this card is to signal the third step of the game when it
// is drawn
string Step3Card::info() const
{
    return "STEP 3";
}

#include <string>
using namespace std;

#include "Step3Card.h"

Step3Card::Step3Card()
    : Card(CardType::STEP3)
{
}

string Step3Card::info() const
{
    return "STEP 3";
}

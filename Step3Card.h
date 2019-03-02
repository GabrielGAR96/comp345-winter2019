#ifndef STEP3CARD_H
#define STEP3CARD_H

#include <string>
using namespace std;

#include "Card.h"

class Step3Card : public Card
{
    public:
        Step3Card();
        string info() const;
};

#endif

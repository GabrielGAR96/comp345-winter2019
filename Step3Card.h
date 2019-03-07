#ifndef STEP3CARD_H
#define STEP3CARD_H

#include <string>
using namespace std;

#include "Card.h"

class Step3Card : public Card
{
    public:
        // Constructors

        Step3Card();

        // Simple toString() like method
        string info() const;
};

#endif

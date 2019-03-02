#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

enum class CardType {POWERPLANT, SUMMARY, STEP3};

class Card
{
    protected:
        CardType type;
    public:
        Card();
        Card(CardType type);
        virtual ~Card();
        virtual string info() const = 0;
        CardType getType() const;
};

#endif

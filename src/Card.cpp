#include "Card.h"

Card::Card()
{
}

Card::Card(CardType type)
    : type(type)
{
}

Card::~Card()
{
}

CardType Card::getType() const
{
    return type;
}

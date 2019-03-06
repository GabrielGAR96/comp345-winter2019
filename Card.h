#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

// So we can check easily for step 3 card... Other values for completeness
enum class CardType {POWERPLANT, SUMMARY, STEP3};

// Abstract Card class
class Card
{
    protected:
        CardType type;
    public:
        // Constructors

        Card();
        // Always call this from derived classes
        Card(CardType type);

        // Destructor

        virtual ~Card();

        // Accessors

        // Override in dervied classes
        // Should be a simple toString() like method
        virtual string info() const = 0;
        CardType getType() const;
};

#endif

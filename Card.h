#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

/* NOTE: All the card definitions should be here but I was thinking like a Java
 * programmer
 *
 * TODO: For Assignment 2 some minimal refactoring can reduce the number of
 * objects created and used as dependency if the above note is dealt with
 */

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

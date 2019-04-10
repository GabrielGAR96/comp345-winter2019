#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "Resource.h"

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


class PowerplantCard : public Card
{
    private:
        // Data members

        int name;
        int powerable;
        int needed;

        Resource uses;

    public:
        // Constructors

        PowerplantCard();
        // Ecological
        PowerplantCard(int name, int powerable, int needed);
        // Resource card
        PowerplantCard(int name, int powerable, int needed, Resource r);

        // Accessors and mutators
        int getName() const;
        int getPowerable() const;
        Resource getResourceType() const;
        // toString() like method
        string info() const;
        int getNeeded();

        bool operator==(const PowerplantCard& rhs) const;
        bool operator<(const PowerplantCard& rhs) const;
        friend ostream& operator<<(ostream& out, const PowerplantCard& c);
};

class SummaryCard : public Card
{
    private:
        // Data members

        const string TURN = "1. DETERMINE TURN ORDER\n"
                            "2. BUY POWER PLANT\n"
                            "   The first player begins.\n"
                            "   Per round, each may buy only one power plant.\n"
                            "3. BUY RAW MATERIALS\n"
                            "   The last player begins.\n"
                            "   Maximum double input per power plant.\n"
                            "4. BUILDING\n"
                            "   The last player begins.\n"
                            "5. BUREAUCRACY\n"
                            "   * Get money.\n"
                            "   * In phase 1 and 2: Place highest power plant under the stack.\n"
                            "   * In phase 3: Remove lowest power plant from the game.\n"
                            "   * Restock raw materials.";
        const int REWARD[21] = {10, 22, 33, 44, 54, 64, 73, 82,
                                90, 98, 105, 112, 118, 124, 129,
                                134, 138, 142, 145, 148, 150};
    public:
        // Constructors

        SummaryCard();

        // Simple toString() like method
        string info() const;

        SummaryCard& operator=(const SummaryCard& rhs);
};

class Step3Card : public Card
{
    public:
        // Constructors

        Step3Card();

        // Simple toString() like method
        string info() const;
};

#endif

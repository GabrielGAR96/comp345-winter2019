#ifndef SUMMARYCARD_H
#define SUMMARYCARD_H

#include <string>
using namespace std;

#include "Card.h"

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
};

#endif

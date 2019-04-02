#include <string>
using namespace std;

#include "SummaryCard.h"

SummaryCard::SummaryCard()
{
}

// Display the information exactly as presented on the summary card from the
// physical game in the format:
// <Front info with rules>
//
// <Back info with monetary rewards>
string SummaryCard::info() const
{
    string info = "";
    info.append("TURN\n");
    info.append(TURN);
    info.append("\n\n");
    for(int i = 0; i < 7; i++)
    {
        int stride = 0;
        while(stride <= 14) {
            info.append(to_string(i + stride) + ": " + to_string(REWARD[i + stride]) + "   ");
            stride += 7;
        }
        info.append("\n");
    }
    return info;
}

SummaryCard& SummaryCard::operator=(const SummaryCard& rhs)
{
    return *this;
}

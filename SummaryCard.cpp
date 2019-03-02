#include <string>
using namespace std;

#include "SummaryCard.h"

SummaryCard::SummaryCard()
{
}

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

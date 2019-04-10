#include <iostream>
#include <string>
using namespace std;

#include "Card.h"
#include "Resource.h"

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

PowerplantCard::PowerplantCard()
    : Card(CardType::POWERPLANT)
{
}

PowerplantCard::PowerplantCard(int name, int powerable, int needed)
    : Card(CardType::POWERPLANT), name(name), powerable(powerable), needed(needed)
{
}

PowerplantCard::PowerplantCard(int name, int powerable, int needed, Resource r)
    : PowerplantCard(name, powerable, needed)
{
    uses = r;
    /* switch(first) { */
    /*     case COALOIL: */
    /*         usesCoalOrOil = true; */
    /*         break; */
    /*     case COAL: */
    /*         usesCoal = true; */
    /*         break; */
    /*     case OIL: */
    /*         usesOil = true; */
    /*         break; */
    /*     case GARBAGE: */
    /*         usesGarbage = true; */
    /*         break; */
    /*     case URANIUM: */
    /*         usesUranium = true; */
    /*         break; */
    /* } */
}

int PowerplantCard::getName() const
{
    return name;
}

int PowerplantCard::getPowerable() const
{
    return powerable;
}

Resource PowerplantCard::getResourceType() const
{
    return uses;
}

string PowerplantCard::info() const
{
    string info = "";

    // Put name on its own line
    info.append("#: " + to_string(name) + "\n");

    // Only get useable resource types if a plant not ecological
    if(needed)
    {
        info.append(getResourceName(uses));
        info.append("\n");
    } else {
        info.append("ecological\n");
    }

    // How many resources are needed to power and number of cities on their own
    // lines
    info.append("req: " + to_string(needed) + "\n");
    info.append("cities: " + to_string(powerable));

    return info;
}

// Names are unique so it suffices to check name:int for equality
bool PowerplantCard::operator==(const PowerplantCard& rhs) const
{
  return this->name == rhs.name;
}

bool PowerplantCard::operator<(const PowerplantCard& rhs) const
{
    return this->name < rhs.name;
}

ostream& operator<<(ostream& out, const PowerplantCard& c)
{
    out << c.info();
    return out;
}

int PowerplantCard::getNeeded(){
  return this->needed;
}

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

Step3Card::Step3Card()
    : Card(CardType::STEP3)
{
}

// The only purpose of this card is to signal the third step of the game when it
// is drawn
string Step3Card::info() const
{
    return "STEP 3";
}

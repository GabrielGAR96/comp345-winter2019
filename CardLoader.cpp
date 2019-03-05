#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <list>
using namespace std;

#include "Card.h"
#include "PowerplantCard.h"
#include "SummaryCard.h"
#include "Step3Card.h"
#include "Resource.h"

void shuffle(PowerplantCard cards[], int size);
Resource getResourceByName(string r);


void shuffle(PowerplantCard cards[], int size)
{
    srand(time(NULL));
    int max = size - 1;
    while(max > 0) {
        int r = rand() % max ;
        PowerplantCard temp = cards[r];
        cards[r] = cards[max];
        cards[max--] = temp;
    }
}

Resource getResourceByName(string r)
{
    if(r == "coal") return COAL;
    if(r == "oil") return OIL;
    if(r == "garbage") return GARBAGE;
    if(r == "uranium") return URANIUM;
    return COAL; // keep compiler happy
}

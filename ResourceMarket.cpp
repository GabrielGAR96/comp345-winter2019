#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#include "ResourceMarket.h"
#include "Resource.h"
#include "ResourcePool.h"

                                                    // 2 players
const int ResourceMarket::RESTOCK_RULES[5][3][4] = {{{3, 2, 1, 1},  // Step 1
                                                     {4, 2, 2, 1},  // Step 2
                                                     {3, 4, 3, 1}}, // Step 3
                                                    // 3 players
                                                    {{4, 2, 1, 1},
                                                     {5, 3, 2, 1},
                                                     {3, 4, 3, 1}},
                                                    // 4 players
                                                    {{5, 3, 2, 1},
                                                     {6, 4, 3, 2},
                                                     {4, 5, 4, 2}},
                                                    // 5 players
                                                    {{5, 4, 3, 2},
                                                     {7, 5, 3, 3},
                                                     {5, 6, 5, 2}},
                                                    // 6 players
                                                    {{7, 5, 3, 2},
                                                     {9, 6, 5, 3},
                                                     {6, 7, 6, 3}}};

ResourceMarket::ResourceMarket()
{}

void ResourceMarket::initialize(ResourcePool& pool)
{
    amountCoal = min(24, pool.getAvailable(COAL));
    amountOil = min(18, pool.getAvailable(OIL));
    amountGarbage = min(6, pool.getAvailable(GARBAGE));
    amountUranium = min(2, pool.getAvailable(URANIUM));
    indexCoal = 24 - amountCoal;
    indexOil = 24 - amountOil;
    indexGarbage = 24 - amountGarbage;
    indexUranium = 12 - amountUranium;
    pool.getResourcesFromPool(COAL, amountCoal);
    pool.getResourcesFromPool(OIL, amountOil);
    pool.getResourcesFromPool(GARBAGE, amountGarbage);
    pool.getResourcesFromPool(URANIUM, amountUranium);
}

int ResourceMarket::getCheapest(Resource r) const
{
    switch(r)
    {
        case COAL:
            return (indexCoal / 3) + 1;
        case OIL:
            return (indexOil / 3) + 1;
        case GARBAGE:
            return (indexGarbage / 3) + 1;
        case URANIUM:
            if(indexUranium < 8) {
                return indexUranium + 1;
            } else {
                return indexUranium + 2 + (indexUranium % 8);
            }
    }
    throw invalid_argument("No such resource " + getResourceName(r));
}

Resource ResourceMarket::buy(Resource r)
{
    switch(r)
    {
        case COAL:
            if (amountCoal > 0) {
                amountCoal--;
                indexCoal++;
                return COAL;
            }
        case OIL:
            if (amountOil > 0) {
                amountOil--;
                indexOil++;
                return OIL;
            }
        case GARBAGE:
            if(amountGarbage > 0) {
                amountGarbage--;
                indexGarbage++;
                return GARBAGE;
            }
        case URANIUM:
            if(amountUranium > 0) {
                amountUranium--;
                indexUranium++;
                return URANIUM;
            }
    }
    throw invalid_argument("No such resource " + getResourceName(r));
}

void ResourceMarket::restock(ResourcePool& pool, int numPlayers, int step)
{
    int i = numPlayers - 2;
    int j = step - 1;
    int refillCoal = min(RESTOCK_RULES[i][j][0], pool.getAvailable(COAL));
    int refillOil = min(RESTOCK_RULES[i][j][1], pool.getAvailable(OIL));
    int refillGarbage = min(RESTOCK_RULES[i][j][2], pool.getAvailable(GARBAGE));
    int refillUranium = min(RESTOCK_RULES[i][j][3], pool.getAvailable(URANIUM));
    amountCoal += refillCoal;
    indexCoal -= refillCoal;
    amountOil += refillOil;
    indexOil -= refillOil;
    amountGarbage += refillGarbage;
    indexGarbage -= refillGarbage;
    amountUranium += refillGarbage;
    indexUranium -= refillUranium;

    pool.getResourcesFromPool(COAL, refillCoal);
    pool.getResourcesFromPool(OIL, refillOil);
    pool.getResourcesFromPool(GARBAGE, refillGarbage);
    pool.getResourcesFromPool(URANIUM, refillUranium);
}

int ResourceMarket::getAmount(Resource r) const
{
    switch(r)
    {
        case COAL:
            return amountCoal;
        case OIL:
            return amountOil;
        case GARBAGE:
            return amountGarbage;
        case URANIUM:
            return amountUranium;
    }
    throw invalid_argument("No such resource " + getResourceName(r));
}

string ResourceMarket::toString() const
{
    string answer = "Coal: " + to_string(amountCoal) + "Oil: " + to_string(amountOil) + "Garbage: " + to_string(amountGarbage) + "Uranium: " + to_string(amountUranium);
    return answer;

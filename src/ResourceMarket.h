#ifndef RESOURCE_MARKET_H
#define RESOURCE_MARKET_H

#include "Resource.h"
#include "ResourcePool.h"

class ResourceMarket
{
    private:
        static const int RESTOCK_RULES[5][3][4];
        int amountCoal;
        int amountOil;
        int amountGarbage;
        int amountUranium;
        int indexCoal;
        int indexOil;
        int indexGarbage;
        int indexUranium;
    public:
        ResourceMarket();
        ResourceMarket(ResourcePool pool);
        int getCheapest(Resource r);
        Resource buy(Resource r);
        void restock(ResourcePool pool, int numPlayers, int step);
};

#endif

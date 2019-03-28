#ifndef RESOURCE_MARKET_H
#define RESOURCE_MARKET_H

#include <string>
using namespace std;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & amountCoal;
            ar & amountOil;
            ar & amountGarbage;
            ar & amountUranium;
            ar & indexCoal;
            ar & indexOil;
            ar & indexGarbage;
            ar & indexUranium;
        }
    public:
        ResourceMarket();
        void initialize(ResourcePool& pool);
        int getCheapest(Resource r) const;
        Resource buy(Resource r);
        void restock(ResourcePool& pool, int numPlayers, int step);
        int getAmount(Resource r) const;
        string toString() const;
};

#endif

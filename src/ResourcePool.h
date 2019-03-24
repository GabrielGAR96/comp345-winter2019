#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Resource.h"

class ResourcePool
{
    private:
        int amountCoal;
        int amountOil;
        int amountGarbage;
        int amountUranium;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & amountCoal;
            ar & amountOil;
            ar & amountGarbage;
            ar & amountUranium;
        }
    public:
        ResourcePool();
        ResourcePool(int coal, int oil, int garbage, int uranium);
        bool getResourcesFromPool(Resource r, int n);
        int getAvailable(Resource r) const;
        void putBack(Resource r, int n);
};

#endif

#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include "Resource.h"

class ResourcePool
{
    private:
        int amountCoal;
        int amountOil;
        int amountGarbage;
        int amountUranium;
    public:
        ResourcePool();
        ResourcePool(int coal, int oil, int garbage, int uranium);
        bool getResourcesFromPool(Resource r, int n);
        int getAvailable(Resource r);
};

#endif

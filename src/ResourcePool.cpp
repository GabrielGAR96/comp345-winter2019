#include "ResourcePool.h"
#include "Resource.h"

ResourcePool::ResourcePool()
{
    ResourcePool(24, 24, 24, 12);
}

ResourcePool::ResourcePool(int coal, int oil, int garbage, int uranium)
{
    amountCoal = coal;
    amountOil = oil;
    amountGarbage = garbage;
    amountUranium = uranium;
}

bool ResourcePool::getResourcesFromPool(Resource r, int n)
{
    switch(r)
    {
        case COAL:
            if(amountCoal >= n) {
                amountCoal -= n;
                return true;
            }
        case OIL:
            if(amountOil >= n) {
                amountOil -= n;
                return true;
            }
        case GARBAGE:
            if(amountGarbage >= n) {
                amountGarbage -= n;
                return true;
            }
        case URANIUM:
            if(amountUranium >= n) {
                amountUranium -= n;
                return true;
            }
    }
    return false;
}

int ResourcePool::getAvailable(Resource r)
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
}

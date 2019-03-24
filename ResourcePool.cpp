#include <iostream>
using namespace std;

#include "ResourcePool.h"
#include "Resource.h"

ResourcePool::ResourcePool() :
    ResourcePool(24, 24, 24, 12) {}

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

int ResourcePool::getAvailable(Resource r) const
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

void ResourcePool::putBack(Resource r, int n)
{
    switch(r)
    {
        case COAL:
            amountCoal += n;
            break;
        case OIL:
            amountOil += n;
            break;
        case GARBAGE:
            amountGarbage += n;
            break;
        case URANIUM:
            amountUranium += n;
            break;
    }
}

//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-18.
//

#ifndef POWERGRID_RESOURCE_H
#define POWERGRID_RESOURCE_H

#include <string>
using std::string;

enum Resource {
    COAL, OIL, GARBAGE, URANIUM //restrict the value of the resource to one of those four
};

inline string getResourceName(Resource resource) { //get the string equivalent to the resource
    switch (resource) {
        case COAL:
            return "coal";
        case OIL:
            return "oil";
        case GARBAGE:
            return "garbage";
        case URANIUM:
            return "uranium";
        default:
            return "unknown";
    }
}

inline Resource getResourceByName(string r) //accessing the resource through a string
{
    if(r == "coal") return COAL;
    if(r == "oil") return OIL;
    if(r == "garbage") return GARBAGE;
    if(r == "uranium") return URANIUM;
    return COAL; // keep compiler happy
}

#endif //POWERGRID_RESOURCE_H

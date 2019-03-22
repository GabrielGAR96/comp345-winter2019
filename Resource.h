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

inline string getResourceName(Resource resource) { //function that gets the string equivalent to the resource
    switch (resource) {
        case COAL:
            return "COAL";
        case OIL:
            return "OIL";
        case GARBAGE:
            return "GARBAGE";
        case URANIUM:
            return "URANIUM";
        default:
            return "unknown";
    }
}

inline Resource getResourceByName(string r) //function that gets the resource through a string
{
    if(r == "COAL") return COAL;
    if(r == "OIL") return OIL;
    if(r == "GARBAGE") return GARBAGE;
    if(r == "URANIUM") return URANIUM;
     // keep compiler happy
}

#endif //POWERGRID_RESOURCE_H

//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-18.
//

#ifndef POWERGRID_RESOURCE_H
#define POWERGRID_RESOURCE_H

#include <string>
using std::string;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

enum Resource {
    COAL, OIL, GARBAGE, URANIUM //restrict the value of the resource to one of those four
};

namespace boost {
    namespace serialization {

        template<typename Archive>
        void serialize(Archive & ar, Resource & r, const unsigned int version)
        {
            ar & r;
        }

    }
}

inline string getResourceName(Resource resource) { //function that gets the string equivalent to the resource
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

inline Resource getResourceByName(string r) //function that gets the resource through a string
{
    if(r == "coal") return COAL;
    if(r == "oil") return OIL;
    if(r == "garbage") return GARBAGE;
    if(r == "uranium") return URANIUM;
    return COAL; // keep compiler happy
}

#endif //POWERGRID_RESOURCE_H

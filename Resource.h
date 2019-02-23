//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-18.
//

#ifndef POWERGRID_RESOURCE_H
#define POWERGRID_RESOURCE_H

#include <string>

using std::string;


enum Resource {
    COAL, OIL, GARBAGE, URANIUM
};

namespace res {
    const int total = 4;
}

inline string getResourceName (Resource resource) {
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

#endif //POWERGRID_RESOURCE_H

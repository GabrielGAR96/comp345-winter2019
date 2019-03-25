#include <fstream>
#include <string>
using namespace std;

#include <boost/archive/text_iarchive.hpp>

#include "MapLoader2.h"
#include "Map.h"

BadMap::BadMap(string msg)
    : logic_error(msg)
{}

Map* MapLoader2::load(string& fname)
{
    Map* powergrid = new Map();

    ifstream input(fname);

    {
        try {
            boost::archive::text_iarchive ar(input);
            ar >> *powergrid;
        } catch(boost::archive::archive_exception& ex) {
            throw BadMap("Cannont read " + fname + " because it is malformed");
        }
    }

    input.close();

    if(!powergrid->isValid()) {
        throw BadMap(fname + " represents a disconnected map");
    }

    return powergrid;
}

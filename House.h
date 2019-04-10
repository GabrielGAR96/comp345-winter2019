//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#ifndef POWERGRID_HOUSE_H
#define POWERGRID_HOUSE_H

#include <string>
using namespace std;

//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

#include "HouseColor.h"

class House{
private: //data members
    int price = 0;
    HouseColor houseColor;

  //  friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & houseColor;
    }

public:
    House();
    House(HouseColor houseColor); //constructors
    ~House(); //destructor

    int getPrice() const;
    HouseColor getHouseColor() const;
    void setPrice(int price); //getters and setters
};

#endif //POWERGRID_HOUSE_H

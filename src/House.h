//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#ifndef POWERGRID_HOUSE_H
#define POWERGRID_HOUSE_H

#include <string>
using namespace std;

#include "HouseColor.h"

class House{
private: //data members
    int price = 0; 
    HouseColor houseColor;

public: 
    House(); 
    House(HouseColor houseColor); //constructors
    ~House(); //destructor

    int getPrice() const;
    HouseColor getHouseColor() const;
    void setPrice(int price); //getters and setters
};

#endif //POWERGRID_HOUSE_H

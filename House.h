//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#ifndef POWERGRID_HOUSE_H
#define POWERGRID_HOUSE_H

#include <string>
using namespace std;

#include "HouseColor.h"

class House{
private:
    int price = 0;
    HouseColor houseColor;

public:
    House();
    House(HouseColor houseColor);
    ~House();

    int getPrice() const;
    HouseColor getHouseColor() const;
    void setPrice(int price);
};

#endif //POWERGRID_HOUSE_H

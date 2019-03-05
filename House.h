//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#ifndef POWERGRID_HOUSE_H
#define POWERGRID_HOUSE_H

#pragma once

#include "HouseColor.h"
#include <memory>

class House{
private:
    int price = 0;
    HouseColor houseColor;
    
public:
    House(HouseColor houseColor);
    ~House();

    int getPrice() const {return price;}
    std::shared_ptr<HouseColor> getHouseColorByName(string color) const {}
    void setPrice(int price) {this->price = price;}
};

#endif //POWERGRID_HOUSE_H

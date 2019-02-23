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
    std::shared_ptr<HouseColor> color;

public:
    House(std::shared_ptr<HouseColor> color);
    ~House();

    int getPrice() const {return price;}
    std::shared_ptr<HouseColor> GetColor() const {return color;}
    void setPrice(int price) {this->price = price;}
};

#endif //POWERGRID_HOUSE_H

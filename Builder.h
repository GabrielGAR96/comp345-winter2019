//
// Created by Gabriel Albuquerque Ribeiro on 2019-04-10.
//
#include "HouseBuilder.h"
#include "House.h"

#ifndef COMP345_WINTER2019_GOOD_BRANCH_BUILDER_H
#define COMP345_WINTER2019_GOOD_BRANCH_BUILDER_H

class Builder {
private:
    HouseBuilder* houseBuilder;
public:
    void setHouseBuilder(HouseBuilder* hb) {
        houseBuilder = hb;
    }
    House* getHouse(){
        return houseBuilder->getHouse();
    }
    void constructHouse(){
        houseBuilder->updatePrice();
    }
};

#endif //COMP345_WINTER2019_GOOD_BRANCH_BUILDER_H

//
// Created by Gabriel Albuquerque Ribeiro on 2019-04-09.
//

#ifndef COMP345_WINTER2019_GOOD_BRANCH_HOUSEDECORATOR_H
#define COMP345_WINTER2019_GOOD_BRANCH_HOUSEDECORATOR_H

#include "House.h"
#include "HouseColor.h"

class HouseBuilder : public House{
protected:
    House *builtHouse;
public:
    House* getHouse(){return builtHouse;}

    void createNewHouse(HouseColor color){builtHouse = new House(color);}

    virtual int getPrice() const {return builtHouse->getPrice();}

    virtual HouseColor getHouseColor() const{return builtHouse->getHouseColor();};

    virtual void updatePrice() = 0;
};

class FirstHouseBuilder : public HouseBuilder{
public:
    virtual void updatePrice(){builtHouse->setPrice(10);}
};


class SecondHouseBuilder : public HouseBuilder{
public:
    virtual void updatePrice(){builtHouse->setPrice(15);}
};


class ThirdHouseBuilder : public HouseBuilder{
public:
    virtual void updatePrice(){builtHouse->setPrice(20);}
};
#endif //COMP345_WINTER2019_GOOD_BRANCH_HOUSEDECORATOR_H

//
// Created by Gabriel Albuquerque Ribeiro on 2019-03-01.
//

#include "City.h"

bool City::addHouse(House *house) {
    if(houses.size() == MAX_HOUSES){
        return false;
    }
    houses.push_back(house);
    return true;
}

int City::getHousePrice() const {
    switch (houses.size())
    {
        case 0:
            return firstHousePrice;
        case 1:
            return secondHousePrice;
        case 2:
            return thirdHousePrice;
        default:
            return 0;
    }
}

bool City::isFull() const {
    return houses.size() == MAX_HOUSES;
}

bool City::isConnectedTo(string cityName) {
    for(auto connection = connections.begin(); connection != connections.end(); ++connection)
        if((*connection)->getFirst()->getName() == cityName || (*connection)->getSecond()->getName() == cityName)
            return true;
    return false;
}
//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#include <string>
using namespace std;

#include "House.h"
#include "HouseColor.h"

House::House() {}

House::House(HouseColor houseColor) : houseColor(houseColor) {}

House::~House() {}

int House::getPrice() const {return price;}
HouseColor getHouseColor() const {return houseColor;}
void House::setPrice(int price) {this->price = price;}

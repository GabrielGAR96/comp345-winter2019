//
// Created by Gabriel Albuquerque Ribeiro on 2019-04-10.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

#include "Player.h"
#include "PowerplantCard.h"
#include "HouseColor.h"
#include "Game.h"
#include "HouseBuilder.h"
#include "City.h"
#include "Builder.h"

int main(){

    Builder builder;

    FirstHouseBuilder* firstHouseBuilder = new FirstHouseBuilder();

    firstHouseBuilder->createNewHouse(RED);

    builder.setHouseBuilder(firstHouseBuilder);
    builder.constructHouse();

    House* house = builder.getHouse();

    cout << "House color: " << house->getHouseColor() << endl;
    cout << "Price: " << house->getPrice() << endl;

    City* detroit = new City("Detroit", 1);
    detroit->build(*house);
    cout << *detroit << endl;
    return 0;
}
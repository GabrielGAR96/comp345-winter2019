//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#ifndef POWERGRID_HOUSECOLOR_H
#define POWERGRID_HOUSECOLOR_H


#include <string>

using std::string;

enum HouseColor
{
    BLACK, BLUE, RED, YELLOW, GREEN, PURPLE
};

inline HouseColor getHouseColorByName(string name)
{
    HouseColor houseColor = BLACK; //default

    if (name == "black")
        houseColor = BLACK;
    else if (name == "blue")
        houseColor = BLUE;
    else if (name == "red")
        houseColor = RED;
    else if (name == "yellow")
        houseColor = YELLOW;
    else if(name == "green")
        houseColor = GREEN;
    else if(name == "purple")
        houseColor = PURPLE;

    return houseColor;
}

inline string getHouseColorName (HouseColor houseColor) {
    switch (houseColor) {
        case BLACK:
            return "black";
        case BLUE:
            return "blue";
        case RED:
            return "red";
        case YELLOW:
            return "yellow";
        case GREEN:
            return "green";
        case PURPLE:
            return "purple";
        default:
            return "unknown";
    }
}

#endif //POWERGRID_HOUSECOLOR_H

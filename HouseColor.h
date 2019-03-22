//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#ifndef POWERGRID_HOUSECOLOR_H
#define POWERGRID_HOUSECOLOR_H


#include <string>

using std::string;

enum HouseColor
{
    BLACK, BLUE, RED, YELLOW, GREEN, PURPLE //restrict the value of the house color to one of those six
};

inline HouseColor getHouseColorByName(string name) //function to get the house color by a string
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

inline string getHouseColorName (HouseColor houseColor) { //function to get the string equivalent to the house color
    switch (houseColor) {
        case BLACK:
            return "BLACK";
        case BLUE:
            return "BLUE";
        case RED:
            return "RED";
        case YELLOW:
            return "YELLOW";
        case GREEN:
            return "GREEN";
        case PURPLE:
            return "PURPLE";
        default:
            return "UNKNOWN";
    }
}

#endif //POWERGRID_HOUSECOLOR_H

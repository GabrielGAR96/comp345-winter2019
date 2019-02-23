//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-17.
//

#ifndef POWERGRID_HOUSECOLOR_H
#define POWERGRID_HOUSECOLOR_H


#include <string>

using std::string;


class HouseColor {
private:
    string name;
    string image;

public:
    HouseColor() {};
    HouseColor(string name, string image);
    string getName() const { return name; };
    string getImage() const { return image; };
    ~HouseColor();
};

#endif //POWERGRID_HOUSECOLOR_H

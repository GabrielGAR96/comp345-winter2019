//
// Created by Gabriel Albuquerque Ribeiro on 2019-03-01.
//
#pragma once
#ifndef POWERGRID_CITY_H
#define POWERGRID_CITY_H
#include "Connection.h"
#include "House.h"
#include <string>
#include <memory>
#include <vector>

using std::string;

class City
{
private:
    static const int MAX_HOUSES = 3;

    int firstHousePrice = 10;
    int secondHousePrice = 15;
    int thirdHousePrice = 20;

    string name = "";
    std::vector<std::shared_ptr<Connection>> connections;
    std::vector<House*> houses;

public:
    City() {}
    explicit City(string name) : name(name) {}

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        City::name = name;
    }

    std::vector<House*>& getHouses(){return houses;}
    int getNumberOfHouses()  {getHouses().size();}
    std::vector<std::shared_ptr<Connection>> const& getConnections() const { return getConnections();}

    void addConnection(std::shared_ptr<Connection> connection){connections.push_back(connection);}
    bool addHouse(House* house);

    int getHousePrice() const;
    bool isFull() const;
    bool isConnectedTo (string cityName);

};

#endif //POWERGRID_CITY_H

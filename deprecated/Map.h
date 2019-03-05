//
// Created by Gabriel Albuquerque Ribeiro on 2019-03-01.
//
#pragma once

#ifndef POWERGRID_MAP_H
#define POWERGRID_MAP_H

#include "City.h"
#include "Connection.h"
#include "Player.h"
#include <map>
#include <vector>

class Map
{
private:
    std::map<string, shared_ptr<City>> cities;
    vector<shared_ptr<Connection>> connections;

public:
    std::map<string, shared_ptr<City>> const& GetCities() const { return cities; }
    vector<shared_ptr<Connection>> const& GetConnections() const { return connections; }
    bool addConnection(shared_ptr<City> first, shared_ptr<City> second, int cost);

};

#endif //POWERGRID_MAP_H

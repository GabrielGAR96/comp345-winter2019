//
// Created by Gabriel Albuquerque Ribeiro on 2019-03-01.
//

#ifndef POWERGRID_CONNECTION_H
#define POWERGRID_CONNECTION_H

#include <memory>

class City;
class Connection
{
public:
    Connection(){}
    Connection(std::shared_ptr<City> firstCity, std::shared_ptr<City> secondCity, int cost){}

    const std::shared_ptr<City> &getFirst() const {
        return first;
    }

    void setFirst(const std::shared_ptr<City> &first) {
        Connection::first = first;
    }

    const std::shared_ptr<City> &getSecond() const {
        return second;
    }

    void setSecond(const std::shared_ptr<City> &second) {
        Connection::second = second;
    }

    int getCost() const {
        return cost;
    }

    void setCost(int cost) {
        Connection::cost = cost;
    }

   )
private:
    std::shared_ptr<City> first;
    std::shared_ptr<City> second;
    int cost = 0;


};

#endif //POWERGRID_CONNECTION_H

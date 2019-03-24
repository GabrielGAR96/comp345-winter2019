//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-18.
//
// This class simply implements the money (elektro) class and the elektro variable
// along with its getters and setters

#ifndef POWERGRID_ELEKTRO_H
#define POWERGRID_ELEKTRO_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Elektro{
private:
    int elektro;

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & elektro;
    }
public:
    Elektro(int elektro) : elektro(elektro) {}

    int getElektro() const {
        return elektro;
    }

    void setElektro(int elektro) {
        Elektro::elektro = elektro;
    }
};
#endif //POWERGRID_ELEKTRO_H

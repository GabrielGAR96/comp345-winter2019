//
// Created by Gabriel Albuquerque Ribeiro on 2019-02-18.
//

#ifndef POWERGRID_ELEKTRO_H
#define POWERGRID_ELEKTRO_H

class Elektro{
private:
    int elektro;

public:
	Elektro();
    Elektro(int elektro) : elektro(elektro) {}

    int getElektro() const {
        return elektro;
    }

    void setElektro(int elektro) {
        Elektro::elektro = elektro;
    }
};
#endif //POWERGRID_ELEKTRO_H

#ifndef EQUATIONS_H
#define EQUATIONS_H


#include "Equation.h"
#include "../Convection/ConvectionS.h"
#include "../Location/LocationS.h"


class EquationS : public Equation<LocationS, ConvectionS> {

public:

    EquationS(GetFromFile &dataFilePar, LocationS &locatePar, ConvectionS &convectPar, Grid &grdPar,
              std::vector<std::vector<double>> &pPar,
              std::vector<std::vector<double>> &SPar) : Equation(dataFilePar, locatePar, convectPar, grdPar, pPar, SPar) {}

    virtual ~EquationS() {}


private:

    void calcСoefficients() {

        convect.calcСoefficients(P[(index + 1) % 2], S[index]);

        locate.setPNew(P[(index + 1) % 2]);

        locate.calcСoefficients(P[index], S[index]);

    }


public:

    void solve(const int &indexPar) {

        index = indexPar;

        aggregateСoefficients();

        calcVar(S[(index + 1) % 2], S[index]);

    }

};


#endif

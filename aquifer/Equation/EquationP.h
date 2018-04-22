#ifndef EQUATIONP_H
#define EQUATIONP_H


#include "Equation.h"
#include "../Convection/ConvectionP.h"
#include "../Location/LocationP.h"


class EquationP : public Equation<LocationP, ConvectionP> {

public:

    EquationP(GetFromFile &dataFilePar, LocationP &locatePar, ConvectionP &convectPar, Grid &grdPar,
              std::vector<std::vector<double>> &PPar,
              std::vector<std::vector<double>> &SPar) : Equation(dataFilePar, locatePar, convectPar, grdPar, PPar, SPar) {}

    virtual ~EquationP() {}


private:

    void calcСoefficients() {

        convect.calcСoefficients(P[index], S[index]);

        locate.calcСoefficients(P[index], S[index]);
    }


public:

    void solve(const int &indexPar) {

        index = indexPar;

        aggregateСoefficients();

        calcVar(P[(index + 1) % 2], P[index]);

    }

};


#endif

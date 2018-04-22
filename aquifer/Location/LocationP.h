#ifndef LOCATIONP_H
#define LOCATIONP_H

#include "Location.h"


class LocationP : public Location {

public:

    LocationP(Grid &grdPar, FuncPars &fPPar, double &timeStepPar, GetFromFile &dataFilePar);

    virtual ~LocationP();


    double getQ1prod();

    double getQ2prod();


private:

    void calcAlpha();


    void defineVar();


    void calcAF();

    void calcAC();

};


#endif

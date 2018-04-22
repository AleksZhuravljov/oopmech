#ifndef LOCATIONS_H
#define LOCATIONS_H

#include "Location.h"


class LocationS : public Location {

public:

    LocationS(Grid &grdPar, FuncPars &fPPar, double &timeStepPar, GetFromFile &dataFilePar);

    virtual ~LocationS();

    void setPNew(const std::vector<double> &PNewPar);


private:

    std::vector<double> PNew;


    void calcAlpha();


    void defineVar();


    void calcAF();

    void calcAC();

};


#endif

#ifndef CONVECTION_H
#define CONVECTION_H

#include "ConvectionPars.h"


class Convection : public ConvectionPars {


public:

    Convection(Grid &grdPar, FuncPars &fPPar, GetFromFile &dataFilePar);

    virtual ~Convection();


    std::string schemeEqName;

    std::string schemeType;

    std::string schemeName;

    bool implicitFlag;


protected:

    GetFromFile &dataFile;


    int dimCell;


public:


    std::vector<double> aF;

    std::vector<double> aC;

    std::vector<double> aR;

    std::vector<double> aL;

    std::vector<double> aT;

    std::vector<double> aB;


private:

    void defineSchemeType();


protected:

    std::vector<double> divergence;

    virtual void calcDivergence() {}


    virtual void calcA() {}


public:

    void calcСoefficients(const std::vector<double> &PPar, const std::vector<double> &SPar);

};


#endif
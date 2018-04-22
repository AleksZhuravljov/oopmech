#ifndef LOCATION_H
#define LOCATION_H


#include <vector>


#include "../States/Grid.h"
#include "../States/FuncPars.h"


class Location {

public:

    Location(Grid &grdPar, FuncPars &fPPar, double &timeStepPar, GetFromFile &dataFilePar);

    virtual ~Location();


protected:

    Grid &grd;


    FuncPars &fP;


    GetFromFile &dataFile;


    std::string schemeEqName;

    std::string schemeType;

    std::string schemeName;

    bool implicitFlag;

    void setSchemeType();


    int dimCell;


    int prodCellIndex;


    double Q1prod;

    double Q2prod;

    double Vprod;


    void calcQ();

    std::vector<double> alpha;

    virtual void calcAlpha() {};


    std::vector<double> var;

    virtual void defineVar() {};


    double &timeStep;


    std::vector<double> P;

    std::vector<double> S;


    virtual void calcAF() {}


    virtual void calcAC() {}


public:

    double r1Std;

    double r2Std;


    std::vector<double> aF;

    std::vector<double> aC;


    void calcСoefficients(const std::vector<double> &PPar, const std::vector<double> &SPar);

};


#endif

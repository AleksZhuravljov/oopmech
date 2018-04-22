#ifndef CONVECTIONPARS_H
#define CONVECTIONPARS_H


#include <vector>


#include "../States/Grid.h"
#include "../States/FuncPars.h"


class ConvectionPars {

public:

    ConvectionPars(Grid &grdPar, FuncPars &fPPar);

    virtual ~ConvectionPars();


protected:

    Grid &grd;


    FuncPars &fP;


    std::vector<double> P;

    std::vector<double> S;


    int dimSurfX;

    int dimSurfY;


    std::vector<double> nablaPX;

    std::vector<double> nablaPY;


    std::vector<double> SX;

    std::vector<double> SY;


    std::vector<double> PX;

    std::vector<double> PY;


    std::vector<double> epsilon1X;

    std::vector<double> epsilon1Y;

    std::vector<double> epsilon2X;

    std::vector<double> epsilon2Y;


    std::vector<double> k1X;

    std::vector<double> k1Y;

    std::vector<double> K1X;

    std::vector<double> K1Y;


    std::vector<double> k2X;

    std::vector<double> k2Y;

    std::vector<double> K2X;

    std::vector<double> K2Y;


private:

    void calcNablaPX();

    void calcNablaPY();


    void calcSX();

    void calcSY();


    void calcPX();

    void calcPY();


    void calcEpsilonX();

    void calcEpsilonY();


    void calckXKX();

    void calckYKY();


protected:

    virtual void calcOtherPars() {}


    void calcPars();

};


#endif
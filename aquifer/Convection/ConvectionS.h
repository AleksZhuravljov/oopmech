#ifndef CONVECTIONS_H
#define CONVECTIONS_H


#include "Convection.h"


class ConvectionS : public Convection {

public:

    ConvectionS(Grid &grdPar, FuncPars &fPPar, GetFromFile &dataFilePar);

    virtual ~ConvectionS();


private:

    std::vector<double> gammaX;

    std::vector<double> gammaY;

    void calcGammaX();

    void calcGammaY();


    std::vector<double> deltaX;

    std::vector<double> deltaY;

    void calcDeltaX();

    void calcDeltaY();


    void calcOtherPars();


    std::vector<double> flux1ExplX;

    std::vector<double> flux1ExplY;


    void calcfluxExplX();

    void calcfluxExplY();


    void calcDivergence();


    std::vector<double> a1SurfXR;

    std::vector<double> a1SurfXL;

    std::vector<double> a1SurfXF;


    std::vector<double> a1SurfYT;

    std::vector<double> a1SurfYB;

    std::vector<double> a1SurfYF;


    void calcASurfX();

    void calcASurfY();


    void calcA();

};


#endif

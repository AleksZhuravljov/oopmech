#ifndef CONVECTIONP_H
#define CONVECTIONP_H


#include "Convection.h"


class ConvectionP : public Convection {

public:

    ConvectionP(Grid &grdPar, FuncPars &fPPar, GetFromFile &dataFilePar);

    virtual ~ConvectionP();


private:


    std::vector<double> beta1X;

    std::vector<double> beta2X;

    std::vector<double> beta1Y;

    std::vector<double> beta2Y;


    void calcBetaX();

    void calcBetaY();


    void calcOtherPars();


    std::vector<double> flux1ExplX;

    std::vector<double> flux1ExplY;


    std::vector<double> flux2ExplX;

    std::vector<double> flux2ExplY;


    void calcfluxExplX();

    void calcfluxExplY();


    void calcDivergence();


    std::vector<double> a1SurfXR;

    std::vector<double> a1SurfXL;

    std::vector<double> a1SurfXF;


    std::vector<double> a1SurfYT;

    std::vector<double> a1SurfYB;

    std::vector<double> a1SurfYF;


    std::vector<double> a2SurfXR;

    std::vector<double> a2SurfXL;

    std::vector<double> a2SurfXF;


    std::vector<double> a2SurfYT;

    std::vector<double> a2SurfYB;

    std::vector<double> a2SurfYF;


    void calcASurfX();

    void calcASurfY();


    void calcA();


};


#endif

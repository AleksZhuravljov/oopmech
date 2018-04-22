#include "ConvectionS.h"

ConvectionS::ConvectionS(Grid &grdPar, FuncPars &fPPar,
                         GetFromFile &dataFilePar) : Convection(grdPar, fPPar, dataFilePar),
                                                     gammaX(dimSurfX, 0), gammaY(dimSurfY, 0),
                                                     deltaX(dimSurfX, 0), deltaY(dimSurfY, 0),
                                                     flux1ExplX(dimSurfX, 0),
                                                     flux1ExplY(dimSurfY, 0),
                                                     a1SurfXR(dimSurfX, 0),
                                                     a1SurfXL(dimSurfX, 0),
                                                     a1SurfXF(dimSurfX, 0),
                                                     a1SurfYT(dimSurfY, 0),
                                                     a1SurfYB(dimSurfY, 0),
                                                     a1SurfYF(dimSurfY, 0) {

    schemeEqName = "SCHEME_S";

}

ConvectionS::~ConvectionS() {}


void ConvectionS::calcGammaX() {
    for (int i = 0; i < dimSurfX; i++)
        gammaX[i] = epsilon1X[i] * K1X[i] * nablaPX[i] * grd.surfsXOMEGA[i];
}

void ConvectionS::calcGammaY() {
    for (int i = 0; i < dimSurfY; i++)
        gammaY[i] = epsilon1Y[i] * K1Y[i] * nablaPY[i] * grd.surfsYOMEGA[i];
}


void ConvectionS::calcDeltaX() {
    for (int i = 0; i < dimSurfX; i++)
        deltaX[i] = epsilon1X[i] * k1X[i] * nablaPX[i] * grd.surfsXOMEGA[i];
}

void ConvectionS::calcDeltaY() {
    for (int i = 0; i < dimSurfY; i++)
        deltaY[i] = epsilon1Y[i] * k1Y[i] * nablaPY[i] * grd.surfsYOMEGA[i];
}


void ConvectionS::calcOtherPars() {

    calcGammaX();

    calcGammaY();


    calcDeltaX();

    calcDeltaY();

}


void ConvectionS::calcfluxExplX() {
    for (int i = 0; i < dimSurfX; i++)
        flux1ExplX[i] = deltaX[i];
}

void ConvectionS::calcfluxExplY() {
    for (int i = 0; i < dimSurfY; i++)
        flux1ExplY[i] = deltaY[i];
}


void ConvectionS::calcDivergence() {

    calcfluxExplX();
    calcfluxExplY();


    for (int i = 0; i < dimCell; i++)
        divergence[i] = flux1ExplX[grd.iSurfXR(i)] - flux1ExplX[grd.iSurfXL(i)] + flux1ExplY[grd.iSurfYT(i)] - flux1ExplY[grd.iSurfYB(i)];

}


void ConvectionS::calcASurfX() {

    for (int i = 0; i < dimSurfX; i++) {

        a1SurfXR[i] = gammaX[i] / 2.;
        a1SurfXL[i] = gammaX[i] / 2.;
        a1SurfXF[i] = deltaX[i] - gammaX[i] * SX[i];

    }

}

void ConvectionS::calcASurfY() {

    for (int i = 0; i < dimSurfY; i++) {

        a1SurfYT[i] = gammaY[i] / 2.;
        a1SurfYB[i] = gammaY[i] / 2.;
        a1SurfYF[i] = deltaY[i] - gammaY[i] * SY[i];

    }
}


void ConvectionS::calcA() {

    if (implicitFlag == false)

        for (int i = 0; i < dimCell; i++) {

            aF[i] = divergence[i];
            aC[i] = 0;
            aR[i] = 0;
            aL[i] = 0;
            aT[i] = 0;
            aB[i] = 0;

        }

    else {

        calcASurfX();
        calcASurfY();

        for (int i = 0; i < grd.cellsX.size(); i++) {

            aF[i] = a1SurfXF[grd.iSurfXR(i)] - a1SurfXF[grd.iSurfXL(i)] + a1SurfYF[grd.iSurfYT(i)] - a1SurfYF[grd.iSurfYB(i)];
            aC[i] = a1SurfXL[grd.iSurfXR(i)] - a1SurfXR[grd.iSurfXL(i)] + a1SurfYB[grd.iSurfYT(i)] - a1SurfYT[grd.iSurfYB(i)];
            aR[i] = a1SurfXR[grd.iSurfXR(i)];
            aL[i] = -a1SurfXL[grd.iSurfXL(i)];
            aT[i] = a1SurfYT[grd.iSurfYT(i)];
            aB[i] = -a1SurfYB[grd.iSurfYB(i)];

        }

    }

}



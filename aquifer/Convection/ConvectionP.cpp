#include "ConvectionP.h"

ConvectionP::ConvectionP(Grid &grdPar, FuncPars &fPPar, GetFromFile &dataFilePar) : Convection(grdPar, fPPar, dataFilePar),
                                                                                    beta1X(dimSurfX, 0), beta2X(dimSurfX, 0),
                                                                                    beta1Y(dimSurfY, 0), beta2Y(dimSurfY, 0),
                                                                                    flux1ExplX(dimSurfX, 0),
                                                                                    flux1ExplY(dimSurfY, 0),
                                                                                    flux2ExplX(dimSurfX, 0),
                                                                                    flux2ExplY(dimSurfY, 0),
                                                                                    a1SurfXR(dimSurfX, 0),
                                                                                    a1SurfXL(dimSurfX, 0),
                                                                                    a1SurfXF(dimSurfX, 0),
                                                                                    a1SurfYT(dimSurfY, 0),
                                                                                    a1SurfYB(dimSurfY, 0),
                                                                                    a1SurfYF(dimSurfY, 0),
                                                                                    a2SurfXR(dimSurfX, 0),
                                                                                    a2SurfXL(dimSurfX, 0),
                                                                                    a2SurfXF(dimSurfX, 0),
                                                                                    a2SurfYT(dimSurfY, 0),
                                                                                    a2SurfYB(dimSurfY, 0),
                                                                                    a2SurfYF(dimSurfY, 0) {

    schemeEqName = "SCHEME_P";

}

ConvectionP::~ConvectionP() {}


void ConvectionP::calcBetaX() {

    for (int i = 0; i < dimSurfX; i++) {

        beta1X[i] = epsilon1X[i] * k1X[i] * grd.surfsXOMEGA[i];

        beta2X[i] = epsilon2X[i] * k2X[i] * grd.surfsXOMEGA[i];

    }

}

void ConvectionP::calcBetaY() {

    for (int i = 0; i < dimSurfY; i++) {

        beta1Y[i] = epsilon1Y[i] * k1Y[i] * grd.surfsYOMEGA[i];

        beta2Y[i] = epsilon2Y[i] * k2Y[i] * grd.surfsYOMEGA[i];

    }

}


void ConvectionP::calcOtherPars() {

    calcBetaX();

    calcBetaY();

}


void ConvectionP::calcfluxExplX() {

    for (int i = 0; i < dimSurfX; i++) {

        flux1ExplX[i] = beta1X[i] * nablaPX[i];

        flux2ExplX[i] = beta2X[i] * nablaPX[i];

    }

}

void ConvectionP::calcfluxExplY() {

    for (int i = 0; i < dimSurfY; i++) {

        flux1ExplY[i] = beta1Y[i] * nablaPY[i];

        flux2ExplY[i] = beta2Y[i] * nablaPY[i];

    }

}


void ConvectionP::calcDivergence() {

    calcfluxExplX();

    calcfluxExplY();


    for (int i = 0; i < dimCell; i++)

        divergence[i] = (flux1ExplX[grd.iSurfXR(i)] - flux1ExplX[grd.iSurfXL(i)] + flux1ExplY[grd.iSurfYT(i)] - flux1ExplY[grd.iSurfYB(i)]) /
                        fP.r1(P[i]) +
                        (flux2ExplX[grd.iSurfXR(i)] - flux2ExplX[grd.iSurfXL(i)] + flux2ExplY[grd.iSurfYT(i)] - flux2ExplY[grd.iSurfYB(i)]) /
                        fP.r2(P[i]);

}


void ConvectionP::calcASurfX() {

    for (int i = 0; i < dimSurfX; i++) {

        a1SurfXR[i] = -beta1X[i] / grd.surfsXL[i];

        a1SurfXL[i] = beta1X[i] / grd.surfsXL[i];

        a1SurfXF[i] = 0;


        a2SurfXR[i] = -beta2X[i] / grd.surfsXL[i];

        a2SurfXL[i] = beta2X[i] / grd.surfsXL[i];

        a2SurfXF[i] = 0;

    }

}

void ConvectionP::calcASurfY() {

    for (int i = 0; i < dimSurfY; i++) {

        a1SurfYT[i] = -beta1Y[i] / grd.surfsYL[i];

        a1SurfYB[i] = beta1Y[i] / grd.surfsYL[i];

        a1SurfYF[i] = 0;


        a2SurfYT[i] = -beta2Y[i] / grd.surfsYL[i];

        a2SurfYB[i] = beta2Y[i] / grd.surfsYL[i];

        a2SurfYF[i] = 0;

    }
}


void ConvectionP::calcA() {

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

            aF[i] = (a1SurfXF[grd.iSurfXR(i)] - a1SurfXF[grd.iSurfXL(i)] + a1SurfYF[grd.iSurfYT(i)] - a1SurfYF[grd.iSurfYB(i)]) / fP.r1(P[i]) +
                    (a2SurfXF[grd.iSurfXR(i)] - a2SurfXF[grd.iSurfXL(i)] + a2SurfYF[grd.iSurfYT(i)] - a2SurfYF[grd.iSurfYB(i)]) / fP.r2(P[i]);

            aC[i] = (a1SurfXL[grd.iSurfXR(i)] - a1SurfXR[grd.iSurfXL(i)] + a1SurfYB[grd.iSurfYT(i)] - a1SurfYT[grd.iSurfYB(i)]) / fP.r1(P[i]) +
                    (a2SurfXL[grd.iSurfXR(i)] - a2SurfXR[grd.iSurfXL(i)] + a2SurfYB[grd.iSurfYT(i)] - a2SurfYT[grd.iSurfYB(i)]) / fP.r2(P[i]);

            aR[i] = a1SurfXR[grd.iSurfXR(i)] / fP.r1(P[i]) +
                    a2SurfXR[grd.iSurfXR(i)] / fP.r2(P[i]);

            aL[i] = -a1SurfXL[grd.iSurfXL(i)] / fP.r1(P[i]) -
                    a2SurfXL[grd.iSurfXL(i)] / fP.r2(P[i]);

            aT[i] = a1SurfYT[grd.iSurfYT(i)] / fP.r1(P[i]) +
                    a2SurfYT[grd.iSurfYT(i)] / fP.r2(P[i]);

            aB[i] = -a1SurfYB[grd.iSurfYB(i)] / fP.r1(P[i]) -
                    a2SurfYB[grd.iSurfYB(i)] / fP.r2(P[i]);

        }

    }

}



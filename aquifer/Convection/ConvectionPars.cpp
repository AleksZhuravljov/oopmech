#include "ConvectionPars.h"


ConvectionPars::ConvectionPars(Grid &grdPar, FuncPars &fPPar) : grd(grdPar),
                                                                fP(fPPar),
                                                                dimSurfX(grdPar.surfsXOMEGA.size()),
                                                                dimSurfY(grdPar.surfsYOMEGA.size()),
                                                                nablaPX(dimSurfX, 0),
                                                                nablaPY(dimSurfY, 0),
                                                                SX(dimSurfX, 0), SY(dimSurfY, 0),
                                                                PX(dimSurfX, 0), PY(dimSurfY, 0),
                                                                epsilon1X(dimSurfX, 0), epsilon1Y(dimSurfY, 0),
                                                                epsilon2X(dimSurfX, 0), epsilon2Y(dimSurfY, 0),
                                                                k1X(dimSurfX, 0), k1Y(dimSurfY, 0),
                                                                K1X(dimSurfX, 0), K1Y(dimSurfY, 0),
                                                                k2X(dimSurfX, 0), k2Y(dimSurfY, 0),
                                                                K2X(dimSurfX, 0), K2Y(dimSurfY, 0) {}

ConvectionPars::~ConvectionPars() {}


void ConvectionPars::calcNablaPX() {

    for (int i = 0; i < dimSurfX; i++)
        if (i % grd.surfsXNumX == 0 || (i + 1) % grd.surfsXNumX == 0)
            nablaPX[i] = 0;
        else
            nablaPX[i] = (P[grd.iCellXL(i)] - P[grd.iCellXR(i)]) / grd.surfsXL[i];

}

void ConvectionPars::calcNablaPY() {

    for (int i = 0; i < dimSurfY; i++)
        if (i < grd.surfsYNumX || i >= grd.surfsYNumX * (grd.surfsYNumY - 1))
            nablaPY[i] = 0;
        else
            nablaPY[i] = (P[grd.iCellYB(i)] - P[grd.iCellYT(i)]) / grd.surfsYL[i];

}


void ConvectionPars::calcSX() {

    for (int i = 0; i < dimSurfX; i++)
        if (i % grd.surfsXNumX == 0)
            SX[i] = S[grd.iCellXR(i)];
        else if ((i + 1) % grd.surfsXNumX == 0)
            SX[i] = S[grd.iCellXL(i)];
        else
            SX[i] = (S[grd.iCellXR(i)] + S[grd.iCellXL(i)]) / 2;

}

void ConvectionPars::calcSY() {

    for (int i = 0; i < dimSurfY; i++)
        if (i < grd.surfsYNumX)
            SY[i] = S[grd.iCellYT(i)];
        else if (i >= grd.surfsYNumX * (grd.surfsYNumY - 1))
            SY[i] = S[grd.iCellYB(i)];
        else
            SY[i] = (S[grd.iCellYT(i)] + S[grd.iCellYB(i)]) / 2;

}


void ConvectionPars::calcPX() {

    for (int i = 0; i < dimSurfX; i++)
        if (i % grd.surfsXNumX == 0)
            PX[i] = P[grd.iCellXR(i)];
        else if ((i + 1) % grd.surfsXNumX == 0)
            PX[i] = P[grd.iCellXL(i)];
        else
            PX[i] = (P[grd.iCellXR(i)] + P[grd.iCellXL(i)]) / 2;

}

void ConvectionPars::calcPY() {

    for (int i = 0; i < dimSurfY; i++)
        if (i < grd.surfsYNumX)
            PY[i] = P[grd.iCellYT(i)];
        else if (i >= grd.surfsYNumX * (grd.surfsYNumY - 1))
            PY[i] = P[grd.iCellYB(i)];
        else
            PY[i] = (P[grd.iCellYT(i)] + P[grd.iCellYB(i)]) / 2;

}


void ConvectionPars::calcEpsilonX() {

    for (int i = 0; i < dimSurfX; i++)
        if (i % grd.surfsXNumX == 0 || (i + 1) % grd.surfsXNumX == 0) {

            epsilon1X[i] = 0;

            epsilon2X[i] = 0;

        } else {

            epsilon1X[i] = grd.perm * fP.r1(PX[i]) / fP.mu1;

            epsilon2X[i] = grd.perm * fP.r2(PX[i]) / fP.mu2;

        }
}

void ConvectionPars::calcEpsilonY() {

    for (int i = 0; i < dimSurfY; i++)
        if (i < grd.surfsYNumX || i >= grd.surfsYNumX * (grd.surfsYNumY - 1)) {

            epsilon1Y[i] = 0;

            epsilon2Y[i] = 0;

        } else {

            epsilon1Y[i] = grd.perm * fP.r1(PY[i]) / fP.mu1;

            epsilon2Y[i] = grd.perm * fP.r2(PY[i]) / fP.mu2;

        }

}


void ConvectionPars::calckXKX() {

    double Scur;

    for (int i = 0; i < dimSurfX; i++) {

        if (nablaPX[i] < 0)
            Scur = S[grd.iCellXR(i)];
        else if (nablaPX[i] > 0)
            Scur = S[grd.iCellXL(i)];
        else
            Scur = SX[i];

        k1X[i] = fP.k1(Scur);
        K1X[i] = fP.K1(Scur);
        k2X[i] = fP.k2(Scur);
        K2X[i] = fP.K2(Scur);

    }
}

void ConvectionPars::calckYKY() {

    double Scur;

    for (int i = 0; i < dimSurfY; i++) {

        if (nablaPY[i] < 0)
            Scur = S[grd.iCellYT(i)];
        else if (nablaPY[i] > 0)
            Scur = S[grd.iCellYB(i)];
        else
            Scur = SY[i];

        k1Y[i] = fP.k1(Scur);
        K1Y[i] = fP.K1(Scur);
        k2Y[i] = fP.k2(Scur);
        K2Y[i] = fP.K2(Scur);

    }
}


void ConvectionPars::calcPars() {

    calcNablaPX();

    calcNablaPY();


    calcSX();

    calcSY();


    calcPX();

    calcPY();


    calcEpsilonX();

    calcEpsilonY();


    calckXKX();

    calckYKY();


    calcOtherPars();

}




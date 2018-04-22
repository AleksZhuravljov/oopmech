#include "LocationS.h"


LocationS::LocationS(Grid &grdPar, FuncPars &fPPar,
                     double &timeStepPar, GetFromFile &dataFilePar) : Location(grdPar, fPPar, timeStepPar, dataFilePar) {

    schemeEqName = "SCHEME_S";

}

LocationS::~LocationS() {}


void LocationS::setPNew(const std::vector<double> &PNewPar) {
    PNew = PNewPar;
}


void LocationS::calcAlpha() {
    for (int i = 0; i < dimCell; i++)
        alpha[i] = grd.poro * grd.cellsV[i];
}


void LocationS::defineVar() {
    var = S;
}


void LocationS::calcAF() {

    for (int i = 0; i < dimCell; i++)
        aF[i] = -alpha[i] / timeStep * var[i] * fP.r1(P[i]);

    aF[prodCellIndex] += Q1prod;

}

void LocationS::calcAC() {

    for (int i = 0; i < dimCell; i++)
        aC[i] = alpha[i] / timeStep * fP.r1(PNew[i]);

}



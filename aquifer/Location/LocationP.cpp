#include "LocationP.h"


LocationP::LocationP(Grid &grdPar, FuncPars &fPPar,
                     double &timeStepPar, GetFromFile &dataFilePar) : Location(grdPar, fPPar, timeStepPar, dataFilePar) {

    schemeEqName = "SCHEME_P";

}

LocationP::~LocationP() {}


double LocationP::getQ1prod(){
    return Q1prod;
}

double LocationP::getQ2prod(){
    return Q2prod;
}


void LocationP::calcAlpha() {
    for (int i = 0; i < dimCell; i++)
        alpha[i] = grd.poro * (fP.R1(P[i]) / fP.r1(P[i]) * S[i] + fP.R2(P[i]) / fP.r2(P[i]) * (1. - S[i])) * grd.cellsV[i];
}


void LocationP::defineVar() {
    var = P;
}


void LocationP::calcAF() {

    for (int i = 0; i < dimCell; i++)
        aF[i] = -alpha[i] / timeStep * var[i];

    aF[prodCellIndex] += Q1prod / fP.r1(P[prodCellIndex]) + Q2prod / fP.r2(P[prodCellIndex]);

}

void LocationP::calcAC() {

    for (int i = 0; i < dimCell; i++)
        aC[i] = alpha[i] / timeStep;

}



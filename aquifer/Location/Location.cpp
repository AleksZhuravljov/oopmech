#include "Location.h"

#include <iostream>

Location::Location(Grid &grdPar, FuncPars &fPPar,
                   double &timeStepPar, GetFromFile &dataFilePar) : grd(grdPar),
                                                                    fP(fPPar),
                                                                    dataFile(dataFilePar),
                                                                    dimCell(grd.cellsV.size()),
                                                                    prodCellIndex(dataFile.getWord<int>("PROD_CELL_INDEX")),
                                                                    Vprod(1. / 3600. / 24. *  dataFile.getWord<double>("V_PROD")),
                                                                    r1Std(dataFile.getWord<double>("R1_STD")),
                                                                    r2Std(dataFile.getWord<double>("R2_STD")),
                                                                    alpha(dimCell, 0),
                                                                    timeStep(timeStepPar),
                                                                    aF(dimCell, 0),
                                                                    aC(dimCell, 0) {}

Location::~Location() {}


void Location::setSchemeType() {

    schemeType = dataFile.getWord<std::string>(schemeEqName);

    schemeName = dataFile.getWord<std::string>(schemeEqName, 1);

    if (schemeType == "implicit")
        implicitFlag = true;
    else if (schemeType == "explicit")
        implicitFlag = false;

}


void Location::calcQ() {


    Q1prod = Vprod * fP.f(S[prodCellIndex]) * fP.r1(P[prodCellIndex]) /
             (fP.f(S[prodCellIndex]) * fP.r1(P[prodCellIndex]) / r1Std + (1. - fP.f(S[prodCellIndex])) * fP.r2(P[prodCellIndex]) / r2Std);

    Q2prod = Vprod * (1. - fP.f(S[prodCellIndex])) * fP.r2(P[prodCellIndex]) /
             (fP.f(S[prodCellIndex]) * fP.r1(P[prodCellIndex]) / r1Std + (1. - fP.f(S[prodCellIndex])) * fP.r2(P[prodCellIndex]) / r2Std);

}


void Location::calcСoefficients(const std::vector<double> &PPar, const std::vector<double> &SPar) {

    P = PPar;

    S = SPar;

    setSchemeType();

    defineVar();

    calcQ();

    calcAlpha();

    calcAF();

    calcAC();

}
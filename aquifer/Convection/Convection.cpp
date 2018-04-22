#include "Convection.h"


Convection::Convection(Grid &grdPar, FuncPars &fPPar,
                       GetFromFile &dataFilePar) : ConvectionPars(grdPar, fPPar),
                                                   dataFile(dataFilePar),
                                                   dimCell(grd.cellsV.size()),
                                                   divergence(dimCell, 0),
                                                   aF(dimCell, 0),
                                                   aC(dimCell, 0),
                                                   aR(dimCell, 0),
                                                   aL(dimCell, 0),
                                                   aT(dimCell, 0),
                                                   aB(dimCell, 0) {}

Convection::~Convection() {}


void Convection::defineSchemeType() {

    schemeType = dataFile.getWord<std::string>(schemeEqName);

    schemeName = dataFile.getWord<std::string>(schemeEqName, 1);

    if (schemeType == "implicit")
        implicitFlag = true;
    else if (schemeType == "explicit")
        implicitFlag = false;

}


void Convection::calcСoefficients(const std::vector<double> &PPar, const std::vector<double> &SPar) {

    P = PPar;

    S = SPar;

    defineSchemeType();

    calcPars();

    calcDivergence();

    calcA();

}
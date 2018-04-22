#include "PlotPar.h"

PlotPar::PlotPar(const Grid &grd) : PlotInterface(),
                                    grd(grd),
                                    flagCellsCur(true),
                                    flagSurfsXCur(false),
                                    flagSurfsYCur(false),
                                    seriesIntOptCur(0) {}

PlotPar::~PlotPar() {}


void PlotPar::setCellsCur() {

    flagCellsCur = true;
    flagSurfsXCur = false;
    flagSurfsYCur = false;

}

void PlotPar::setSurfsXCur() {

    flagCellsCur = false;
    flagSurfsXCur = true;
    flagSurfsYCur = false;

}

void PlotPar::setSurfsYCur() {

    flagCellsCur = false;
    flagSurfsXCur = false;
    flagSurfsYCur = true;

}


void PlotPar::addSeries(const std::vector<double> &seriesPar, const std::string &seriesNamePar) {

    series.push_back(seriesPar);
    seriesIntOpt.push_back(seriesIntOptCur);
    seriesName.push_back(seriesNamePar);
    curveType.push_back(curveTypeCur);

    flagCells.push_back(flagCellsCur);
    flagSurfsX.push_back(flagSurfsXCur);
    flagSurfsY.push_back(flagSurfsYCur);

    extraAddSeries();

}

void PlotPar::addSeries(const std::vector<double> &seriesPar) {

    addSeries(seriesPar, "");

    extraAddSeries();

}


void PlotPar::clearSeries() {

    series.clear();
    seriesIntOpt.clear();
    seriesName.clear();
    curveType.clear();

    flagCells.clear();
    flagSurfsX.clear();
    flagSurfsY.clear();

    extraClearSeries();

}










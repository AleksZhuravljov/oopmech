#ifndef PLOTPAR_H
#define PLOTPAR_H


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include "../States/Grid.h"
#include "PlotInterface.h"


class PlotPar : public PlotInterface {

public:

    PlotPar(const Grid &grdPar);

    virtual ~PlotPar();


    void setCellsCur();

    void setSurfsXCur();

    void setSurfsYCur();


    void addSeries(const std::vector<double> &seriesPar, const std::string &seriesNamePar);

    void addSeries(const std::vector<double> &seriesPar);

    void clearSeries();


protected:

    Grid grd;


    bool flagCellsCur;

    bool flagSurfsXCur;

    bool flagSurfsYCur;


    std::vector<bool> flagCells;

    std::vector<bool> flagSurfsX;

    std::vector<bool> flagSurfsY;


    std::vector<std::vector<double>> series;


    int seriesIntOptCur;

    std::vector<int> seriesIntOpt;


    virtual void extraAddSeries() {}

    virtual void extraClearSeries() {}


};


#endif

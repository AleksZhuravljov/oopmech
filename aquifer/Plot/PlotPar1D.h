#ifndef PLOTPAR1D_H
#define PLOTPAR1D_H


#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


#include "../Helper/StringAndNumber.h"
#include "PlotPar.h"


class PlotPar1D : public PlotPar {

public:

    PlotPar1D(const Grid &grdPar);

    virtual ~PlotPar1D();


    void setX();

    void setY();

    void setSeriesIntOptCur(const int &seriesIntOptCurPar);


    void outPutData();


private:

    void outPutPlotCommands();


    bool flagX;

    bool flagY;

};


#endif

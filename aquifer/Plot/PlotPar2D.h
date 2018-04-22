#ifndef PLOTPAR2D_H
#define PLOTPAR2D_H


#include <iomanip>


#include "PlotPar.h"
#include "../Helper/StringAndNumber.h"


class PlotPar2D : public PlotPar {

public:

    PlotPar2D(const Grid &grdPar);

    virtual ~PlotPar2D();


    void setFlagPm3dModCur(const bool &flagPm3dModCurPar);


    void outPutData();


private:

    bool flagPm3dModCur;

    std::vector<bool> flagPm3dMod;

    void extraAddSeries();

    void extraClearSeries();


    void outPutPlotCommands();

};


#endif

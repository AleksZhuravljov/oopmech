#ifndef PLOT_H
#define PLOT_H


#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>


#include "../Helper/StringAndNumber.h"
#include "PlotInterface.h"


class Plot : public PlotInterface {

public:

    Plot();

    virtual ~Plot();


    void addSeries(const std::vector<double> &seriesXPar, const std::vector<double> &seriesYPar, const std::string &seriesNamePar);

    void addSeries(const std::vector<double> &seriesXPar, const std::vector<double> &seriesYPar);

    void clearSeries();


    void setY2FlagCur(const bool &Y2FlagCurPar);


    void outPutData();


private:

    std::vector<std::vector<double>> seriesX;

    std::vector<std::vector<double>> seriesY;


    bool Y2FlagCur;

    std::vector<bool> Y2Flag;


    void outPutPlotCommands();


};


#endif
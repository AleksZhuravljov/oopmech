#ifndef CALCDATA_H
#define CALCDATA_H


#include "Aggregator.h"
#include "Plot/Plot.h"
#include "Plot/PlotPar1D.h"
#include "Plot/PlotPar2D.h"
#include "Helper/StringAndNumber.h"


void simple2D(const std::string &dataFileName);


void kKPlot(const std::string &dataFileName);

void fFPlot(const std::string &dataFileName);

void rRPlot(const std::string &dataFileName);

void r1R1Plot(const std::string &dataFileName);


void allFuncsPlot(const std::string &dataFileName);


#endif

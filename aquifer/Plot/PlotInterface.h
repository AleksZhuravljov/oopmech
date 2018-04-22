#ifndef PLOTINTERFACE_H
#define PLOTINTERFACE_H


#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>


#include "../Helper/StringAndNumber.h"


class PlotInterface {

public:

    PlotInterface();

    virtual ~PlotInterface();


    void setPlotName(const std::string &plotNamePar);


    void setCurveTypeCur(const std::string &curveTypeCurPar);


    void addDescription(const std::string &descriptionPlot);

    void addDescription(const std::vector<std::string> &descriptionPlotArrayPar);

    void clearDescription();


    void setTerminal(const std::string &terminalPar);

    void setSeparateTerminalFlag(const bool &separateTerminalFlagPar);

    void clearTerminal();


    void setTermOptions(const std::string &termOptionsPar);

    void clearTermOptions();


    void setOpenResultFlag(const bool &openResultFlagPar);


    void setUsingSysTermFlag(const bool &usingSysTermPar);


    virtual void outPutData() {}


    void setXMult(const double &XMultPar);

    void setYMult(const double &YMultPar);

    void setY2Mult(const double &Y2MultPar);

    void setZMult(const double &ZMultPar);


    void make();


protected:

    std::string plotName;


    std::string outDir;


    std::vector<std::string> seriesName;


    std::string curveTypeCur;

    std::vector<std::string> curveType;


    std::vector<std::string> descriptionPlotArray;


    std::string terminal;

    bool separateTerminalFlag;

    std::string termOptions;


    bool openResultFlag;

    bool usingSysTermFlag;


    void mkOutDir();


    void outPutDescription();


    virtual void outPutPlotCommands() {}


    double XMult;

    double YMult;

    double Y2Mult;

    double ZMult;

};


#endif

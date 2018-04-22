#include "PlotInterface.h"


PlotInterface::PlotInterface() : plotName("noName"),
                                 outDir("out/"),
                                 openResultFlag(false),
                                 separateTerminalFlag(false),
                                 usingSysTermFlag(true),
                                 XMult(1.),
                                 YMult(1.),
                                 Y2Mult(1.),
                                 ZMult(1.) {}

PlotInterface::~PlotInterface() {}


void PlotInterface::setPlotName(const std::string &plotNamePar) {
    plotName = plotNamePar;
}


void PlotInterface::setCurveTypeCur(const std::string &curveTypeCurPar) {
    curveTypeCur = curveTypeCurPar;
}


void PlotInterface::addDescription(const std::string &descriptionPlot) {
    descriptionPlotArray.push_back(descriptionPlot);
}

void PlotInterface::addDescription(const std::vector<std::string> &descriptionPlotArrayPar) {
    descriptionPlotArray.insert(descriptionPlotArray.end(), descriptionPlotArrayPar.begin(), descriptionPlotArrayPar.end());
}

void PlotInterface::clearDescription() {
    descriptionPlotArray.clear();
}


void PlotInterface::setTerminal(const std::string &terminalPar) {
    terminal = terminalPar;
}

void PlotInterface::setSeparateTerminalFlag(const bool &separateTerminalFlagPar) {
    separateTerminalFlag = separateTerminalFlagPar;
}

void PlotInterface::clearTerminal() {
    terminal = "";
    termOptions = "";
}


void PlotInterface::setTermOptions(const std::string &termOptionsPar) {
    termOptions = termOptionsPar;
}

void PlotInterface::clearTermOptions() {
    termOptions = "";
}


void PlotInterface::setOpenResultFlag(const bool &openResultFlagPar) {
    openResultFlag = openResultFlagPar;
}


void PlotInterface::setUsingSysTermFlag(const bool &usingSysTermFlagPar) {
    usingSysTermFlag = usingSysTermFlagPar;
}


void PlotInterface::make() {

    outPutDescription();

    outPutData();

    outPutPlotCommands();


    std::string filePlotName = plotName + ".plt";

    std::string command = "cd " + outDir + ";" + " gnuplot " + filePlotName;

    if (terminal == "" && separateTerminalFlag == true)
        command += " &";
    else if (openResultFlag == true)
        command += "; open " + plotName + "." + terminal;

    if (terminal != "" || separateTerminalFlag != true)
        command += "; ";

    command += " cd ..";


    if (usingSysTermFlag == true)
        std::cout << system(command.c_str());

}


void PlotInterface::mkOutDir() {

    std::string command = "mkdir " + outDir;

    if (std::ifstream(outDir.c_str())) {}
    else
        std::cout << system(command.c_str());

}


void PlotInterface::outPutDescription() {

    mkOutDir();


    std::ofstream pltStream;

    std::string filePlotName;
    filePlotName = outDir + plotName + ".plt";

    pltStream.open(filePlotName.c_str());

    if (terminal != "") {
        pltStream << "set term " << terminal;
        if (termOptions != "")
            pltStream << " " << termOptions;
        pltStream << std::endl << "set output '" << plotName << "." << terminal << "'" << std::endl;
    }


    for (int i = 0; i < descriptionPlotArray.size(); i++)
        pltStream << descriptionPlotArray[i] << std::endl;

    pltStream.close();

}

void PlotInterface::setXMult(const double &XMultPar) {
    XMult = XMultPar;
}

void PlotInterface::setYMult(const double &YMultPar) {
    YMult = YMultPar;
}

void PlotInterface::setY2Mult(const double &Y2MultPar) {
    Y2Mult = Y2MultPar;
}

void PlotInterface::setZMult(const double &ZMultPar) {
    ZMult = ZMultPar;
}
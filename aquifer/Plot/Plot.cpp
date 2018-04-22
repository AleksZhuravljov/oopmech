#include "Plot.h"

Plot::Plot() : PlotInterface(), Y2FlagCur(false) {

    curveTypeCur = "lp lw 2 pt 7";

}

Plot::~Plot() {}


void Plot::addSeries(const std::vector<double> &seriesXPar, const std::vector<double> &seriesYPar, const std::string &seriesNamePar) {

    seriesX.push_back(seriesXPar);
    seriesY.push_back(seriesYPar);
    seriesName.push_back(seriesNamePar);
    Y2Flag.push_back(Y2FlagCur);
    curveType.push_back(curveTypeCur);

}

void Plot::addSeries(const std::vector<double> &seriesXPar, const std::vector<double> &seriesYPar) {

    addSeries(seriesXPar, seriesYPar, "");

}


void Plot::clearSeries() {

    seriesX.clear();
    seriesY.clear();
    seriesName.clear();
    Y2Flag.clear();
    curveType.clear();

}


void Plot::setY2FlagCur(const bool &Y2FlagCurPar) {
    Y2FlagCur = Y2FlagCurPar;
}


void Plot::outPutData() {

    mkOutDir();


    std::ofstream dataStream;

    dataStream.precision(5);

    int widthCellOut = 14;

    dataStream.setf(std::ios::scientific, std::ios::floatfield);

    std::string fileDataName;


    for (int i = 0; i < seriesX.size(); i++) {

        fileDataName = outDir + plotName + toString(i) + ".dat";

        dataStream.open(fileDataName.c_str());

        for (int j = 0; j < seriesX[i].size(); j++) {

            dataStream << std::setw(widthCellOut) << XMult * seriesX[i][j];

            if (Y2Flag[i])
                dataStream << std::setw(widthCellOut) << Y2Mult * seriesY[i][j] << std::endl;
            else
                dataStream << std::setw(widthCellOut) << YMult * seriesY[i][j] << std::endl;

        }


        dataStream.close();

    }

}


void Plot::outPutPlotCommands() {

    mkOutDir();


    std::ofstream pltStream;

    std::string filePlotName;


    filePlotName = outDir + plotName + ".plt";

    pltStream.open(filePlotName.c_str(), std::ios::app);

    std::string fileDataName;

    pltStream << "set title \"" << plotName << "\"" << std::endl;

    for (int i = 0; i < seriesX.size(); i++)
        if (Y2Flag[i]) {
            pltStream << "set y2tics" << std::endl;
            break;
        }

    pltStream << "plot\\" << std::endl;

    for (int i = 0; i < seriesX.size(); i++) {

        fileDataName = plotName + toString(i) + ".dat";

        if (i > 0)
            pltStream << ",\\" << std::endl;

        pltStream << "'" << fileDataName << "' using 1:2 ";

        if (Y2Flag[i])
            pltStream << "axes x1y2 ";

        pltStream << "w " << curveType[i] << " ti " << "'" << seriesName[i] << "'";

    }

    if (terminal == "" && separateTerminalFlag == true)
        pltStream << std::endl << "pause mouse close";

    pltStream.close();

}





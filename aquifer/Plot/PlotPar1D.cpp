#include "PlotPar1D.h"


PlotPar1D::PlotPar1D(const Grid &grdPar) : PlotPar(grdPar), flagX{true}, flagY{false} {

    curveTypeCur = "lp lw 2 pt 7";

}

PlotPar1D::~PlotPar1D() {}


void PlotPar1D::setX() {

    flagX = true;
    flagY = false;

}

void PlotPar1D::setY() {

    flagX = false;
    flagY = true;

}


void PlotPar1D::setSeriesIntOptCur(const int &seriesIntOptCurPar) {
    seriesIntOptCur = seriesIntOptCurPar;
}


void PlotPar1D::outPutData() {

    mkOutDir();


    int NumX = 0;

    std::vector<double> coordinate;

    bool flagPut = false;


    std::ofstream dataStream;

    dataStream.precision(5);

    int widthCellOut = 14;

    dataStream.setf(std::ios::scientific, std::ios::floatfield);

    std::string fileDataName;

    for (int i = 0; i < series.size(); i++) {

        // Definition of NumX and coordinate:

        if (flagCells[i]) {

            NumX = grd.cellsNumX;

            if (flagX)
                coordinate = grd.cellsX;
            else if (flagY)
                coordinate = grd.cellsY;

        } else if (flagSurfsX[i]) {

            NumX = grd.surfsXNumX;

            if (flagX)
                coordinate = grd.surfsXX;
            else if (flagY)
                coordinate = grd.surfsXY;

        } else {

            NumX = grd.surfsYNumX;

            if (flagX)
                coordinate = grd.surfsYX;
            else if (flagY)
                coordinate = grd.surfsYY;

        }


        fileDataName = outDir + plotName + toString(i) + ".txt";

        dataStream.open(fileDataName.c_str());

        for (int j = 0; j < series[i].size(); j++) {

            flagPut = false;

            if (flagX && (j >= NumX * seriesIntOpt[i] && j < NumX * (seriesIntOpt[i] + 1)))
                flagPut = true;
            else if (flagY && (j - seriesIntOpt[i]) % NumX == 0)
                flagPut = true;

            if (flagPut)
                dataStream << std::setw(widthCellOut) << XMult * coordinate[j] << std::setw(widthCellOut) << YMult * series[i][j]
                           << std::endl;

        }

        dataStream.close();

    }

}


void PlotPar1D::outPutPlotCommands() {

    std::string command = "mkdir " + outDir;
    if (std::ifstream(outDir.c_str())) {}
    else
        std::cout << system(command.c_str());


    std::ofstream pltStream;

    std::string filePlotName;

    filePlotName = outDir + plotName + ".plt";

    pltStream.open(filePlotName.c_str(), std::ios::app);

    std::string fileDataName;

    pltStream << "set title \"" << plotName << "\"" << std::endl;

    pltStream << "plot\\" << std::endl;

    for (int i = 0; i < series.size(); i++) {

        fileDataName = plotName + toString(i) + ".txt";

        if (i > 0)
            pltStream << ",\\" << std::endl;
        pltStream << "'" << fileDataName << "' using 1:2 ";

        pltStream << "w " << curveType[i];

        if (seriesName[i] != "")
            pltStream << " ti " << "'" << seriesName[i] << "'";
        else
            pltStream << " notitle";

    }

    if (terminal == "" && separateTerminalFlag == true)
        pltStream << std::endl << "pause mouse close";

    pltStream.close();

}






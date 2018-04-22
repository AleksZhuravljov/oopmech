#include "PlotPar2D.h"


PlotPar2D::PlotPar2D(const Grid &grdPar) : PlotPar(grdPar),
                                           flagPm3dModCur(true) {

    curveTypeCur = "";

}

PlotPar2D::~PlotPar2D() {}


void PlotPar2D::setFlagPm3dModCur(const bool &flagPm3dModCurPar) {
    flagPm3dModCur = flagPm3dModCurPar;
}


void PlotPar2D::outPutData() {

    mkOutDir();



    // definition of minValueArray and maxValueArray:

    std::vector<double> minValueArray;
    std::vector<double> maxValueArray;

    double currentValue = 0;

    for (int i = 0; i < series.size(); i++) {

        minValueArray.push_back(0);
        maxValueArray.push_back(0);

        minValueArray[i] = series[i][0];
        maxValueArray[i] = series[i][0];

        for (int j = 0; j < series[i].size(); j++) {

            currentValue = series[i][j];

            if (minValueArray[i] > currentValue)
                minValueArray[i] = currentValue;

            if (maxValueArray[i] < currentValue)
                maxValueArray[i] = currentValue;

        }
    }


    // definition of modSeriesArray:

    int NumX = 0;

    std::vector<double> coordinateX;
    std::vector<double> coordinateY;

    std::vector<double> modSeries; // temporary modified series

    std::vector<std::vector<double>> modSeriesArray; // modified series array


    for (int i = 0; i < series.size(); i++) {
        modSeries.clear();

        for (int j = 0; j < series[i].size(); j++) {

            modSeries.push_back(series[i][j]);

            if (flagCells[i] && flagPm3dMod[i])
                if ((j + 1) % grd.cellsNumX == 0)
                    modSeries.push_back(minValueArray[i]);

        }

        if (flagCells[i] && flagPm3dMod[i])
            for (int j = 0; j < grd.cellsNumX + 1; j++)
                modSeries.push_back(minValueArray[i]);

        modSeriesArray.push_back(modSeries);

    }


    // out put series to data files:

    std::ofstream dataStream;

    dataStream.precision(5);

    int widthCellOut = 14;

    dataStream.setf(std::ios::scientific, std::ios::floatfield);

    std::string fileDataName;

    for (int i = 0; i < modSeriesArray.size(); i++) {

        // definition of NumX, coordinateX and coordinateY:

        if (flagSurfsX[i]) {

            NumX = grd.surfsXNumX;

            coordinateX = grd.surfsXX;
            coordinateY = grd.surfsXY;

        } else if (flagSurfsY[i]) {

            NumX = grd.surfsYNumX;

            coordinateX = grd.surfsYX;
            coordinateY = grd.surfsYY;

        } else {

            if (flagPm3dMod[i]) {

                NumX = grd.nodesNumX;

                coordinateX = grd.nodesX;
                coordinateY = grd.nodesY;

            } else {

                NumX = grd.cellsNumX;

                coordinateX = grd.cellsX;
                coordinateY = grd.cellsY;

            }
        }


        fileDataName = outDir + plotName + toString(i) + ".txt";

        dataStream.open(fileDataName.c_str());

        for (int j = 0; j < modSeriesArray[i].size(); j++) {

            dataStream << std::setw(widthCellOut) << XMult * coordinateX[j];
            dataStream << std::setw(widthCellOut) << YMult * coordinateY[j];
            dataStream << std::setw(widthCellOut) << ZMult * modSeriesArray[i][j] << std::endl;

            if ((j + 1) % NumX == 0)
                dataStream << std::endl;

        }

        dataStream.close();

    }

}


void PlotPar2D::extraAddSeries() {
    flagPm3dMod.push_back(flagPm3dModCur);
}

void PlotPar2D::extraClearSeries() {
    flagPm3dMod.clear();
}


void PlotPar2D::outPutPlotCommands() {

    mkOutDir();


    std::ofstream pltStream;

    std::string filePlotName;

    filePlotName = outDir + plotName + ".plt";

    pltStream.open(filePlotName.c_str(), std::ios::app);

    std::string fileDataName;

    pltStream << "set title \"" << plotName << "\"" << std::endl;

    pltStream << "splot\\" << std::endl;

    for (int i = 0; i < series.size(); i++) {

        fileDataName = plotName + toString(i) + ".txt";

        if (i > 0)
            pltStream << ",\\" << std::endl;
        pltStream << "'" << fileDataName << "' ";


        if (curveType[i] != "")
            pltStream << "w " << curveType[i];

        if (seriesName[i] == "")
            pltStream << " notitle";
        else
            pltStream << " ti " << "'" << seriesName[i] << "'";

    }

    if (terminal == "" && separateTerminalFlag == true)
        pltStream << std::endl << "pause mouse close";

    pltStream.close();

}



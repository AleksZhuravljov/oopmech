#include "Grid.h"
#include <iostream>


Grid::Grid(GetFromFile &dataFilePar) : dataFile(dataFilePar),
                                       gridFile(dataFile.getWord<std::string>("GRID_FILE")),
                                       poro(gridFile.getWord<double>("PORO")),
                                       perm(gridFile.getWord<double>("PERM")),
                                       h(dataFile.getWord<double>("THICKNESS")),
                                       nodesNumX(gridFile.getWord<int>("NUMBER_X_NODES")),
                                       nodesX(gridFile.getVector<double>("NODES_X")),
                                       nodesY(gridFile.getVector<double>("NODES_Y")),
                                       nodesNumY((int) (nodesX.size() / nodesNumX)) {

    calcCellsParameters();


    calcSurfsXParameters();

    calcSurfsYParameters();


    calcSurfsXL();

    calcSurfsYL();

}

Grid::~Grid() {}


void Grid::calcSurfsXL() {

    surfsXL.clear();

    double Lx = 0;
    double Ly = 0;

    for (int i = 0; i < surfsXOMEGA.size(); i++) {

        if (i % surfsXNumX == 0) {
            Lx = 2 * (cellsX[iCellXR(i)] - surfsXX[i]);
            Ly = 2 * (cellsY[iCellXR(i)] - surfsXY[i]);
        } else if ((i + 1) % surfsXNumX == 0) {
            Lx = 2 * (surfsXX[i] - cellsX[iCellXL(i)]);
            Ly = 2 * (surfsXY[i] - cellsY[iCellXL(i)]);
        } else {
            Lx = cellsX[iCellXR(i)] - cellsX[iCellXL(i)];
            Ly = cellsY[iCellXR(i)] - cellsY[iCellXL(i)];
        }

        surfsXL.push_back(std::sqrt(Lx * Lx + Ly * Ly));

    }
}

void Grid::calcSurfsYL() {

    surfsYL.clear();

    double Lx = 0;
    double Ly = 0;

    for (int i = 0; i < surfsYOMEGA.size(); i++) {

        if (i < surfsYNumX) {
            Lx = 2 * (cellsX[iCellYT(i)] - surfsYX[i]);
            Ly = 2 * (cellsY[iCellYT(i)] - surfsYY[i]);
        } else if (i >= surfsYNumX * (surfsYNumY - 1)) {
            Lx = 2 * (surfsYX[i] - cellsX[iCellYB(i)]);
            Ly = 2 * (surfsYY[i] - cellsY[iCellYB(i)]);
        } else {
            Lx = cellsX[iCellYT(i)] - cellsX[iCellYB(i)];
            Ly = cellsY[iCellYT(i)] - cellsY[iCellYB(i)];
        }

        surfsYL.push_back(std::sqrt(Lx * Lx + Ly * Ly));
    }
}


void Grid::calcSurfsXParameters() {

    surfsXNumX = nodesNumX;
    surfsXNumY = cellsNumY;

    double x1 = 0;
    double x2 = 0;

    double y1 = 0;
    double y2 = 0;

    for (int i = 0; i < nodesX.size(); i++)
        if (i < nodesNumX * (nodesNumY - 1)) {

            x1 = nodesX[i];
            y1 = nodesY[i];

            x2 = nodesX[i + nodesNumX];
            y2 = nodesY[i + nodesNumX];

            surfsXX.push_back((x1 + x2) / 2);
            surfsXY.push_back((y1 + y2) / 2);
            surfsXOMEGA.push_back(std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2)));
            surfsXOMEGA.back() *= h;

        }
}


void Grid::calcSurfsYParameters() {

    surfsYNumX = cellsNumX;
    surfsYNumY = nodesNumY;

    double x1 = 0;
    double x2 = 0;

    double y1 = 0;
    double y2 = 0;

    for (int i = 0; i < nodesX.size(); i++)
        if ((i + 1) % nodesNumX != 0) {

            x1 = nodesX[i];
            y1 = nodesY[i];

            x2 = nodesX[i + 1];
            y2 = nodesY[i + 1];

            surfsYX.push_back((x1 + x2) / 2);
            surfsYY.push_back((y1 + y2) / 2);
            surfsYOMEGA.push_back(std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2)));
            surfsYOMEGA.back() *= h;

        }
}


void Grid::calcCellsParameters() {

    cellsNumX = nodesNumX - 1;
    cellsNumY = nodesNumY - 1;

    for (int i = 0; i < nodesX.size(); i++)
        if ((i + 1) % nodesNumX != 0 && i < nodesNumX * (nodesNumY - 1))
            cellsX.push_back((nodesX[i] + nodesX[i + 1] + nodesX[i + nodesNumX] + nodesX[i + nodesNumX + 1]) / 4);


    for (int i = 0; i < nodesY.size(); i++)
        if ((i + 1) % nodesNumX != 0 && i < nodesNumX * (nodesNumY - 1))
            cellsY.push_back((nodesY[i] + nodesY[i + 1] + nodesY[i + nodesNumX] + nodesY[i + nodesNumX + 1]) / 4);

    double x1 = 0;
    double x2 = 0;
    double x3 = 0;
    double x4 = 0;

    double y1 = 0;
    double y2 = 0;
    double y3 = 0;
    double y4 = 0;

    double a = 0;
    double b = 0;
    double c = 0;
    double d = 0;

    double p = 0;


    for (int i = 0; i < nodesX.size(); i++)
        if ((i + 1) % nodesNumX != 0 && i < nodesNumX * (nodesNumY - 1)) {

            x1 = nodesX[i];
            y1 = nodesY[i];

            x2 = nodesX[i + 1];
            y2 = nodesY[i + 1];

            x3 = nodesX[i + nodesNumX];
            y3 = nodesY[i + nodesNumX];

            x4 = nodesX[i + nodesNumX + 1];
            y4 = nodesY[i + nodesNumX + 1];

            a = std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
            b = std::sqrt(std::pow((x3 - x1), 2) + std::pow((y3 - y1), 2));
            c = std::sqrt(std::pow((x4 - x3), 2) + std::pow((y4 - y3), 2));
            d = std::sqrt(std::pow((x4 - x2), 2) + std::pow((y4 - y2), 2));

            p = (a + b + c + d) / 2;

            cellsV.push_back(sqrt((p - a) * (p - b) * (p - c) * (p - d)));

            cellsV.back() *= h;
        }
}


int Grid::iSurfXR(int iPar) {
    return iPar + iPar / cellsNumX + 1;
}

int Grid::iSurfXL(int iPar) {
    return iPar + iPar / cellsNumX;
}

int Grid::iSurfYT(int iPar) {
    return iPar + surfsYNumX;
}

int Grid::iSurfYB(int iPar) {
    return iPar;
}


int Grid::iCellXR(int iPar) {
    return iPar - iPar / surfsXNumX;
}

int Grid::iCellXL(int iPar) {
    return iPar - iPar / surfsXNumX - 1;
}

int Grid::iCellYT(int iPar) {
    return iPar;
}

int Grid::iCellYB(int iPar) {
    return iPar - surfsYNumX;
}
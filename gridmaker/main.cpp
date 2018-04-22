#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>


#include "GetFromFile.h"


const double PI = 4. * atan(1.);

int main(int narg, char **arg) {


    GetFromFile dataFile(arg[1]);


    double poro = dataFile.getWord<double>("PORO");


    double perm = dataFile.getWord<double>("PERM");


    double X0 = dataFile.getWord<double>("X0");


    double Y0 = dataFile.getWord<double>("Y0");


    double XL = dataFile.getWord<double>("XL");

    double YL = dataFile.getWord<double>("YL");


    double angle = dataFile.getWord<double>("ANGLE");
    angle *= PI / 180.;


    int nodesNumX = dataFile.getWord<double>("NODES_NUM_X");


    int nodesNumY = dataFile.getWord<double>("NODES_NUM_Y");


    std::vector<double> nodesX;

    for (int i = 0; i < nodesNumY; i++)
        for (int j = 0; j < nodesNumX; j++)
            nodesX.push_back((X0 + XL / (nodesNumX - 1) * j) * cos(angle) - (Y0 + YL / (nodesNumY - 1) * i) * sin(angle));


    std::vector<double> nodesY;

    for (int i = 0; i < nodesNumY; i++)
        for (int j = 0; j < nodesNumX; j++)
            nodesY.push_back((X0 + XL / (nodesNumX - 1) * j) * sin(angle) + (Y0 + YL / (nodesNumY - 1) * i) * cos(angle));


    int wBig = 20;

    int wSmall = 15;


    std::ofstream stream;

    stream.precision(5);

    stream.setf(std::ios::scientific, std::ios::floatfield);

    stream.open(dataFile.getWord<std::string>("GRID_FILE").c_str());

    stream << std::left << std::setw(wBig) << "PORO";
    stream << std::right << std::setw(wSmall) << poro << std::endl;


    stream << std::left << std::setw(wBig) << "PERM";
    stream << std::right << std::setw(wSmall) << perm << " m2" << std::endl;


    stream << std::endl;
    stream << "NUMBER_X_NODES " << nodesNumX << std::endl;

    stream << "NODES_X" << std::endl;

    for (int i = 0; i < nodesX.size(); i++) {

        stream << std::right << std::setw(wSmall) << nodesX[i];
        if ((i + 1) % nodesNumX == 0)
            stream << std::endl;

    }

    stream << "\\ m" << std::endl;

    stream << std::endl;

    stream << "NODES_Y" << std::endl;

    for (int i = 0; i < nodesY.size(); i++) {

        stream << std::right << std::setw(wSmall) << nodesY[i];
        if ((i + 1) % nodesNumX == 0)
            stream << std::endl;

    }

    stream << "\\ m" << std::endl;

    stream.close();


    double SiniReg1 = dataFile.getWord<double>("SAT_INI_REG_1");
    double SiniReg2 = dataFile.getWord<double>("SAT_INI_REG_2");

    double XminReg2 = dataFile.getWord<double>("X_MIN_REG_2");
    double XmaxReg2 = dataFile.getWord<double>("X_MAX_REG_2");
    double YminReg2 = dataFile.getWord<double>("Y_MIN_REG_2");
    double YmaxReg2 = dataFile.getWord<double>("Y_MAX_REG_2");


    double dX = (XL - X0) / (nodesNumX - 1);
    double dY = (YL - Y0) / (nodesNumX - 1);
    int cal = (XL - X0) / dX;
    int row = (YL - Y0) / dY;
    int calMin = (XminReg2 - X0) / dX + 1;
    int calMax = (XmaxReg2 - X0) / dX + 1;
    int rowMin = (YminReg2 - Y0) / dY + 1;
    int rowMax = (YmaxReg2 - Y0) / dY + 1;

    std::cout << "dX " << dX << std::endl;
    std::cout << "dY " << dY << std::endl;
    std::cout << "cal " << cal << std::endl;
    std::cout << "row " << row << std::endl;
    std::cout << "calMin " << calMin << std::endl;
    std::cout << "calMax " << calMax << std::endl;
    std::cout << "rowMin " << rowMin << std::endl;
    std::cout << "rowMax " << rowMax << std::endl;

    std::vector<double> Sini;

    for (int i = 0; i < nodesNumY - 1; i++)
        for (int j = 0; j < nodesNumX - 1; j++)
            if ((i + 1 >= calMin && i + 1 <= calMax) && (j + 1 >= rowMin && j + 1 <= rowMax))
                Sini.push_back(SiniReg2);
            else
                Sini.push_back(SiniReg1);

    stream.open(dataFile.getWord<std::string>("SATINI_FILE").c_str());

    stream << "SAT_INI" << std::endl;

    for (int i = 0; i < Sini.size(); i++) {

        stream << std::right << std::setw(wSmall) << Sini[i];
        if ((i + 1) % (nodesNumX - 1) == 0)
            stream << std::endl;

    }

    stream << "\\" << std::endl;

    stream.close();

    stream.unsetf(std::ios::floatfield);

    return 0;
}
#ifndef AGGREGATOR_H
#define AGGREGATOR_H


#include <ctime>
#include <iomanip>
#include <iostream>
#include <unistd.h>


#include "Equation/EquationP.h"
#include "Equation/EquationS.h"
#include "Helper/MatrixOperations.h"
#include "States/Grid.h"
#include "States/FuncPars.h"
#include "Convection/ConvectionP.h"
#include "Convection/ConvectionS.h"
#include "Location/LocationP.h"
#include "Location/LocationS.h"
#include "Helper/ColorForConsol.h"


class Aggregator {

public:

    Aggregator(const std::string &dataFileName, std::vector<std::vector<double> > &PPar, std::vector<std::vector<double> > &SPar);

    virtual ~Aggregator();


    GetFromFile dataFile;


    Grid grd;


    FuncPars fP;


private:

    int dimCell;


    std::vector<std::vector<double> > &P;

    std::vector<std::vector<double> > &S;


    unsigned int startTimeCalc;


    double timeStep;


    int prodCellIndex;


    GetFromFile satIniFile;


    std::vector<std::vector<double>> Pcur;

    std::vector<std::vector<double>> Scur;


    LocationP locateP;

    LocationS locateS;


    ConvectionP convectP;

    ConvectionS convectS;


    EquationP eqP;

    EquationS eqS;


    double timeStepCur;


    double VSumProdCur;


    double V2SumProdCur;


    long long int timeStepCount;


    unsigned int outPutDelay;

    unsigned int outPutTime;


    void outPars();


    void outAtribs();


    void calcTimeStepCur();


    void calcQSumQ1Sum();


    void calcAddAtribs();


    double timeCurrent;


    double percents;


    int parsOutCount;

    int atribsOutCount;


public:


    std::vector<double> displParTime;


    std::vector<double> displProdTime;


    std::vector<double> VSumProd;


    std::vector<double> V2SumProd;


    double bulkMass2Ini;

    std::vector<double> bulkMass2;


    std::vector<double> displEf2;


    std::vector<double> VProd;


    std::vector<double> V2Prod;


    std::vector<double> frac1;


    std::vector<double> Pw;

    double PwCur;


    std::vector<double> PwAv;

    double PwAvCur;


    double rW;

    double rC;

    double skin;


    void calculate();

};


#endif

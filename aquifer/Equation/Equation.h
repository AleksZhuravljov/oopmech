#ifndef AQUATION_H
#define AQUATION_H


#include <string>


#include "../Helper/GetFromFile.h"
#include "../Helper/LinearEquation.h"
#include "../States/FuncPars.h"
#include "../States/Grid.h"


template<class Tloc, class Tconv>
class Equation {

public:

    Equation(GetFromFile &dataFilePar, Tloc &locatePar, Tconv &convectPar, Grid &grdPar,
             std::vector<std::vector<double>> &PPar, std::vector<std::vector<double>> &SPar);

    virtual ~Equation() {};


private:

    GetFromFile &dataFile;


protected:

    Tconv &convect;


    Tloc &locate;


private:

    Grid &grd;


    int dimCell;

    int cellsNumX;


protected:

    virtual void calcСoefficients() {}


private:

    std::vector<double> aF;

    void aggregateAF();


    std::vector<double> aC;

    void aggregateAC();


    std::vector<double> aR;

    void aggregateAR();


    std::vector<double> aL;

    void aggregateAL();


    std::vector<double> aT;

    void aggregateAT();


    std::vector<double> aB;

    void aggregateAB();


    std::vector<int> poi;

    std::vector<int> col;

    std::vector<double> val;

    void aggregateMatrix();


protected:

    void aggregateСoefficients();


    int index;


    std::vector<std::vector<double>> &P;


    std::vector<std::vector<double>> &S;


private:

    double maxTolerance;


    LinearEquation LE;


protected:

    void calcVar(std::vector<double> &var, const std::vector<double> &varOld);


public:

    virtual void solve(const int &indexPar) {}

};


template<class Tloc, class Tconv>
Equation<Tloc, Tconv>::Equation(GetFromFile &dataFilePar, Tloc &locatePar, Tconv &convectPar, Grid &grdPar,
                                std::vector<std::vector<double>> &PPar,
                                std::vector<std::vector<double>> &SPar) : dataFile(dataFilePar),
                                                                          convect(convectPar),
                                                                          locate(locatePar),
                                                                          grd(grdPar),
                                                                          dimCell(grd.cellsV.size()),
                                                                          cellsNumX(grd.cellsNumX),
                                                                          aC(dimCell, 0), aF(dimCell, 0), aR(dimCell, 0), aL(dimCell, 0),
                                                                          aT(dimCell, 0), aB(dimCell, 0),
                                                                          maxTolerance(dataFile.getWord<double>("MAX_TOLERANCE")),
                                                                          P(PPar),
                                                                          S(SPar),
                                                                          LE(poi, col, val, dimCell) {}


template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateAF() {
    for (int i = 0; i < dimCell; i++)
        aF[i] = locate.aF[i] + convect.aF[i];
}

template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateAC() {
    for (int i = 0; i < dimCell; i++)
        aC[i] = locate.aC[i] + convect.aC[i];
}

template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateAR() {
    for (int i = 0; i < dimCell; i++)
        aR[i] = convect.aR[i];
}

template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateAL() {
    for (int i = 0; i < dimCell; i++)
        aL[i] = convect.aL[i];
}

template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateAT() {
    for (int i = 0; i < dimCell; i++)
        aT[i] = convect.aT[i];
}

template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateAB() {
    for (int i = 0; i < dimCell; i++)
        aB[i] = convect.aB[i];
}


template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateMatrix() {

    col.clear();
    poi.clear();
    val.clear();

    int j = 0;

    poi.push_back(j);

    for (int i = 0; i < dimCell; i++) {

        if (aB[i] != 0) {
            col.push_back(i - cellsNumX);
            val.push_back(aB[i]);
            j++;
        }

        if (aL[i] != 0) {
            col.push_back(i - 1);
            val.push_back(aL[i]);
            j++;
        }

        if (aC[i] != 0) {
            col.push_back(i);
            val.push_back(aC[i]);
            j++;
        }

        if (aR[i] != 0) {
            col.push_back(i + 1);
            val.push_back(aR[i]);
            j++;
        }

        if (aT[i] != 0) {
            col.push_back(i + cellsNumX);
            val.push_back(aT[i]);
            j++;
        }

        poi.push_back(j);

    }

}


template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::aggregateСoefficients() {

    calcСoefficients();

    aggregateAF();

    aggregateAC();

    aggregateAR();

    aggregateAL();

    aggregateAT();

    aggregateAB();


    aggregateMatrix();

}


template<class Tloc, class Tconv>
void Equation<Tloc, Tconv>::calcVar(std::vector<double> &var, const std::vector<double> &varOld) {

    if (convect.implicitFlag == true) {

        if (convect.schemeName == "biConjugateGrSt")
            LE.calcBiConjugateGrSt(aF, var, varOld, maxTolerance);
        else if (convect.schemeName == "conjugateGrLSq")
            LE.calcConjugateGrLSq(aF, var, varOld, maxTolerance);
        else if (convect.schemeName == "supernodalLUFact")
            LE.calcSupernodalLUFact(aF, var);

    } else
        for (int i = 0; i < dimCell; i++)
            var[i] = -aF[i] / aC[i];

}


#endif
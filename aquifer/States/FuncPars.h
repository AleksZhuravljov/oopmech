#ifndef FUNCPARS_H
#define FUNCPARS_H


#include <cmath>
#include <string>


#include "../Helper/GetFromFile.h"


class FuncPars {

public:

    FuncPars(GetFromFile &dataFilePar);

    virtual ~FuncPars();


private:

    GetFromFile &dataFile;


public:

    GetFromFile fPFile;


    double dA1;

    double dB1;


    double dA2;

    double dB2;


    double PMin;

    double PMax;


private:

    double kA1;

    double kn1;


    double kA2;

    double kn2;


public:

    double S1r;

    double mu1;


    double S2r;

    double mu2;


    double k1(const double &S);

    double k2(const double &S);


    double K1(const double &S);

    double K2(const double &S);


    double f(const double &S);

    double F(const double &S);


    double r1(const double &P);

    double r2(const double &P);


    double R1(const double &P);

    double R2(const double &P);

};


#endif

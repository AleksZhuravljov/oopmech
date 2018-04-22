#include "FuncPars.h"


FuncPars::FuncPars(GetFromFile &dataFilePar) : dataFile(dataFilePar),
                                               fPFile(dataFile.getWord<std::string>("FP_FILE")),
                                               dA1(fPFile.getWord<double>("dA1")),
                                               dB1(fPFile.getWord<double>("dB1")),
                                               dA2(fPFile.getWord<double>("dA2")),
                                               dB2(fPFile.getWord<double>("dB2")),
                                               PMin(fPFile.getWord<double>("PMin")),
                                               PMax(fPFile.getWord<double>("PMax")),
                                               kA1(fPFile.getWord<double>("kA1")),
                                               kn1(fPFile.getWord<double>("kn1")),
                                               mu1(fPFile.getWord<double>("visc1")),
                                               kA2(fPFile.getWord<double>("kA2")),
                                               kn2(fPFile.getWord<double>("kn2")),
                                               mu2(fPFile.getWord<double>("visc2")),
                                               S1r(fPFile.getWord<double>("S1r")),
                                               S2r(fPFile.getWord<double>("S2r")) {}


FuncPars::~FuncPars() {}


double FuncPars::k1(const double &S) {
    if (S < S1r)
        return 0;
    else if (S > 1. - S2r)
        return kA1;
    else
        return kA1 * std::pow((S - S1r) / (1. - S1r - S2r), kn1);
}

double FuncPars::k2(const double &S) {
    if (S < S1r)
        return kA2;
    else if (S > 1. - S2r)
        return 0;
    else
        return kA2 * std::pow((1. - S - S2r) / (1. - S1r - S2r), kn2);
}


double FuncPars::K1(const double &S) {
    if (S < S1r)
        return 0;
    else if (S > 1. - S2r)
        return 0;
    else
        return kn1 * kA1 * std::pow((S - S1r), (kn1 - 1.)) / std::pow((1. - S1r - S2r), (2. * kn1 - 2.));
}

double FuncPars::K2(const double &S) {
    if (S < S1r)
        return 0;
    else if (S > 1. - S2r)
        return 0;
    else
        return -kn2 * kA2 * std::pow((1. - S - S2r), (kn2 - 1.)) / std::pow((1. - S1r - S2r), (2. * kn2 - 2.));
}


double FuncPars::f(const double &S) {
    return k1(S) / mu1 / (k1(S) / mu1 + k2(S) / mu2);
}

double FuncPars::F(const double &S) {
    return (K1(S) / mu1 * k2(S) / mu2 - K2(S) / mu2 * k1(S) / mu1) / (k1(S) / mu1 + k2(S) / mu2) / (k1(S) / mu1 + k2(S) / mu2);
}


double FuncPars::r1(const double &P) {
    return dA1 * P + dB1;
}

double FuncPars::r2(const double &P) {
    return dA2 * P + dB2;
}


double FuncPars::R1(const double &P) {
    return dA1;
}

double FuncPars::R2(const double &P) {
    return dA2;
}
#include "LinearEquation.h"


LinearEquation::LinearEquation(std::vector<int> &poi, std::vector<int> &col,
                               std::vector<double> &val, const int &dimPar) : dim(dimPar),
                                                                              poi(poi), col(col), val(val),
                                                                              matrix(dim, dim),
                                                                              X0(dim), F(dim), X(dim) {}

LinearEquation::~LinearEquation() {}


void LinearEquation::fillMatrix() {

    coefficients.clear();

    for (int i = 0; i < poi.size() - 1; i++)
        for (int j = poi[i]; j < poi[i + 1]; j++)
            coefficients.push_back(Eigen::Triplet<double>(i, col[j], val[j]));

    matrix.setZero();

    matrix.setFromTriplets(coefficients.begin(), coefficients.end());

}


void LinearEquation::fillF(const std::vector<double> &FPar) {

    for (int i = 0; i < dim; i++)
        F[i] = -FPar[i];

}


void LinearEquation::fillX0(const std::vector<double> &X0Par) {

    for (int i = 0; i < dim; i++)
        X0[i] = X0Par[i];

}


void LinearEquation::outX(std::vector<double> &XPar) {

    XPar.clear();

    for (int i = 0; i < dim; i++)
        XPar.push_back(X[i]);

}


void LinearEquation::setMaxTolerance(const double &maxTolerance) {

    if (maxTolerance != 0)
        conjugateGrLSq.setTolerance(maxTolerance);

}


void LinearEquation::calcBiConjugateGrSt(const std::vector<double> &FPar, std::vector<double> &XPar, const std::vector<double> &X0Par,
                                         const double &maxTolerance) {
    fillMatrix();

    setMaxTolerance(maxTolerance);

    biConjugateGrSt.compute(matrix);

    fillF(FPar);

    fillX0(X0Par);

    X = biConjugateGrSt.solveWithGuess(F, X0);

    outX(XPar);

}


void LinearEquation::calcConjugateGrLSq(const std::vector<double> &FPar, std::vector<double> &XPar, const std::vector<double> &X0Par,
                                        const double &maxTolerance) {

    fillMatrix();

    setMaxTolerance(maxTolerance);

    conjugateGrLSq.compute(matrix);

    fillF(FPar);

    fillX0(X0Par);

    X = conjugateGrLSq.solveWithGuess(F, X0);

    outX(XPar);

}


void LinearEquation::calcSupernodalLUFact(const std::vector<double> &FPar, std::vector<double> &XPar) {

    fillMatrix();

    supernodalLUFact.compute(matrix);

    fillF(FPar);

    X = supernodalLUFact.solve(F);

    outX(XPar);

}
#ifndef LINEAREQUATION_H
#define LINEAREQUATION_H


#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>


#include <Eigen3/Eigen/Sparse>


class LinearEquation {

public:

    LinearEquation(std::vector<int> &poi, std::vector<int> &col, std::vector<double> &val, const int &dimPar);

    virtual ~LinearEquation();


private:

    std::vector<int> &poi;

    std::vector<int> &col;

    std::vector<double> &val;


    int dim;


    std::vector<Eigen::Triplet<double>> coefficients;


    Eigen::SparseMatrix<double> matrix;

    void fillMatrix();


    Eigen::VectorXd X0;

    void fillX0(const std::vector<double> &X0Par);


    Eigen::VectorXd F;

    void fillF(const std::vector<double> &FPar);


    Eigen::VectorXd X;

    void outX(std::vector<double> &XPar);


    void setMaxTolerance(const double &maxTolerance);


    Eigen::BiCGSTAB<Eigen::SparseMatrix<double>> biConjugateGrSt;


    Eigen::LeastSquaresConjugateGradient<Eigen::SparseMatrix<double>> conjugateGrLSq;


    Eigen::SparseLU<Eigen::SparseMatrix<double>> supernodalLUFact;


public:

    void calcBiConjugateGrSt(const std::vector<double> &FPar, std::vector<double> &XPar,
                             const std::vector<double> &X0Par, const double &maxTolerance);


    void calcConjugateGrLSq(const std::vector<double> &FPar, std::vector<double> &XPar,
                            const std::vector<double> &X0Par, const double &maxTolerance);


    void calcSupernodalLUFact(const std::vector<double> &FPar, std::vector<double> &XPar);


};


#endif
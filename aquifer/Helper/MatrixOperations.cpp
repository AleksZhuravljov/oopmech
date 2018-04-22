#include "MatrixOperations.h"


MatrixOperations::MatrixOperations(std::vector<int> &poi, std::vector<int> &col, std::vector<double> &val) : poi(poi), col(col), val(val) {}

MatrixOperations::~MatrixOperations() {}


void MatrixOperations::vectorMult(std::vector<double> &result, const std::vector<double> &param) {

    for (int i = 0; i < poi.size() - 1; i++) {

        result[i] = 0;

        for (int j = poi[i]; j < poi[i + 1]; j++)
            result[i] += val[j] * param[col[j]];

    }

}


double MatrixOperations::elementVectorMult(const std::vector<double> &param, const int &iPar) {

    double result = 0;

    for (int j = poi[iPar]; j < poi[iPar + 1]; j++)
        result += val[j] * param[col[j]];

    return result;

}


void MatrixOperations::getDiagonal(std::vector<double> &result) {

    for (int i = 0; i < poi.size() - 1; i++) {

        result[i] = 0;

        for (int j = poi[i]; j < poi[i + 1]; j++)
            if (i == col[j])
                result[i] = val[j];

    }

}



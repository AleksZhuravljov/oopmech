#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H


#include <iomanip>
#include <iostream>
#include <vector>


class MatrixOperations {

public:

    MatrixOperations(std::vector<int> &poi, std::vector<int> &col, std::vector<double> &val);

    virtual ~MatrixOperations();


    std::vector<int> &poi;

    std::vector<int> &col;

    std::vector<double> &val;


    template<class T>
    void streamIn(T &outPut, const int &width, const int &prec);


    template<class T>
    void streamInFull(T &outPut, const int &width, const int &prec, const bool &flagPortrait);


    template<class T>
    void streamInFull(T &outPut, const int &width, const int &prec);


    void vectorMult(std::vector<double> &result, const std::vector<double> &param);


    double elementVectorMult(const std::vector<double> &param, const int &iPar);


    void getDiagonal(std::vector<double> &result);

};


template<class T>
void MatrixOperations::streamIn(T &outPut, const int &width, const int &prec) {

    outPut.precision(prec);

    outPut << "ind:";
    for (unsigned int i = 0; i < val.size(); i++)
        outPut << std::setw(width) << i;
    outPut << std::endl;

    outPut << "val:";
    for (unsigned int i = 0; i < val.size(); i++)
        outPut << std::setw(width) << val[i];
    outPut << std::endl;

    outPut << "col:";
    for (unsigned int i = 0; i < col.size(); i++)
        outPut << std::setw(width) << col[i];
    outPut << std::endl;

    outPut << "poi:";
    int multW = 0;
    for (unsigned int i = 0; i < poi.size(); i++) {
        multW = 0;
        if (i > 0)
            multW = poi[i] - poi[i - 1];
        if (multW == 0)
            multW = 1;
        if ((i == 0) || (i > 0 && poi[i] - poi[i - 1] != 0))
            outPut << std::setw(width * multW) << poi[i];
    }


    outPut << std::endl;

    //outPut.setf(std::ios::fixed, std::ios::floatfield);
    //outPut.setf(std::ios::scientific, std::ios::floatfield);
    //outPut.unsetf(std::ios::floatfield);

}


template<class T>
void MatrixOperations::streamInFull(T &outPut, const int &width, const int &prec) {

    streamInFull(outPut, width, prec, false);

}


template<class T>
void MatrixOperations::streamInFull(T &outPut, const int &width, const int &prec, const bool &flagPortrait) {

    double a = 0;

    int m = 0;

    if (flagPortrait == true) {
        for (int i = 0; i < poi.size(); i++)
            outPut << "▁▁";
        outPut << std::endl;
    }

    for (unsigned int i = 0; i < poi.size() - 1; i++) {

        if (flagPortrait == true)
            outPut << "▏";

        for (unsigned int k = 0; k < poi.size() - 1; k++) {

            a = 0;

            m = k;

            for (int j = poi[i]; j < poi[i + 1]; j++)
                if (m == col[j])
                    a = val[j];

            if (flagPortrait == false)
                if (a != 0)
                    outPut << std::setw(width) << a;
                else
                    outPut << std::setw(width) << "*";
            else {

                if (a == 0) outPut << "  ";
                else outPut << "▝▘";

            }

        }

        if (flagPortrait == true)
            outPut << "▕";

        outPut << std::endl;
    }

    if (flagPortrait == true) {

        for (int i = 0; i < poi.size(); i++)
            outPut << "▔▔";

        outPut << std::endl;

    }

    //outPut.setf(std::ios::fixed, std::ios::floatfield);
    //outPut.setf(std::ios::scientific, std::ios::floatfield);
    //outPut.unsetf(std::ios::floatfield);

}


#endif

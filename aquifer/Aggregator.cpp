#include "Aggregator.h"


Aggregator::Aggregator(const std::string &dataFileName,
                       std::vector<std::vector<double> > &PPar,
                       std::vector<std::vector<double> > &SPar) : dataFile(dataFileName),
                                                                  grd(dataFile),
                                                                  fP(dataFile),
                                                                  dimCell(grd.cellsV.size()),
                                                                  P(PPar),
                                                                  S(SPar),
                                                                  startTimeCalc(clock()),
                                                                  outPutTime(startTimeCalc),
                                                                  timeStep(dataFile.getWord<double>("TIME_STEP")),
                                                                  prodCellIndex(dataFile.getWord<int>("PROD_CELL_INDEX")),
                                                                  Pcur(2,
                                                                       std::vector<double>(dimCell, 1.E+5 * dataFile.getWord<double>("P_INI"))),
                                                                  satIniFile(dataFile.getWord<std::string>("S_INI_FILE")),
                                                                  Scur(2, satIniFile.getVector<double>("SAT_INI")),
                                                                  locateP(grd, fP, timeStepCur, dataFile),
                                                                  locateS(grd, fP, timeStepCur, dataFile),
                                                                  convectP(grd, fP, dataFile),
                                                                  convectS(grd, fP, dataFile),
                                                                  eqP(dataFile, locateP, convectP, grd, Pcur, Scur),
                                                                  eqS(dataFile, locateS, convectS, grd, Pcur, Scur),
                                                                  outPutDelay(1.E+6 * dataFile.getWord<double>("OUT_PUT_DELAY")),
                                                                  displParTime(dataFile.getVector<double>("TIME")),
                                                                  timeCurrent(0),
                                                                  parsOutCount(0),
                                                                  atribsOutCount(0),
                                                                  timeStepCount(0),
                                                                  VSumProdCur(0),
                                                                  V2SumProdCur(0),
                                                                  bulkMass2Ini(0),
                                                                  rW(dataFile.getWord<double>("R_WELL")),
                                                                  rC(sqrt(grd.cellsV[prodCellIndex] / grd.h / 3.14)),
                                                                  skin(dataFile.getWord<double>("SKIN")) {

    for (int i = 0; i < grd.cellsV.size(); i++)
        bulkMass2Ini += grd.poro * grd.cellsV[i] * (1. - Scur[(timeStepCount + 1) % 2][i]) *
                        fP.r2(Pcur[(timeStepCount + 1) % 2][i]);

    for (int i = 0; i < displParTime.size(); i++)
        displParTime[i] *= 60 * 60 * 24;


}

Aggregator::~Aggregator() {}


void Aggregator::outPars() {

    if (timeCurrent == displParTime[parsOutCount]) {

        S.push_back(Scur[timeStepCount % 2]);

        P.push_back(Pcur[timeStepCount % 2]);

        parsOutCount++;
    }

}


void Aggregator::outAtribs() {

    if ((timeCurrent / displParTime.back() * 100) >= atribsOutCount) {


        VSumProd.push_back(VSumProdCur);


        V2SumProd.push_back(V2SumProdCur);


        displProdTime.push_back(timeCurrent);


        bulkMass2.push_back(0);

        for (int i = 0; i < grd.cellsV.size(); i++)
            bulkMass2.back() += grd.poro * grd.cellsV[i] * (1. - Scur[timeStepCount % 2][i]) * fP.r2(Pcur[timeStepCount % 2][i]);

        Pw.push_back(PwCur);

        PwAv.push_back(PwAvCur);


        for (int i = 1; i <= percents / 2; i++)
            std::cout << "█";

        for (int i = percents / 2 + 1; i <= 50; i++)
            std::cout << "▄";


        std::cout.precision(1);
        std::cout.setf(std::ios::fixed, std::ios::floatfield);
        std::cout << std::setw(8) << percents << " %";

        std::cout.precision(3);
        std::cout.setf(std::ios::scientific, std::ios::floatfield);
        std::cout << std::setw(12) << timeCurrent << " s";

        std::cout.precision(3);
        std::cout.setf(std::ios::scientific, std::ios::floatfield);
        std::cout << std::setw(12) << 1.E-6 * (clock() - startTimeCalc) << " s";

        std::cout << std::setw(10) << timeStepCount << " steps";
        std::cout.unsetf(std::ios::floatfield);

        std::cout << '\r';

        std::cout.flush();

        atribsOutCount = percents + 2;


        if ((clock() - outPutTime) < outPutDelay)
            usleep(outPutDelay - (clock() - outPutTime));

        outPutTime = clock();

    }

}


void Aggregator::calcTimeStepCur() {

    timeStepCur = timeStep;

    if ((timeCurrent + timeStepCur) > displParTime[parsOutCount])
        timeStepCur = displParTime[parsOutCount] - timeCurrent;

}


void Aggregator::calcQSumQ1Sum() {

    VSumProdCur += (locateP.getQ1prod() / locateP.r1Std + locateP.getQ2prod() / locateP.r2Std) * timeStepCur;

    V2SumProdCur += locateP.getQ2prod() / locateP.r2Std * timeStepCur;

    double rAv = fP.f(Scur[timeStepCount % 2][prodCellIndex]) * fP.r1(Pcur[timeStepCount % 2][prodCellIndex]) +
                 (1. - fP.f(Scur[timeStepCount % 2][prodCellIndex])) * fP.r2(Pcur[timeStepCount % 2][prodCellIndex]);

    double transmis = grd.perm * (fP.k1(Scur[timeStepCount % 2][prodCellIndex]) / fP.mu1 +
                                  fP.k2(Scur[timeStepCount % 2][prodCellIndex]) / fP.mu2);

    PwCur = Pcur[timeStepCount % 2][prodCellIndex] -
            (locateP.getQ1prod() + locateP.getQ2prod()) * (log(rC / rW) - 3. / 4. + skin) /
            (2. * 3.14 * transmis * rAv * grd.h);

    PwAvCur = Pcur[timeStepCount % 2][prodCellIndex];

}


void Aggregator::calcAddAtribs() {

    displEf2.push_back(0);

    VProd.push_back(0);

    V2Prod.push_back(0);

    double Sini = satIniFile.getVector<double>("SAT_INI")[prodCellIndex];

    double Pini = dataFile.getWord<double>("P_INI");

    frac1.push_back(fP.f(Sini) * fP.r1(Pini) / (fP.f(Sini) * fP.r1(Pini) + (1. - fP.f(Sini)) * fP.r2(Pini)));


    for (int i = 1; i < VSumProd.size(); i++) {

        displEf2.push_back(1. - bulkMass2[i] / bulkMass2Ini);

        VProd.push_back((VSumProd[i] - VSumProd[i - 1]) / (displProdTime[i] - displProdTime[i - 1]));

        V2Prod.push_back((V2SumProd[i] - V2SumProd[i - 1]) / (displProdTime[i] - displProdTime[i - 1]));

        frac1.push_back((VProd[i] - V2Prod[i]) / VProd[i]);

    }

}


void Aggregator::calculate() {

    P.clear();

    S.clear();


    outPars();


    std::cout << green << std::endl;
    std::cout << "calculation";
    std::cout << std::endl;


    do {

        calcTimeStepCur();

        eqP.solve(timeStepCount % 2);

        eqS.solve(timeStepCount % 2);

        timeStepCount++;

        timeCurrent += timeStepCur;

        percents = timeCurrent / displParTime.back() * 100;

        calcQSumQ1Sum();

        outAtribs();

        outPars();

    } while (timeCurrent < displParTime.back());


    std::cout << resetColor << std::endl;


    calcAddAtribs();

}



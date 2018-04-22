#include "CalcData.h"


void simple2D(const std::string &dataFileName) {

    GetFromFile dataFile(dataFileName);

    std::vector<std::vector<double> > P;
    std::vector<std::vector<double> > S;
    Aggregator agg(dataFileName, P, S);


    double volumeMod = dataFile.getWord<double>("VOLUME_MOD");
    double volumeCur = 0;
    double volumeMult = 0;
    if (volumeMod != 0) {
        for (int i = 0; i < agg.grd.cellsV.size(); i++)
            if (i % agg.grd.cellsNumX == 0 || (i + 1) % agg.grd.cellsNumX == 0 || i < agg.grd.cellsNumX ||
                i >= (agg.grd.cellsNumX - 1) * agg.grd.cellsNumY)
                volumeCur += agg.grd.cellsV[i];

        volumeMult = 1. + volumeMod / volumeCur;

        for (int i = 0; i < agg.grd.cellsV.size(); i++)
            if (i % agg.grd.cellsNumX == 0 || (i + 1) % agg.grd.cellsNumX == 0 || i < agg.grd.cellsNumX ||
                i >= (agg.grd.cellsNumX - 1) * agg.grd.cellsNumY)

                agg.grd.cellsV[i] *= volumeMult;

    }


    if (dataFile.getWord<bool>("ANIMATION")) {

        double displParTimeMax = agg.displParTime.back();
        agg.displParTime.clear();
        int numDisplParTimeIntervals = dataFile.getWord<int>("ANIMATION", 1);
        for (int i = 0; i < numDisplParTimeIntervals + 1; i++)
            agg.displParTime.push_back(displParTimeMax / numDisplParTimeIntervals * i);

    }

    agg.calculate();


    std::string pltSName;
    PlotPar2D pltS(agg.grd);
    pltS.setFlagPm3dModCur(false);
    pltS.setXMult(1.E-3);
    pltS.setYMult(1.E-3);
    pltS.setCellsCur();

    if (dataFile.getWord<bool>("PM3D")) {

        pltS.setFlagPm3dModCur(true);

        pltS.setCurveTypeCur("");

        pltS.addDescription("unset grid");
        pltS.addDescription("set pm3d map corners2color c1");

    } else {

        pltS.setCurveTypeCur("l lw 2 lt 1 palette");

        pltS.addDescription("set contour");
        pltS.addDescription("unset surface");
        pltS.addDescription("set cntrparam levels auto 20");
        pltS.addDescription("set view map");
        pltS.addDescription("set grid");

    }

    pltS.addDescription("set cbrange[0:1]");
    pltS.addDescription("set xlabel 'X, 10^{3} m'");
    pltS.addDescription("set ylabel 'Y, 10^{3} m'");
    pltS.addDescription("set cblabel 'saturation'");
    pltS.addDescription("set y2label");
    pltS.addDescription("unset y2tics");

    pltS.addDescription("set size square");
    pltS.setUsingSysTermFlag(false);

    PlotPar2D pltP(agg.grd);
    std::string pltPName;
    pltP.setFlagPm3dModCur(false);
    pltP.setXMult(1.E-3);
    pltP.setYMult(1.E-3);
    pltP.setZMult(1.E-5);
    pltP.setCellsCur();

    if (dataFile.getWord<bool>("PM3D")) {

        pltP.setFlagPm3dModCur(true);

        pltP.setCurveTypeCur("");

        pltP.addDescription("unset grid");
        pltP.addDescription("set pm3d map corners2color c1");

    } else {

        pltP.setCurveTypeCur("l lw 2 lt 1 palette");

        pltP.addDescription("set contour");
        pltP.addDescription("unset surface");
        pltP.addDescription("set cntrparam levels auto 20");
        pltP.addDescription("set view map");
        pltP.addDescription("set grid");

    }

    GetFromFile fPFile = dataFile.getWord<std::string>("FP_FILE");


    std::string cbrange =
            "set cbrange[" + toString(1.E-5 * fPFile.getWord<double>("PMin")) + ":" +
            toString(1.E-5 * fPFile.getWord<double>("PMax")) + "]";

    if (dataFile.getWord<int>("ANIMATION") != 0)
        pltP.addDescription(cbrange);
    pltP.addDescription("set xlabel 'X, 10^{3} m'");
    pltP.addDescription("set ylabel 'Y, 10^{3} m'");
    pltP.addDescription("set cblabel 'pressure, bar'");
    pltP.addDescription("set y2label");
    pltP.addDescription("unset y2tics");
    pltP.addDescription("set size square");
    pltP.setUsingSysTermFlag(false);

    Plot pltQ;
    std::string pltQName = "VV2VsumV2sum";
    pltQ.setPlotName(pltQName);
    pltQ.addDescription("set xlabel 't, day'");
    pltQ.addDescription("set ylabel 'V,V_2, sm^3/day'");
    pltQ.addDescription("set y2label 'V_{sum},V_{2sum}, 10^{3} sm^3'");
    pltQ.addDescription("set size nosquare");
    pltQ.addDescription("set grid");
    pltQ.setXMult(1. / (60. * 60. * 24.));
    pltQ.setYMult(60. * 60. * 24.);
    pltQ.setY2Mult(1.E-3);
    pltQ.setCurveTypeCur("l lw 3 lt 1 lc 1");
    pltQ.addSeries(agg.displProdTime, agg.VProd, "VProd");
    pltQ.setCurveTypeCur("l lw 3 lt 1 lc 2");
    pltQ.addSeries(agg.displProdTime, agg.V2Prod, "V2Prod");
    pltQ.setY2FlagCur(true);
    pltQ.setCurveTypeCur("l lw 3 lt 1 lc 3");
    pltQ.addSeries(agg.displProdTime, agg.VSumProd, "VSumProd");
    pltQ.setCurveTypeCur("l lw 3 lt 1 lc 4");
    pltQ.addSeries(agg.displProdTime, agg.V2SumProd, "V2SumProd");
    pltQ.setUsingSysTermFlag(false);
    pltQ.make();


    Plot pltDEf;
    std::string pltDEfName = "frac1DisplEf1PwPwAv";
    pltDEf.setPlotName(pltDEfName);
    pltDEf.addDescription("set xlabel 't, day'");
    pltDEf.addDescription("set ylabel 'frac_1,DisplEf_2'");
    pltDEf.addDescription("set y2label 'pressure, bar'");
    pltDEf.addDescription("set grid");
    pltDEf.addDescription("set size nosquare");
    pltDEf.setXMult(1. / (60. * 60. * 24.));
    pltDEf.setY2Mult(1.E-5);
    pltDEf.setCurveTypeCur("l lw 3 lt 1 lc 1");
    pltDEf.addSeries(agg.displProdTime, agg.displEf2, "DisplEf_2");
    pltDEf.setCurveTypeCur("l lw 3 lt 1 lc 2");
    pltDEf.addSeries(agg.displProdTime, agg.frac1, "frac_1");
    pltDEf.setY2FlagCur(true);
    pltDEf.setCurveTypeCur("l lw 3 lt 1 lc 3");
    pltDEf.addSeries(agg.displProdTime, agg.Pw, "Pw");
    pltDEf.setCurveTypeCur("l lw 3 lt 1 lc 4");
    pltDEf.addSeries(agg.displProdTime, agg.PwAv, "PwAv");
    pltDEf.setUsingSysTermFlag(false);
    pltDEf.make();


    std::string outDir = "out/";

    std::string plotName = "simple2D";

    std::string filePlotName;

    std::ofstream dataStream;

    std::string command;


    if (dataFile.getWord<bool>("ANIMATION")) {

        filePlotName = outDir + plotName + ".plt";
        dataStream.open(filePlotName.c_str());

        dataStream << "set term gif \\" << std::endl;
        dataStream << "  animate \\" << std::endl;
        dataStream << "  optimize \\" << std::endl;
        dataStream << "  delay 15 \\" << std::endl;
        dataStream << "  size 1300, 1000 \\" << std::endl;
        dataStream << "  background \"white\"" << std::endl;
        dataStream << std::endl;

        dataStream << "set output '" << plotName << ".gif'" << std::endl;
        dataStream << std::endl;

        for (int i = 0; i < agg.displParTime.size(); i++) {

            pltSName = "S" + toString(i);
            pltS.setPlotName(pltSName);
            pltS.clearSeries();
            pltS.addSeries(S[i]);
            pltS.make();

            pltPName = "P" + toString(i);
            pltP.setPlotName(pltPName);
            pltP.clearSeries();
            pltP.addSeries(P[i]);
            pltP.make();

            dataStream << "set multiplot layout 2, 2 title '" << agg.displParTime[i] << " s'" << std::endl;
            dataStream << "load '" << pltPName << ".plt'" << std::endl;
            dataStream << "load '" << pltQName << ".plt'" << std::endl;
            dataStream << "load '" << pltSName << ".plt'" << std::endl;
            dataStream << "load '" << pltDEfName << ".plt'" << std::endl;
            dataStream << "unset multiplot" << std::endl;

        }

        dataStream.close();
        command = "cd " + outDir + "; " + "gnuplot " + plotName + ".plt; open " + plotName + ".gif -a safari; cd ..";
        std::cout << system(command.c_str());

    } else
        for (int i = 0; i < agg.displParTime.size(); i++) {

            pltSName = "S" + toString(i);
            pltS.setPlotName(pltSName);
            pltS.clearSeries();
            pltS.addSeries(S[i]);
            pltS.make();

            pltPName = "P" + toString(i);
            pltP.setPlotName(pltPName);
            pltP.clearSeries();
            pltP.addSeries(P[i]);
            pltP.make();

            filePlotName = outDir + plotName + toString(i) + ".plt";
            dataStream.open(filePlotName.c_str());
            dataStream << "set term png size 1300,1000" << std::endl;
            dataStream << "set output '" << plotName << toString(i) << ".png'" << std::endl;
            dataStream << "set multiplot layout 2, 2 title '" << agg.displParTime[i] << " s'" << std::endl;
            dataStream << "load '" << pltPName << ".plt'" << std::endl;
            dataStream << "load '" << pltQName << ".plt'" << std::endl;
            dataStream << "load '" << pltSName << ".plt'" << std::endl;
            dataStream << "load '" << pltDEfName << ".plt'" << std::endl;
            dataStream << "unset multiplot" << std::endl;
            dataStream.close();
            command = "cd " + outDir + "; " + "gnuplot " + plotName + toString(i) + ".plt; open " + plotName +
                      toString(i) + ".png; cd ..";
            std::cout << system(command.c_str());
        }

}


//=====================================================================================================================


//=====================================================================================================================


void kKPlot(const std::string &dataFileName) {

    GetFromFile dataFile(dataFileName);


    FuncPars fP(dataFile);


    std::vector<double> X;

    std::vector<double> Y;


    Plot plt;


    plt.setUsingSysTermFlag(false);


    plt.setPlotName("kK");

    plt.addDescription("set xlabel \'S\'");
    plt.addDescription("set ylabel \'k\'");
    plt.addDescription("set y2label \'K\'");
    plt.addDescription("set xrange [0:1]");
    plt.addDescription("set yrange [0:1]");
    plt.addDescription("set y2range [*:*]");
    plt.addDescription("set ytics");
    plt.addDescription("set y2tics");
    plt.addDescription("set grid");

    plt.setCurveTypeCur("l lw 2");

    X.clear();
    Y.clear();
    for (int i = 0; i <= 20; i++) {
        X.push_back(0.05 * i);
        Y.push_back(fP.k1(X[i]));
    }
    plt.addSeries(X, Y, "k_1");

    X.clear();
    Y.clear();
    for (int i = 0; i <= 20; i++) {
        X.push_back(0.05 * i);
        Y.push_back(fP.k2(X[i]));
    }
    plt.addSeries(X, Y, "k_2");


    plt.setY2FlagCur(true);

    X.clear();
    Y.clear();
    for (int i = 0; i <= 1000; i++) {
        X.push_back(0.001 * i);
        Y.push_back(fP.K1(X[i]));
    }
    plt.addSeries(X, Y, "K_1");

    X.clear();
    Y.clear();
    for (int i = 0; i <= 1000; i++) {
        X.push_back(0.001 * i);
        Y.push_back(fP.K2(X[i]));
    }
    plt.addSeries(X, Y, "K_2");


    plt.make();

}


//---------------------------------------------------------------------------------------------------------------------


void fFPlot(const std::string &dataFileName) {

    GetFromFile dataFile(dataFileName);


    FuncPars fP(dataFile);


    std::vector<double> X;

    std::vector<double> Y;


    Plot plt;


    plt.setUsingSysTermFlag(false);


    plt.setPlotName("fF");

    plt.addDescription("set xlabel \'S\'");
    plt.addDescription("set ylabel \'f\'");
    plt.addDescription("set y2label \'F\'");
    plt.addDescription("set xrange [0:1]");
    plt.addDescription("set yrange [0:1]");
    plt.addDescription("set y2range [*:*]");
    plt.addDescription("set ytics");
    plt.addDescription("set y2tics");
    plt.addDescription("set grid");

    plt.setCurveTypeCur("l lw 2");


    X.clear();
    Y.clear();
    for (int i = 0; i <= 1000; i++) {
        X.push_back(0.001 * i);
        Y.push_back(fP.f(X[i]));
    }
    plt.addSeries(X, Y, "f");


    plt.setY2FlagCur(true);

    X.clear();
    Y.clear();
    for (int i = 0; i <= 1000; i++) {
        X.push_back(0.001 * i);
        Y.push_back(fP.F(X[i]));
    }
    plt.addSeries(X, Y, "F");


    plt.make();

}


//---------------------------------------------------------------------------------------------------------------------


void rRPlot(const std::string &dataFileName) {

    GetFromFile dataFile(dataFileName);


    FuncPars fP(dataFile);


    std::vector<double> X;

    std::vector<double> Y;


    Plot plt;


    plt.setUsingSysTermFlag(false);


    plt.setPlotName("rR");

    plt.addDescription("set xlabel \'P, 10^7 Pa\'");
    plt.addDescription("set ylabel \'r, kg/m3\'");
    plt.addDescription("set y2label \'R, 10^{-7} kg/m3/Pa\'");
    plt.addDescription("set xrange [" + toString(1.E-7 * fP.PMin) + ":" + toString(1.E-7 * fP.PMax) + "]");
    plt.addDescription("set yrange [*:*]");
    plt.addDescription("set y2range [*:*]");
    plt.addDescription("set ytics");
    plt.addDescription("set y2tics");
    plt.addDescription("set grid");

    plt.setCurveTypeCur("l lw 2");

    X.clear();
    Y.clear();
    for (double P = fP.PMin; P <= fP.PMax; P += 0.001 * (fP.PMax - fP.PMin)) {
        X.push_back(1.E-7 * P);
        Y.push_back(fP.r1(P));
    }
    plt.addSeries(X, Y, "r_1");

    X.clear();
    Y.clear();
    for (double P = fP.PMin; P <= fP.PMax; P += 0.001 * (fP.PMax - fP.PMin)) {
        X.push_back(1.E-7 * P);
        Y.push_back(fP.r2(P));
    }
    plt.addSeries(X, Y, "r_2");


    plt.setY2FlagCur(true);

    X.clear();
    Y.clear();
    for (double P = fP.PMin; P <= fP.PMax; P += 0.001 * (fP.PMax - fP.PMin)) {
        X.push_back(1.E-7 * P);
        Y.push_back(1.E+7 * fP.R1(P));
    }
    plt.addSeries(X, Y, "R_1");

    X.clear();
    Y.clear();
    for (double P = fP.PMin; P <= fP.PMax; P += 0.001 * (fP.PMax - fP.PMin)) {
        X.push_back(1.E-7 * P);
        Y.push_back(1.E+7 * fP.R2(P));
    }
    plt.addSeries(X, Y, "R_2");


    plt.make();

}


//---------------------------------------------------------------------------------------------------------------------


void r2R2Plot(const std::string &dataFileName) {

    GetFromFile dataFile(dataFileName);


    FuncPars fP(dataFile);


    std::vector<double> X;

    std::vector<double> Y;


    Plot plt;


    plt.setUsingSysTermFlag(false);


    plt.setPlotName("r2R2");

    plt.addDescription("set xlabel \'P, 10^7 Pa\'");
    plt.addDescription("set ylabel \'r, kg/m3\'");
    plt.addDescription("set y2label \'R, 10^{-7} kg/m3/Pa\'");
    plt.addDescription("set xrange [" + toString(1.E-7 * fP.PMin) + ":" + toString(1.E-7 * fP.PMax) + "]");
    plt.addDescription("set yrange [*:*]");
    plt.addDescription("set y2range [*:*]");
    plt.addDescription("set ytics");
    plt.addDescription("set y2tics");
    plt.addDescription("set grid");

    plt.setCurveTypeCur("l lw 2");

    X.clear();
    Y.clear();
    for (double P = fP.PMin; P <= fP.PMax; P += 0.001 * (fP.PMax - fP.PMin)) {
        X.push_back(1.E-7 * P);
        Y.push_back(fP.r2(P));
    }
    plt.addSeries(X, Y, "r_2");


    plt.setY2FlagCur(true);

    X.clear();
    Y.clear();
    for (double P = fP.PMin; P <= fP.PMax; P += 0.001 * (fP.PMax - fP.PMin)) {
        X.push_back(1.E-7 * P);
        Y.push_back(1.E+7 * fP.R2(P));
    }
    plt.addSeries(X, Y, "R_2");


    plt.make();

}


//=====================================================================================================================


void allFuncsPlot(const std::string &dataFileName) {

    GetFromFile dataFile(dataFileName);

    if (dataFile.getWord<bool>("fPPlotFlag")) {

        std::string outDir = "out/";

        std::string plotName = "allFuncs";


        kKPlot(dataFileName);

        fFPlot(dataFileName);

        rRPlot(dataFileName);

        r2R2Plot(dataFileName);


        std::string filePlotName = outDir + plotName + ".plt";


        std::ofstream dataStream;

        dataStream.open(filePlotName.c_str());

        dataStream << "set term png size 1300,1000" << std::endl;
        dataStream << "set output '" << plotName << ".png'" << std::endl;
        dataStream << "set multiplot layout 2, 2" << std::endl;
        dataStream << "load 'kK.plt'" << std::endl;
        dataStream << "load 'rR.plt'" << std::endl;
        dataStream << "load 'fF.plt'" << std::endl;
        dataStream << "load 'r2R2.plt'" << std::endl;
        dataStream << "unset multiplot" << std::endl;

        dataStream.close();

        std::string command = "cd " + outDir + "; " + "gnuplot " + plotName + ".plt";
        command += "; cd ..";


        std::cout << system(command.c_str());

    }

}




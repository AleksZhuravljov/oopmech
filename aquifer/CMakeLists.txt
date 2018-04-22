cmake_minimum_required(VERSION 3.7)
project(aquifer)

set(CMAKE_CXX_STANDARD 11)

find_package(Eigen3 3.1.2)
include_directories(${EIGEN3_INCLUDE_DIRS})

set(SOURCE_FILES

        main.cpp myHeaders.h Aggregator.cpp Aggregator.h CalcData.cpp CalcData.h

        Equation/Equation.h Equation/EquationP.h Equation/EquationS.h

        Convection/ConvectionPars.cpp Convection/ConvectionPars.h Convection/Convection.cpp Convection/Convection.h
        Convection/ConvectionS.cpp Convection/ConvectionS.h Convection/ConvectionP.cpp Convection/ConvectionP.h

        Helper/ColorForConsol.h Helper/GetFromFile.h Helper/LinearEquation.cpp Helper/LinearEquation.h Helper/MatrixOperations.cpp
        Helper/MatrixOperations.h Helper/StringAndNumber.h

        Location/Location.cpp Location/Location.h Location/LocationP.cpp Location/LocationP.h Location/LocationS.cpp Location/LocationS.h

        Plot/PlotInterface.cpp Plot/PlotInterface.h Plot/Plot.cpp  Plot/Plot.h
        Plot/PlotPar.cpp Plot/PlotPar.h Plot/PlotPar1D.cpp Plot/PlotPar1D.h Plot/PlotPar2D.cpp Plot/PlotPar2D.h

        States/FuncPars.cpp States/FuncPars.h States/Grid.cpp States/Grid.h)

add_executable(aquifer ${SOURCE_FILES})
target_link_libraries(aquifer ${EIGEN3_LIBRARIES})
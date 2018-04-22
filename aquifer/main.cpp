#include "myHeaders.h"

int main(int narg, char **arg) {

    GetFromFile dataFile(arg[1]);

    std::string calcType = dataFile.getWord<std::string>("CALC_TYPE");

    std::cout << calcType << std::endl;

    if (calcType == "simple2D")
        simple2D(arg[1]);



    allFuncsPlot(arg[1]);


    return 0;
}
#ifndef COLORFORCONSOL_H
#define COLORFORCONSOL_H


#include <iostream>
#include <string>


const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string resetColor("\033[0m");


// std::cout << green << "calculate color" << resetColor << std::endl;


#endif

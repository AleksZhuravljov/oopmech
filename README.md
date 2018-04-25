# Project Title
The C++ object-oriented programming approach in fluid and gas mechanics numerical problems.

## Motivation
Functional programming is the conventional approach for the numerical solutions in the problems of continuum mechanics.
Nevertheless, in the case of complex problems, it becomes really difficult to design,
develop and maintain the source code using functional programming.

This project attempts to understand how deep such numerical models can be based on paradigms of object-oriented programming
and whether this can troubleshoot the abovementioned difficulties.

## Description
The following reservoir engineering [problem](https://github.com/AleksZhuravljov/oopmech/blob/master/aquifer/scheme.png)
is solved:

- two-phase compressible fluids (methane and water)
- a two-dimensional arial grid system
- there is a production well in the center of the reservoir
- the volume of the boundary grid blocks is artificially increased
using pore volume multipliers when modelling the aquifer

## Getting Started

```
git clone https://github.com/AleksZhuravljov/oopmech
cd oopmech/aquifer
cmake CMakeList.txt
make
cd InOut
../aquifer data.txt
```

### Prerequisites

The things you need to install the software and how to install them

```
brew install eigen
brew install cmake
brew install gnuplot
```

## Author

* [**Aleksandr Zhuravljov**](https://github.com/AleksZhuravljov/)


## License

This project is licensed under the Academic Free License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* [**Sergei Iskakov**](https://github.com/iskakoff) for practical advice on writing C++ code 
* [**Zakhar Lanetc**](https://github.com/lanetszb) for model validation using [Eclipse](https://www.software.slb.com/products/eclipse)



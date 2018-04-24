# Project Title
The C++ object-oriented programming algorithmic of fluid and gas mechanics numerical problems.

## Motivation
Functional programming is the conventional approach in the numerical solution of the problems of continuum mechanics.
However, in the case of complex problems with this approach, it becomes really difficult to design, develop and maintain the source code.

This project is an attempt to understand how deep such numerical models can be based on paradigms of object-oriented programming
and whether this can neglect the above difficulties.

## Description
The following reservoir engineering [problem](https://github.com/AleksZhuravljov/oopmech/aquifer/scheme.png) is solving:

- two-phase compressible fluid (methane and water)
- a two-dimensional arial grid
- in the center of the reservoir there is a producing well
- the volume of the boundary grid blocks is artificially increased for modeling the aquifer

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

What things you need to install the software and how to install them

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

* [**Sergei Iskakov**](https://github.com/iskakoff) for practical advice on writing C ++ code 
* [**Zakhar Lanetc**](https://github.com/lanetszb) for model validation



# asmFoam - A multiphase CFD solver with coupled activated sludge biokinetics

`asmFoam` is a multiphase CFD solver that is coupled with an activated sludge model, based on the ASM1 model of Henze et al. (1987). There are currently two oxygen transfer models available, based on: (i) constant, spatially uniform values of `kL` (mass transfer coefficient) and `a` (interfacial area), expressedd as the product, kLa  (ii) dynamically calculated values of `kL`, based on Higbie's penetration theory, and `a`, based on local bubble size and gas volume fraction.

The model is implemented using the [OpenFOAM](https://openfoam.org) libaries for discretization and solution of the governing equations.

## Getting Started

### Prerequisites

Install OpenFOAM and set up paths.

Install ParaView.

### Installation

Build `asmFoam`

## Running the Example Problems

## Authors

- [Chris DeGroot](http://www.eng.uwo.ca/mechanical/faculty/degroot_c/index.html)

## License

- This project is licensed under the GNU General Public License, version 3 (GPL-3.0). See LICENSE.txt for details.

## Acknowledgements

- This work is supported by a research grant from the Natural Sciences and Engineering Research Council of Canada (NSERC) through the Discovery Grants program.

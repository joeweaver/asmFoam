# asmFoam - A multiphase CFD solver with coupled activated sludge biokinetics

`asmFoam` is a multiphase CFD solver that is coupled with an activated sludge model, based on the ASM1 model of Henze et al. (1987). There are currently two oxygen transfer models available, based on: (i) constant, spatially uniform values of `kL` (mass transfer coefficient) and `a` (interfacial area), expressed as the product, kLa  (ii) dynamically calculated values of `kL`, based on Higbie's penetration theory, and `a`, based on local bubble size and gas volume fraction.

The model is implemented using the [OpenFOAM](https://openfoam.org) libraries for discretization and solution of the governing equations.

## Getting Started

### Prerequisites

Install OpenFOAM and set up paths.

Install ParaView.

### Installation

Build `asmFoam`

## Running the Code

Setting up a case for the `asmFoam` solver proceeds similarly to typical `OpenFOAM` cases, with the exception of the additional configuration required by those models implemented specifically for `asmFoam`. It is assumed that the user is generally familiar with using `OpenFOAM` and setting up cases, so a detailed explanation will not be provided here.

### Initial and Boundary Conditions

To use the `asmFoam` solver, boundary and initial conditions must be specified on all additional fields that are solved, using appropriate files in the `0` subdirectory of the main case directory. The additional fields introduced by the `asmFoam` solver are: `SND`, `SNH`, `SNO`, `SO`, `SS`, `XBA`, `XBH`, `XND`, `XP`, and `XS`. The units of all these fields are kilograms per cubic metre.

### ASM Configuration (biokineticsProperties dictionary)

A dictionary file called `biokineticsProperties` must be provided in the `constant` subdirectory to configure the activated sludge model. This file requires a number of dictionaries and parameters to be defined, as outlined below.

The stoichiometry coefficients are defined as follows:

```
stoichiometry
{
    YA     0.24;
    YH     0.67;
    fP     0.08;
    iXB    0.086;
    iXP    0.06;
}
```

Note that all of the stoichiometric coefficients are dimensionless. A description of each parameter is given in the following table:

| Parameter | Description |
| --------- | ----------- |
| YA        | Autotrophic yield |
| YH        | Heterotrophic yield |
| fP        | Fraction of biomass yielding particulate products |
| iXB       | Mass of nitrogen per mass of COD in biomass |
| iXP       | Mass of nitrogen per mass of COD in products from biomass |

The kinetics coefficients are defined as:

```
kinetics
{
    muA         muA   [ 0  0 -1 0 0 0 0] 5.79e-6;
    muH         muH   [ 0  0 -1 0 0 0 0] 3.47e-5;
    KS          KS    [ 1 -3  0 0 0 0 0] 0.02;
    KOA         KOA   [ 1 -3  0 0 0 0 0] 0.0004;
    KOH         KOH   [ 1 -3  0 0 0 0 0] 0.0002;
    KNO         KNO   [ 1 -3  0 0 0 0 0] 0.0005;
    KNH         KNH   [ 1 -3  0 0 0 0 0] 0.001;
    KX          KX    [ 0  0  0 0 0 0 0] 0.02;
    bA          bA    [ 0  0 -1 0 0 0 0] 4.86e-6;
    bH          bH    [ 0  0 -1 0 0 0 0] 4.86e-6;
    ka          ka    [-1  3 -1 0 0 0 0] 9.26e-4;
    kh          kh    [ 0  0 -1 0 0 0 0] 2.31e-5;
    etag        etag  [ 0  0  0 0 0 0 0] 0.8;
    etah        etah  [ 0  0  0 0 0 0 0] 0.4;
}
```

The dimensions of each parameter is specified using the OpenFOAM convention, where each value corresponds to the power of each base unit, where the order of the dimensions is Mass [kilogram, kg], Length [metre, m], Time [second, s], Temperature [Kelvin, K], Quantity [mole, mol], Current [Ampere, A], Luminous Intensity [candela, cd]. A description of each parameter is given in the following table:

| Parameter | Description | Units |
| --------- | ----------- | ----- |
| muA       | Maximum specific growth rate for autotrophic biomass | s^-1 |
| muH       | Maximum specific growth rate for heterotrophic biomass | s^-1 |
| KS        | Half-saturation coefficient for heterotrophic biomass | kg/m^3 |
| KOA       | Oxygen half-saturation coefficient for autotrophic biomass | kg/m^3 |
| KOH       | Oxygen half-saturation coefficient for heterotrophic biomass | kg/m^3 |
| KNO       | Nitrate half-saturation coefficient for denitrifying heterotrophic biomass | kg/m^3 |
| KNH       | Ammonia half-saturation coefficient for autotrophic biomass | kg/m^3 |
| KX        | Half-saturation coefficient for hydrolysis of slowly biodegradable substrate | dimensionless |
| bA        | Decay coefficient for autotrophic biomass | s^-1 |
| bH        | Decay coefficient for heterotrophic biomass | s^-1 |
| ka        | Ammonification rate | m^3/kg/s |
| kh        | Maximum specific hydrolysis rate | s^-1 |
| etag      | Correction factor for muH under anoxic conditions | dimensionless |
| etah      | Correction factor for hydrolysis under anoxic conditions | dimensionless |

The diffusivities of each species in water are defined as:

```
diffusivities
{
    DSS         DSS    [ 0 2 -1 0 0 0 0] 1e-6;
    DSO         DSO    [ 0 2 -1 0 0 0 0] 1e-6;
    DSNO        DSNO   [ 0 2 -1 0 0 0 0] 1e-6;
    DSNH        DSNH   [ 0 2 -1 0 0 0 0] 1e-6;
    DSND        DSND   [ 0 2 -1 0 0 0 0] 1e-6;
    DXS         DXS    [ 0 2 -1 0 0 0 0] 1e-9;
    DXBH        DXBH   [ 0 2 -1 0 0 0 0] 1e-9;
    DXBA        DXBA   [ 0 2 -1 0 0 0 0] 1e-9;
    DXP         DXP    [ 0 2 -1 0 0 0 0] 1e-9;
    DXND        DXND   [ 0 2 -1 0 0 0 0] 1e-9;
}
```

The dimensions of each diffusivity is m^2/s. It is recommended that for particulate species, which do not diffuse in water, a small diffusivity is specified for numerical stability.

An oxygen transfer model must be specified to determine the rate of oxygen transfer from the gas phase to the liquid phase. The model can be specified as either `constant` or `dynamic`. The `constant` model assumes a single, spatially uniform value for `kLa` and is specified through the following dictionary entry:

```
oxygenTransferModel
{
    type constant;
    constantCoeffs
    {
        kLa      kLa   [ 0 0 -1 0 0 0 0 ] 0.00243;
    }
}
```

The `dynamic` model is specified as follows:

```
oxygenTransferModel
{
    type dynamic;
    dynamicCoeffs
    {
        DL       DL    [ 0 2 -1 0 0 0 0 ] 1.97e-9;
    }
}
```

where `DL` is the diffusivity of oxygen in water. For both models, the oxygen saturation concentration must be specified as follows:

```
SOsat    SOsat [ 1 -3  0 0 0 0 0] 0.00928;
```

Other parameters that need to be specified are given by example as follows:

```
ScT        0.7;
liquidName water;
gasName    air;
```

A description of each of these parameters is given in the following table:

| Parameter  | Description |
| ---------- | ----------- |
| ScT        | Turbulent Schmidt number, used to determine turbulent diffusivity for each species |
| liquidName | Name of the liquid phase, as specified in `phaseProperties` dictionary |
| gasName    | Name of the gas phase, as specified in `phaseProperties` dictionary |

### No Flow Verification Problem

All test cases are available in the [asmFoamTests](https://bitbucket.org/cdegroot/asmfoamtests/) Git repository. The most basic example is called ``NoFlow`` and can be found in the ``Verification`` directory of the test repository. As the name suggests, there is no flow involved in this problem, which means that the correct numerical solution to the problem can be found by simply solving the ordinary differential equations representing the ASM1 model.

## Authors

- [Chris DeGroot](http://www.eng.uwo.ca/mechanical/faculty/degroot_c/index.html)

## License

- This project is licensed under the GNU General Public License, version 3 (GPL-3.0). See LICENSE.txt for details.

## Acknowledgements

- This work is supported by a research grant from the Natural Sciences and Engineering Research Council of Canada (NSERC) through the Discovery Grants program.

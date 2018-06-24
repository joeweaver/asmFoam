# asmFoam - A multiphase CFD solver with coupled activated sludge biokinetics

`asmFoam` is a multiphase CFD solver that is coupled with an activated sludge model, based on the ASM1 model of Henze et al. (1987). There are currently two oxygen transfer models available, based on: (i) constant, spatially uniform values of `kL` (mass transfer coefficient) and `a` (interfacial area), expressedd as the product, kLa  (ii) dynamically calculated values of `kL`, based on Higbie's penetration theory, and `a`, based on local bubble size and gas volume fraction.

The model is implemented using the [OpenFOAM](https://openfoam.org) libaries for discretization and solution of the governing equations.

## Getting Started

### Prerequisites

Install OpenFOAM and set up paths.

Install ParaView.

### Installation

Build `asmFoam`

## Running the Code

Setting up a case for the `asmFoam` solver proceeds similarly to typical `OpenFOAM` cases, with the exception of the additional configuration required by those models implemented specifically for `asmFoam`. It is assumed that the user is generally familiar with using `OpenFOAM` and setting up cases, so a detailed explanation will not be provided here.

To use the `asmFoam` solver, boundary and initial conditions must be specified on all additional fields that are solved, using appropriate files in the `0` subdirectory of the main case directory. The additional fields introduced by the `asmFoam` solver are: `SND`, `SNH`, `SNO`, `SO`, `SS`, `XBA`, `XBH`, `XND`, `XP`, and `XS`. The units of all these fields are kilograms per cubic metre.

A dictionary file called `biokineticsProperties` must be provided in the `constant` subdirectory to configure the activated sludge model. A sample file is included below (neglecting any comments and headers).

```
stoichiometry
{
    YA          YA  [0 0 0 0 0 0 0] 0.24;
    YH          YH  [0 0 0 0 0 0 0] 0.67;
    fP          fP  [0 0 0 0 0 0 0] 0.08;
    iXB         iXB [0 0 0 0 0 0 0] 0.086;
    iXP         iXP [0 0 0 0 0 0 0] 0.06;
}

kinetics
{
    muH         muH   [ 0  0 -1 0 0 0 0] 3.47e-5;
    KS          KS    [ 1 -3  0 0 0 0 0] 0.02;
    KOH         KOH   [ 1 -3  0 0 0 0 0] 0.0002;
    KNO         KNO   [ 1 -3  0 0 0 0 0] 0.0005;
    bH          bH    [ 0  0 -1 0 0 0 0] 4.86e-6;
    etag        etag  [ 0  0  0 0 0 0 0] 0.8;
    etah        etah  [ 0  0  0 0 0 0 0] 0.4;
    kh          kh    [ 0  0 -1 0 0 0 0] 2.31e-5;
    KX          KX    [ 0  0  0 0 0 0 0] 0.02;
    muA         muA   [ 0  0 -1 0 0 0 0] 5.79e-6;
    KNH         KNH   [ 1 -3  0 0 0 0 0] 0.001;
    KOA         KOA   [ 1 -3  0 0 0 0 0] 0.0004;
    bA          bA    [ 0  0 -1 0 0 0 0] 4.86e-6;
    ka          ka    [-1  3 -1 0 0 0 0] 9.26e-4;
}

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

oxygenTransferModel
{
    type constant;
    constantCoeffs
    {
        kLa      kLa   [ 0  0 -1 0 0 0 0] 0.00243;
    }
}

SOsat    SOsat [ 1 -3  0 0 0 0 0] 0.00928;

ScT 0.7;
liquidName water;
gasName    air;
```

### No Flow Verification Problem

All test cases are available in the [asmFoamTests](https://bitbucket.org/cdegroot/asmfoamtests/) Git repository. The most basic example is called ``NoFlow`` and can be found in the ``Verification`` directory of the test repository. As the name suggests, there is no flow involved in this problem, which means that the correct numerical solution to the problem can be found by simply solving the ordinary differential equations representing the ASM1 model.

## Authors

- [Chris DeGroot](http://www.eng.uwo.ca/mechanical/faculty/degroot_c/index.html)

## License

- This project is licensed under the GNU General Public License, version 3 (GPL-3.0). See LICENSE.txt for details.

## Acknowledgements

- This work is supported by a research grant from the Natural Sciences and Engineering Research Council of Canada (NSERC) through the Discovery Grants program.

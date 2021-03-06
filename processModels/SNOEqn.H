// Scalar transport equation for nitrate and nitrite nitrogen

fvScalarMatrix SNOEqn
(
    fvm::ddt(alphaLiquid, SNO)
    + fvm::div(liquidPhase.alphaPhi(), SNO)
    - fvm::laplacian(fvc::interpolate(alphaLiquid)*DSNO, SNO)
    ==
    - alphaLiquid*(1-YH)/2.86/YH*rhoHeterotrophAnoxicGrowth
    + alphaLiquid*rhoAutotrophAerobicGrowth/YA
    - fvm::Sp(dissipationCoeff, SNO)
    + dissipationCoeff*SNO
);

SNOEqn.relax();
SNOEqn.solve();

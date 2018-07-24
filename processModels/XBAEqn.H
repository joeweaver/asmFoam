// Scalar transport equation for active autotrophic biomass

fvScalarMatrix XBAEqn
(
    fvm::ddt(alphaLiquid, XBA)
    + fvm::div(liquidPhase.alphaPhi(), XBA)
    - fvm::laplacian(fvc::interpolate(alphaLiquid)*DXBA, XBA)
    ==
      alphaLiquid*rhoAutotrophAerobicGrowth
    - alphaLiquid*rhoAutotrophDecay
    - fvm::Sp(dissipationCoeff, XBA)
    + dissipationCoeff*XBA
);

XBAEqn.relax();
XBAEqn.solve();

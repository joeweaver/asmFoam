fvScalarMatrix XBHEqn
(
    fvm::ddt(alphaLiquid, XBH)
    + fvm::div(liquidPhase.alphaPhi(), XBH)
    - fvm::laplacian(alphaLiquid*(turbulence->nut()/ScT + DXBH), XBH)
    ==
      alphaLiquid*rhoHeterotrophAerobicGrowth
    + alphaLiquid*rhoHeterotrophAnoxicGrowth
    - alphaLiquid*rhoHeterotrophDecay
    - fvm::Sp(dissipationCoeff, XBH)
);

XBHEqn.relax();
XBHEqn.solve();

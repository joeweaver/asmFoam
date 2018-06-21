fvScalarMatrix XBAEqn
(
    fvm::ddt(alphaLiquid, XBA)
    + fvm::div(liquidPhase.alphaPhi(), XBA)
    - fvm::laplacian(alphaLiquid*(turbulence->nut()/ScT + DXBA), XBA)
    ==
      alphaLiquid*rhoAutotrophAerobicGrowth
    - alphaLiquid*rhoAutotrophDecay
    - fvm::Sp(dissipationCoeff, XBA)
);

XBAEqn.relax();
XBAEqn.solve();

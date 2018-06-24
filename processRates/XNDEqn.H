fvScalarMatrix XNDEqn
(
    fvm::ddt(alphaLiquid, XND)
    + fvm::div(liquidPhase.alphaPhi(), XND)
    - fvm::laplacian(alphaLiquid*(turbulence->nut()/ScT + DXND), XND)
    ==
      alphaLiquid*(iXB-fP*iXP)*rhoHeterotrophDecay
    + alphaLiquid*(iXB-fP*iXP)*rhoAutotrophDecay
    - alphaLiquid*rhoOrganicNitrogenHydrolysis
    - fvm::Sp(dissipationCoeff, XND)
);

XNDEqn.relax();
XNDEqn.solve();

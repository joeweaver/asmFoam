fvScalarMatrix XPEqn
(
    fvm::ddt(alphaLiquid, XP)
    + fvm::div(liquidPhase.alphaPhi(), XP)
    - fvm::laplacian(alphaLiquid*(turbulence->nut()/ScT + DXP), XP)
    ==
      alphaLiquid*fP*rhoHeterotrophDecay
    + alphaLiquid*fP*rhoAutotrophDecay
    - fvm::Sp(dissipationCoeff, XP)
);

XPEqn.relax();
XPEqn.solve();

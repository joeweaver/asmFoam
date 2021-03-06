// Scalar transport equation for particulate products arising from biomass decay

fvScalarMatrix XPEqn
(
    fvm::ddt(alphaLiquid, XP)
    + fvm::div(liquidPhase.alphaPhi(), XP)
    - fvm::laplacian(fvc::interpolate(alphaLiquid)*DXP, XP)
    ==
      alphaLiquid*fP*rhoHeterotrophDecay
    + alphaLiquid*fP*rhoAutotrophDecay
    - fvm::Sp(dissipationCoeff, XP)
    + dissipationCoeff*XP
);

XPEqn.relax();
XPEqn.solve();

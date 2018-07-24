// Scalar transport equation for slowly biodegradable substrate

fvScalarMatrix XSEqn
(
    fvm::ddt(alphaLiquid, XS)
    + fvm::div(liquidPhase.alphaPhi(), XS)
    - fvm::laplacian(fvc::interpolate(alphaLiquid)*DXS, XS)
    ==
      alphaLiquid*(1-fP)*rhoHeterotrophDecay
    + alphaLiquid*(1-fP)*rhoAutotrophDecay
    - alphaLiquid*rhoOrganicHydrolysis
    - fvm::Sp(dissipationCoeff, XS)
    + dissipationCoeff*XS
);

XSEqn.relax();
XSEqn.solve();

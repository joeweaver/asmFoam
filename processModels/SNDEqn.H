// Scalar transport equation for slowly biodegradable organic nitrogen

fvScalarMatrix SNDEqn
(
    fvm::ddt(alphaLiquid, SND)
    + fvm::div(liquidPhase.alphaPhi(), SND)
    - fvm::laplacian(fvc::interpolate(alphaLiquid)*DSND, SND)
    ==
    - alphaLiquid*rhoAmmonification
    + alphaLiquid*rhoOrganicNitrogenHydrolysis
    - fvm::Sp(dissipationCoeff, SND)
    + dissipationCoeff*SND
);

SNDEqn.relax();
SNDEqn.solve();

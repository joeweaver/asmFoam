Info<< "Reading biokineticsProperties" << endl;

IOdictionary biokineticsProperties
(
    IOobject
    (
        "biokineticsProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

Info << "  Reading stoichiometric parameters" << endl;

Info << "    Reading autotrophic yield, YA" << endl;

dimensionedScalar YA
(   
    biokineticsProperties.subDict("stoichiometry").lookup("YA")
);

Info << "    Reading heterotrophic yield, YH" << endl;

dimensionedScalar YH
(
    biokineticsProperties.subDict("stoichiometry").lookup("YH")
);

Info << "    Reading fraction of biomass leading to particulate products, fP" << endl;

dimensionedScalar fP
(
    biokineticsProperties.subDict("stoichiometry").lookup("fP")
);

Info << "    Reading mass of nitrogen per mass of COD in biomass, iXB" << endl;

dimensionedScalar iXB
(
    biokineticsProperties.subDict("stoichiometry").lookup("iXB")
);

Info << "    Reading mass of nitrogen per mass of COD in products from biomass, iXP" << endl;

dimensionedScalar iXP
(
    biokineticsProperties.subDict("stoichiometry").lookup("iXP")
);

Info << "  Reading kinetic parameters" << endl;

Info << "    Reading maximum specific growth rate for heterotrophic biomass, muH" << endl;

dimensionedScalar muH
(
    biokineticsProperties.subDict("kinetics").lookup("muH")
);

Info << "    Reading half-saturation coefficient for heterotrophic biomass, KS" << endl;

dimensionedScalar KS
(
    biokineticsProperties.subDict("kinetics").lookup("KS")
);

Info << "    Reading oxygen half-saturation coefficient for heterotrophic biomass, KOH" << endl;

dimensionedScalar KOH
(
    biokineticsProperties.subDict("kinetics").lookup("KOH")
);

Info << "    Reading nitrate half-saturation coefficient for denitrifying heterotrophic biomass, KNO" << endl;

dimensionedScalar KNO
(
    biokineticsProperties.subDict("kinetics").lookup("KNO")
);

Info << "    Reading decay coefficient for heterotrophic biomass, bH" << endl;

dimensionedScalar bH
(
    biokineticsProperties.subDict("kinetics").lookup("bH")
);

Info << "    Reading maximum specific growth rate for autotrophic biomass, muA" << endl;

dimensionedScalar muA
(
    biokineticsProperties.subDict("kinetics").lookup("muA")
);

Info << "    Reading ammonia half-saturation coefficient for autotrophic biomass, KNH" << endl;

dimensionedScalar KNH
(
    biokineticsProperties.subDict("kinetics").lookup("KNH")
);

Info << "    Reading oxygen half-saturation coefficient for autotrophic biomass, KOA" << endl;

dimensionedScalar KOA
(
    biokineticsProperties.subDict("kinetics").lookup("KOA")
);

Info << "    Reading decay coefficient for autotrophic biomass, bA" << endl;

dimensionedScalar bA
(
    biokineticsProperties.subDict("kinetics").lookup("bA")
);

Info << "    Reading correction factor for muH under anoxic conditions, etag" << endl;

dimensionedScalar etag
(
    biokineticsProperties.subDict("kinetics").lookup("etag")
);

Info << "    Reading ammonification rate, ka" << endl;

dimensionedScalar ka
(
    biokineticsProperties.subDict("kinetics").lookup("ka")
);

Info << "    Reading maximum specific hydrolysis rate, kh" << endl;

dimensionedScalar kh
(
    biokineticsProperties.subDict("kinetics").lookup("kh")
);

Info << "    Reading half-saturation coefficient for hydrolysis of slowly biodegradable substrate, KX" << endl;

dimensionedScalar KX
(
    biokineticsProperties.subDict("kinetics").lookup("KX")
);

Info << "    Reading correction factor for hydrolysis under anoxic conditions, etah" << endl;

dimensionedScalar etah
(
    biokineticsProperties.subDict("kinetics").lookup("etah")
);

Info << "  Reading oxygen saturation concentration, SOsat" << endl;

dimensionedScalar SOsat
(
    biokineticsProperties.lookup("SOsat")
);

Info << "  Reading turbulent Schmidt number, ScT" << endl;
scalar ScT
(
    readScalar(biokineticsProperties.lookup("ScT"))
);

Info << "  Reading liquid phase name, liquidName" << endl;
word liquidName
(
    biokineticsProperties.lookup("liquidName")
);

Info << "  Reading gas phase name, gasName" << endl;
word gasName
(
    biokineticsProperties.lookup("gasName")
);

Info << endl;

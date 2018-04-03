Info << "Reading field SI (soluble inert organic matter)\n" << endl;

volScalarField SI
(
    IOobject
    (
        "SI",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field SS (Readily biodegradable substrate)\n" << endl;

volScalarField SS
(
    IOobject
    (
        "SS",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field XI (particulate inert organic matter)\n" << endl;

volScalarField XI
(
    IOobject
    (
        "XI",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field XS (slowly biodegradable substrate)\n" << endl;

volScalarField XS
(
    IOobject
    (
        "XS",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field XBH (active heterotrophic biomass)\n" << endl;

volScalarField XBH
(
    IOobject
    (
        "XBH",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field XBA (active autotrophic biomass)\n" << endl;

volScalarField XBA
(
    IOobject
    (
        "XBA",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field XP (particulate products arising from biomass decay)\n" << endl;

volScalarField XP
(
    IOobject
    (
        "XP",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field SO (oxygen)\n" << endl;

volScalarField SO
(
    IOobject
    (
        "SO",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field SNO (nitrate and nitrite)\n" << endl;

volScalarField SNO
(
    IOobject
    (
        "SNO",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field SNH (ammonia and ammonium nitrogen)\n" << endl;

volScalarField SNH
(
    IOobject
    (
        "SNH",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field SND (soluble biodegradable organic nitrogen)\n" << endl;

volScalarField SND
(
    IOobject
    (
        "SND",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field XND (particulate biodegradable organic nitrogen)\n" << endl;

volScalarField XND
(
    IOobject
    (
        "XND",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << "Reading field SALK (alkalinity)\n" << endl;

volScalarField SALK
(
    IOobject
    (
        "SALK",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


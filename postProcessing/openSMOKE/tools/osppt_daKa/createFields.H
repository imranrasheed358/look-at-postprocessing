#include "createRDeltaT.H"

Info<< "Reading thermophysical properties\n" << endl;
autoPtr<psiReactionThermo> pThermo(psiReactionThermo::New(mesh));
psiReactionThermo& thermo = pThermo();
thermo.validate(args.executable(), "h", "e");

basicSpecieMixture& composition = thermo.composition();
PtrList<volScalarField>& Y = composition.Y();

const word inertSpecie(thermo.get<word>("inertSpecie"));
if (!composition.species().found(inertSpecie))
{
    FatalIOErrorIn(args.executable().c_str(), thermo)
        << "Inert specie " << inertSpecie << " not found in available species "
        << composition.species() << exit(FatalIOError);
}
/*
volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh
    ),
    thermo.rho()
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField& p = thermo.p();

#include "compressibleCreatePhi.H"

pressureControl pressureControl(p, rho, pimple.dict(), false);

mesh.setFluxRequired(p.name());

Info << "Creating turbulence model.\n" << nl;
autoPtr<compressible::turbulenceModel> turbulence
(
    compressible::turbulenceModel::New
    (
        rho,
        U,
        phi,
        thermo
    )
);

Info<< "Creating reaction model\n" << endl;
autoPtr<CombustionModel<psiReactionThermo>> reaction
(
    CombustionModel<psiReactionThermo>::New(thermo, turbulence())
);

multivariateSurfaceInterpolationScheme<scalar>::fieldTable fields;

forAll(Y, i)
{
    fields.add(Y[i]);
}
fields.add(thermo.he());

volScalarField Qdot
(
    IOobject
    (
        "Qdot",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimEnergy/dimVolume/dimTime, Zero)
);

#include "createDpdt.H"

#include "createK.H"

#include "createMRF.H"
#include "createFvOptions.H"
*/

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        runTime,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
mesh
);
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        runTime,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
mesh
);
thermo.p() = p;

//----added for osppt_daKa----//
volScalarField k
(
    IOobject
    (
        "k",
        runTime.timeName(),
        runTime,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
mesh
);
volScalarField epsilon
(
    IOobject
    (
        "epsilon",
        runTime.timeName(),
        runTime,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
mesh
);
volScalarField Z
(
    IOobject
    (
        "Z",
        runTime.timeName(),
        runTime,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
mesh
);
//---- ----//

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    asmFoam

Description
    Solver for an activated sludge system based on ASM1 biokinetics.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "twoPhaseSystem.H"
#include "phaseCompressibleTurbulenceModel.H"
#include "pimpleControl.H"
#include "localEulerDdtScheme.H"
#include "fvcSmooth.H"
#include "oxygenTransferModel.H"

namespace Foam
{
    tmp<volScalarField> byDt(const volScalarField& vf)
    {
        if (fv::localEulerDdt::enabled(vf.mesh()))
        {
            return fv::localEulerDdt::localRDeltaT(vf.mesh())*vf;
        }
        else
        {
            return vf/vf.mesh().time().deltaT();
        }
    }

    tmp<surfaceScalarField> byDt(const surfaceScalarField& sf)
    {
        if (fv::localEulerDdt::enabled(sf.mesh()))
        {
            return fv::localEulerDdt::localRDeltaTf(sf.mesh())*sf;
        }
        else
        {
            return sf/sf.mesh().time().deltaT();
        }
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "postProcess.H"

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createTimeControls.H"
    #include "createFields.H"
    #include "createFieldRefs.H"

    #include "readBiokineticsProperties.H"
    #include "createAsmFields.H"

    if (!LTS)
    {
        #include "CourantNo.H"
        #include "setInitialDeltaT.H"
    }

    Switch faceMomentum
    (
        pimple.dict().lookupOrDefault<Switch>("faceMomentum", false)
    );

    Switch implicitPhasePressure
    (
        mesh.solverDict(alpha1.name()).lookupOrDefault<Switch>
        (
            "implicitPhasePressure", false
        )
    );

    #include "pUf/createRDeltaTf.H"
    #include "pUf/createDDtU.H"

    #include "fluidPhases.H"
    #include "createOxygenTransferModel.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "readTimeControls.H"

        int nEnergyCorrectors
        (
            pimple.dict().lookupOrDefault<int>("nEnergyCorrectors", 1)
        );

        if (LTS)
        {
            #include "setRDeltaT.H"
            if (faceMomentum)
            {
                #include "setRDeltaTf.H"
            }
        }
        else
        {
            #include "CourantNos.H"
            #include "setDeltaT.H"
        }

        runTime++;
        Info<< "Time = " << runTime.timeName() << nl << endl;

        // --- ASM rates
        #include "asmRates.H"

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            if (solveFlow)
            {
                fluid.solve();
                fluid.correct();

                #include "YEqns.H"

                if (faceMomentum)
                {
                    #include "pUf/UEqns.H"
                    #include "EEqns.H"
                    #include "pUf/pEqn.H"
                    #include "pUf/DDtU.H"
                }
                else
                {
                    #include "pU/UEqns.H"
                    #include "EEqns.H"
                    #include "pU/pEqn.H"
                }

                fluid.correctKinematics();

                if (pimple.turbCorr())
                {
                    fluid.correctTurbulence();
                }
            }

            // --- Calculate dissipation coefficient for pure gas regions
            dissipationCoeff = 0.001*pos(alphaGas - 0.99)/runTime.deltaT();

            // --- Update scalar diffusivities
            surfaceScalarField mask = fvc::interpolate(alphaGas);
            forAll(mask, faceI)
            {
                if (alphaGas[mesh.owner()[faceI]] > 0.2 || alphaGas[mesh.neighbour()[faceI]] > 0.2)
                {
                    mask[faceI] = 0;
                }
                else
                {
                    mask[faceI] = 1;
                }
            }
            surfaceScalarField DT = fvc::interpolate(liquidPhase.turbulence().nuEff()/ScT);
            DSS  = (DT + DSSValue)*mask;
            DXS  = (DT + DXSValue)*mask;
            DXBH = (DT + DXBHValue)*mask;
            DXBA = (DT + DXBAValue)*mask;
            DXP  = (DT + DXPValue)*mask;
            DSO  = (DT + DSOValue)*mask;
            DSNO = (DT + DSOValue)*mask;
            DSNH = (DT + DSNHValue)*mask;
            DSND = (DT + DSNDValue)*mask;
            DXND = (DT + DXNDValue)*mask;

            // --- Solve ASM scalar equations
            #include "SSEqn.H"
            #include "XSEqn.H"
            #include "XBHEqn.H"
            #include "XBAEqn.H"
            #include "XPEqn.H"
            #include "SOEqn.H"
            #include "SNOEqn.H"
            #include "SNHEqn.H"
            #include "SNDEqn.H"
            #include "XNDEqn.H"

        }

        runTime.write();

        Info<< "ExecutionTime = "
            << runTime.elapsedCpuTime()
            << " s\n\n" << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //

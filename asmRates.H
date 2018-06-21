// Define small concentration to avoid divide by zero
dimensionedScalar small = dimensionedScalar("small", dimensionSet(1,-3,0,0,0,0,0), SMALL);

// Define multiplier to zero reaction rates in pure gas regions
volScalarField mult = 1 - pos(alphaGas - 0.5);

// Define process rates
volScalarField rhoHeterotrophAerobicGrowth = mult * muH * SS/(KS + SS) * SO/(KOH + SO) * XBH;
volScalarField rhoHeterotrophAnoxicGrowth = mult * muH * SS/(KS + SS) * KOH/(KOH + SO) * SNO/(KNO + SNO) * etag * XBH;
volScalarField rhoAutotrophAerobicGrowth = mult * muA * SNH/(KNH + SNH) * SO/(KOA + SO) * XBA;
volScalarField rhoHeterotrophDecay = mult * bH * XBH;
volScalarField rhoAutotrophDecay = mult * bA * XBA;
volScalarField rhoAmmonification = mult * ka * SND * XBH;
volScalarField rhoOrganicHydrolysis = mult * kh * XS/(KX*XBH + max(XS, small)) * (SO/(KOH + SO) + etah * KOH/(KOH + SO) * SNO/(KNO + SNO)) * XBH;
volScalarField rhoOrganicNitrogenHydrolysis = mult * rhoOrganicHydrolysis * XND / max(XS, small);

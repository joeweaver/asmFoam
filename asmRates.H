volScalarField rhoHeterotrophAerobicGrowth = muH * SS/(KS + SS) * SO/(KOH + SO) * XBH;
volScalarField rhoHeterotrophAnoxicGrowth = muH * SS/(KS + SS) * KOH/(KOH + SO) * SNO/(KNO + SNO) * etag * XBH;
volScalarField rhoAutotrophAerobicGrowth = muA * SNH/(KNH + SNH) * SO/(KOA + SO) * XBA;
volScalarField rhoHeterotrophDecay = bH * XBH;
volScalarField rhoAutotrophDecay = bA * XBA;
volScalarField rhoAmmonification = ka * SND * XBH;
volScalarField rhoOrganicHydrolysis = kh * XS/XBH/(KX + XS/XBH) * (SO/(KOH + SO) + etah * KOH/(KOH + SO) * SNO/(KNO + SNO)) * XBH;
volScalarField rhoOrganicNitrogenHydrolysis = rhoOrganicHydrolysis * XND / XS;

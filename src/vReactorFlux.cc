#include "vReactorFlux.hh"
#include <vector>


vReactorFlux::vReactorFlux(TString modelName)
{
	mvConstant = new vConstant();
	mModelName = modelName;
	mFissionFraction = { 0.5, 0.1, 0.3, 0.1 };
	mReleasedEnergy = { 201.7, 205.0, 210.0, 212.4 }; // MeV
	Initialization();
}


vReactorFlux::~vReactorFlux() {}


void vReactorFlux::Initialization()
{
	const double Day2Sec = 8.64E+04;
	const double GW2MeV = 6.2415E+21;

	double energyPerFission = 0;
	for (int i = 0; i < 4; i++)
		energyPerFission += mFissionFraction[i] * mReleasedEnergy[i];
	double NFissionPerSecond = mThermalPower * GW2MeV / energyPerFission;
	mDistance = mDistance * 100; // m -> cm

	mNeutrinoFlux0 = NFissionPerSecond * Day2Sec / 4. / TMath::Pi() / mDistance / mDistance;
}


void vReactorFlux::SetDistance(double distance)
{
	mDistance = distance;
	Initialization();
}


void vReactorFlux::SetFissionFraction(std::vector<double> ff)
{
	mFissionFraction = ff;
	Initialization();
}


void vReactorFlux::SetReleasedEnergy(std::vector<double> re)
{
	mReleasedEnergy = re;
	Initialization();
}


double vReactorFlux::GetReactorNeutrinoFlux(double E, int iso)
{
	if (E < 0) return 0;
	double result;
	if (mModelName == "Gutlein")
	{
		result = GetReactvFlux_Gutlein(E, iso);
	}
	else
	{
		result = GetReactvFlux_HuberMuller(E, iso);
	}
	return result;
}


double vReactorFlux::GetReactvFlux_Gutlein(double E, int iso)
{
	if (E < 0) return 0;
	double result;
	if (iso == 0)
	{
		result = GetReactvFlux_Gutlein_Total(E);
	}
	else
	{
		result = GetReactvFlux_Gutlein_Isotope(E, iso);
	}
	return result;
}


double vReactorFlux::GetReactvFlux_HuberMuller(double E, int iso)
{
	if (E < 0) return 0;
	double result;
	if (iso == 0)
	{
		result = GetReactvFlux_HuberMuller_Total(E);
	}
	else
	{
		result = GetReactvFlux_HuberMuller_Isotope(E, iso);
	}
	return result;
}


double vReactorFlux::GetReactvFlux_Gutlein_Total(double E)
{
	if (E < 0) return 0;
	double result = 0;
	for (int iso = 1; iso <= 3; iso++)
	{
		result += GetReactvFlux_Gutlein_Isotope(E, iso);
	}
	if (result < 0) result = 0;
	return result;
}


double vReactorFlux::GetReactvFlux_Gutlein_Isotope(double E, int iso)
{
	if (E < 0) return 0;
	E = E * 1000; // MeV -> keV
	double result = 0;

	int isoindex = iso - 1;
	if (iso > 2) return 0;

	const int niso = 3;
	double ff[niso] = { 0, 0, 0 };

	double tot_ff = 0;
	for (int i = 0; i < niso; i++)
		tot_ff += mFissionFraction[i];
	for (int i = 0; i < niso; i++)
		ff[i] = mFissionFraction[i] / tot_ff;

	std::vector<double> par = mvConstant->GetGutleinConstant(iso);

	double A0 = par[0], A1 = par[1];
	double a0 = par[2], a1 = par[3], a2 = par[4];

	double flux = a0 * (A0 - A1) - a1 * A0 + a2 * A1;
	flux *= A0 * (TMath::Exp(-E / a0) - TMath::Exp(-E / a1)) + A1 * (TMath::Exp(-E / a2) - TMath::Exp(-E / a0));
	flux *= 0.0001;

	result = ff[isoindex] * flux * mNeutrinoFlux0;

	if (result < 0) result = 0;
	return result;
}


double vReactorFlux::GetReactvFlux_HuberMuller_Total(double E)
{
	if (E < 0) return 0;
	double result = 0;
	for (int iso = 1; iso <= 3; iso++)
	{
		result += GetReactvFlux_HuberMuller_Isotope(E, iso);
	}
	if (result < 0) result = 0;
	return result;
}


double vReactorFlux::GetReactvFlux_HuberMuller_Isotope(double E, int iso)
{
	if (E < 0) return 0;
	if (iso > 4) return 0;
	double result = 0;
	int isoindex = iso - 1;

	std::vector<double> par = mvConstant->GetHuberMullerConstant(iso);

	double E2 = E * E;
	double E3 = E2 * E;
	double E4 = E3 * E;
	double E5 = E4 * E;
	std::vector<double> Earr = { 1, E, E2, E3, E4, E5 };

	for (int i = 0; i < 6; i++)
	{
		result += par[i] * Earr[i];
	}
	result = TMath::Exp(result);

	result *= mFissionFraction[isoindex] * mNeutrinoFlux0;

	if (result < 0) result = 0;
	return result;
}
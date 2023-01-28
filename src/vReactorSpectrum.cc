#include "../header/vReactorSpectrum.hh"
#include "../header/vConstant.hh"


vReactorSpectrum::vReactorSpectrum(TString modelName)
{
	fModelName = modelName;
	fFissionFraction = { 0.5, 0.1, 0.3, 0.1 };
	fReleasedEnergy = { 201.7, 205.0, 210.0, 212.4 }; // MeV
	Initialization();
}


void vReactorSpectrum::Initialization()
{
	const double SecPerDay = 8.64E+04;
	const double GW2MeV = 6.2415E+21;

	double energyPerFission = 0;
	for (int i = 0; i < 4; i++)
		energyPerFission += fFissionFraction[i] * fReleasedEnergy[i];
	double NFissionPerSecond = fThermalPower * GW2MeV / energyPerFission;
	fNeutrinoCurrent0 = NFissionPerSecond * SecPerDay;
}


void vReactorSpectrum::PrintInfo() const
{
	cout << "<vEnergySpectrum->vNeutrinoSpectrum->vReactorSpectrum>" << endl;
	cout << "    Thermal Power (GWth)  : " << fThermalPower << endl;
	cout << "    Fission Fraction      : ["
		<< fFissionFraction[0] << ", "
		<< fFissionFraction[1] << ", "
		<< fFissionFraction[2] << ", "
		<< fFissionFraction[3] << "]" << endl;
	cout << "    Released Energy (MeV) : ["
		<< fReleasedEnergy[0] << ", "
		<< fReleasedEnergy[1] << ", "
		<< fReleasedEnergy[2] << ", "
		<< fReleasedEnergy[3] << "]" << endl;
}


void vReactorSpectrum::SetThermalPower(double thermalPower)
{
	fThermalPower = thermalPower;
	Initialization();
}


void vReactorSpectrum::SetFissionFraction(std::vector<double> ff)
{
	fFissionFraction = ff;
	Initialization();
}


void vReactorSpectrum::SetReleasedEnergy(std::vector<double> re)
{
	fReleasedEnergy = re;
	Initialization();
}


double vReactorSpectrum::GetCurrent(double E) const
{
	return GetCurrent(E, 0);
}


double vReactorSpectrum::GetCurrent(double E, int iso) const
{
	if (E < 0) return 0;
	double result;
	if (fModelName == "Gutlein")
	{
		result = GetReactvCurrent_Gutlein(E, iso);
	}
	else
	{
		result = GetReactvCurrent_HuberMueller(E, iso);
	}
	return result;
}


double vReactorSpectrum::GetReactvCurrent_Gutlein(double E, int iso) const
{
	if (E < 0) return 0;
	double result;
	if (iso == 0)
	{
		result = GetReactvCurrent_Gutlein_Total(E);
	}
	else
	{
		result = GetReactvCurrent_Gutlein_Isotope(E, iso);
	}
	return result;
}


double vReactorSpectrum::GetReactvCurrent_HuberMueller(double E, int iso) const
{
	if (E < 0) return 0;
	double result;
	if (iso == 0)
	{
		result = GetReactvCurrent_HuberMueller_Total(E);
	}
	else
	{
		result = GetReactvCurrent_HuberMueller_Isotope(E, iso);
	}
	return result;
}


double vReactorSpectrum::GetReactvCurrent_Gutlein_Total(double E) const
{
	if (E < 0) return 0;
	double result = 0;
	for (int iso = 1; iso <= 3; iso++)
	{
		result += GetReactvCurrent_Gutlein_Isotope(E, iso);
	}
	if (result < 0) result = 0;
	return result;
}


double vReactorSpectrum::GetReactvCurrent_Gutlein_Isotope(double E, int iso) const
{
	if (E < 0) return 0;
	E = E * 1000; // MeV -> keV
	double result = 0;

	int isoindex = iso - 1;
	if (iso >= 4) return 0;

	const int niso = 3;
	double ff[niso] = { 0, 0, 0 };

	double tot_ff = 0;
	for (int i = 0; i < niso; i++) tot_ff += fFissionFraction[i];
	for (int i = 0; i < niso; i++) ff[i] = fFissionFraction[i] / tot_ff;

	double A0 = GUTLEINCONSTANT[isoindex][0], A1 = GUTLEINCONSTANT[isoindex][1];
	double a0 = GUTLEINCONSTANT[isoindex][2], a1 = GUTLEINCONSTANT[isoindex][3], a2 = GUTLEINCONSTANT[isoindex][4];

	double flux = a0 * (A0 - A1) - a1 * A0 + a2 * A1;
	flux *= A0 * (TMath::Exp(-E / a0) - TMath::Exp(-E / a1)) + A1 * (TMath::Exp(-E / a2) - TMath::Exp(-E / a0));
	flux *= 0.0001; // Why?
	flux *= 1000; // /keV -> /MeV

	result = ff[isoindex] * flux * fNeutrinoCurrent0;

	if (result < 0) result = 0;
	return result;
}


double vReactorSpectrum::GetReactvCurrent_HuberMueller_Total(double E) const
{
	if (E < 0) return 0;
	double result = 0;
	for (int iso = 1; iso <= 3; iso++)
	{
		result += GetReactvCurrent_HuberMueller_Isotope(E, iso);
	}
	if (result < 0) result = 0;
	return result;
}


double vReactorSpectrum::GetReactvCurrent_HuberMueller_Isotope(double E, int iso) const
{
	if (E < 0) return 0;
	if (iso > 4) return 0;
	double result = 0;
	int isoindex = iso - 1;

	double E2 = E * E;
	double E3 = E2 * E;
	double E4 = E3 * E;
	double E5 = E4 * E;
	double Earr[6] = { 1, E, E2, E3, E4, E5 };

	for (int i = 0; i < 6; i++)
	{
		result += HUBERMUELLERCONSTANT[isoindex][i] * Earr[i];
	}
	result = TMath::Exp(result);

	result *= fFissionFraction[isoindex] * fNeutrinoCurrent0;

	if (result < 0) result = 0;
	return result;
}
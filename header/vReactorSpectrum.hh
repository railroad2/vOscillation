#pragma once

#ifndef VREACTORSPECTRUM_HH
#define VREACTORSPECTRUM_HH


#include "vNeutrinoSpectrum.hh"
#include <vector>


class vReactorSpectrum : public vNeutrinoSpectrum
{
public:
	vReactorSpectrum(TString modelName);
	~vReactorSpectrum() {}

	void Initialization();
	void PrintInfo();

	double GetCurrent(double E); // /day
	double GetCurrent(double E, int iso); // /day

	//Setter and Getter
	void                SetThermalPower(double thermalPower);
	void                SetFissionFraction(std::vector<double> ff);
	void                SetReleasedEnergy(std::vector<double> re);
	
	double              GetThermalPower() { return fThermalPower; }
	std::vector<double> GetFissionFraction() { return fFissionFraction; }
	std::vector<double> GetReleasedEnergy() { return fReleasedEnergy; }
	double              GetNeutrinoCurrent0() { return fNeutrinoCurrent0; }

private:
	double GetReactvCurrent_Gutlein(double E, int iso); // 1 : U-235, 2 : U-238, 3 : Pu-239, 4 : Pu-241
	double GetReactvCurrent_HuberMueller(double E, int iso);
	double GetReactvCurrent_Gutlein_Total(double E);
	double GetReactvCurrent_Gutlein_Isotope(double E, int iso);
	double GetReactvCurrent_HuberMueller_Total(double E);
	double GetReactvCurrent_HuberMueller_Isotope(double E, int iso);

	TString fModelName;
	double fNeutrinoCurrent0;
	double fThermalPower = 16.85; // GWth
	std::vector<double> fFissionFraction;
	std::vector<double> fReleasedEnergy; // MeV
};

#endif

// Reference
// [1] Huber, P. (2011).Determination of antineutrino spectra from nuclear reactors.Physical Review C, 84(2).https://doi.org/10.1103/physrevc.84.024617
// [2] Mueller, T.A., et al. (2011).Improved predictions of reactor antineutrino spectra.Physical Review C, 83(5).https ://doi.org/10.1103/physrevc.83.054615

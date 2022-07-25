#pragma once

#ifndef VREACTORFLUX_HH
#define VREACTORFLUX_HH

#include "vConstant.hh"
#include "TString.h"

class vReactorFlux
{
public:
	vReactorFlux(TString modelName);
	~vReactorFlux();
	void Initialization();
	double GetReactorNeutrinoFlux(double E, int iso=0);
	TF1* GetReactorNeutrinoFlux_TF(int iso = 0, double startE = 1.5, double endE = 9);

	//Setter and Getter
	void SetDistance(double distance);
	void SetThermalPower(double thermalPower);
	void SetFissionFraction(std::vector<double> ff);
	void SetReleasedEnergy(std::vector<double> re);
	double GetDistance() { return mDistance; }
	double GetThermalPower() { return mThermalPower; }
	std::vector<double> GetFissionFraction() { return mFissionFraction; }
	std::vector<double> GetReleasedEnergy() { return mReleasedEnergy; }
	double GetNeutrinoFlux0() { return mNeutrinoFlux0; }

private:
	double GetReactvFlux_Gutlein(double E, int iso); // 1 : U-235, 2 : U-238, 3 : Pu-239, 4 : Pu-241
	double GetReactvFlux_HuberMueller(double E, int iso);
	double GetReactvFlux_Gutlein_Total(double E);
	double GetReactvFlux_Gutlein_Isotope(double E, int iso);
	double GetReactvFlux_HuberMueller_Total(double E);
	double GetReactvFlux_HuberMueller_Isotope(double E, int iso);

	TString mModelName;
	double mDistance = 60000; // m
	double mNeutrinoFlux0;
	double mThermalPower = 16.85; // GWth
	std::vector<double> mFissionFraction;
	std::vector<double> mReleasedEnergy; // MeV

	vConstant* mvConstant;
};


class vRF_TF
{
public:
	vRF_TF(vReactorFlux* vrf) { mvrf = vrf; }
	double operator()(double* x, double* p)
	{
		return mvrf->GetReactorNeutrinoFlux(x[0], p[0]);
	}

private:
	vReactorFlux* mvrf;
};
#endif
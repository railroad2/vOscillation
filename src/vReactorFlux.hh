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
	void SetDistance(double distance);
	void SetFissionFraction(std::vector<double> ff);
	void SetReleasedEnergy(std::vector<double> re);

private:
	double GetReactvFlux_Gutlein(double E, int iso);
	double GetReactvFlux_HuberMuller(double E, int iso);
	double GetReactvFlux_Gutlein_Total(double E);
	double GetReactvFlux_Gutlein_Isotope(double E, int iso);
	double GetReactvFlux_HuberMuller_Total(double E);
	double GetReactvFlux_HuberMuller_Isotope(double E, int iso);

	TString mModelName;
	double mDistance = 60000; // m
	double mNeutrinoFlux0;
	double mThermalPower = 16.85; // GWth
	std::vector<double> mFissionFraction;
	std::vector<double> mReleasedEnergy; // MeV

	vConstant* mvConstant;
};
#endif
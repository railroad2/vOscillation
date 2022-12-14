#ifndef VENERGYSPECTRUM_HH
#define VENERGYSPECTRUM_HH


#include "vNeutrinoSpectrum.hh"
#include "vIBD.hh"


class vEnergySpectrum
{
public:
	vEnergySpectrum(vNeutrinoSpectrum* vns, double emin, double emax)
	{
		SetNeutrinoSpectrum(vns);
		fvibd = new vIBD();
		fEmin = emin;
		fEmax = emax;
	}
	double operator()(double* x, double* p)
	{
		double E = x[0];
		return fvns->GetCurrent(E) * fvibd->GetCrossSection(E);
	}

	void PrintInfo() { fvns->PrintInfo(); }

	vNeutrinoSpectrum* GetNeutrinoSpectrum() { return fvns; }
	void SetNeutrinoSpectrum(vNeutrinoSpectrum* vns) { fvns = vns; }

	double GetEmin() { return fEmin; }
	double GetEmax() { return fEmax; }
	void   SetEmin(double emin) { fEmin = emin; }
	void   SetEmax(double emax) { fEmax = emax; }

private:
	vNeutrinoSpectrum* fvns;
	vIBD* fvibd;

	double fEmin;
	double fEmax;
};

#endif
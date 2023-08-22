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
		fEmin = emin;
		fEmax = emax;
	}
	virtual ~vEnergySpectrum() {}

	double operator()(double* x, double* p) 
	{
		double E = x[0];
        return GetEnergySpectrum(E);
	}

	void PrintInfo() const { fvns->PrintInfo(); }

	vNeutrinoSpectrum* GetNeutrinoSpectrum() const { return fvns; }
	void SetNeutrinoSpectrum(vNeutrinoSpectrum* vns) { fvns = vns; }

	double GetEmin() const { return fEmin; }
	double GetEmax() const { return fEmax; }
	void   SetEmin(double emin) { fEmin = emin; }
	void   SetEmax(double emax) { fEmax = emax; }

    double GetEnergySpectrum(double E)
    {
        return fvns->GetCurrent(E) * fvibd.GetCrossSection_integral(E); // cm^2/day/proton
    }
private:
	vNeutrinoSpectrum* fvns;
	vIBD fvibd;

	double fEmin;
	double fEmax;
};

#endif

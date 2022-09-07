#pragma once

#ifndef VSOLARFLUX_HH
#define VSOLARFLUX_HH

#include "vConstant.hh"


class vSolarFlux
{
	public:
		double GetSolarNeutrinoFlux_NoPeak(double E);
		double GetSolarNeutrinoFlux_NoPeak(double E, TString src);
		double GetSolarNeutrinoFlux_NoPeak(double E, int src);
		double GetSolarNeutrinoFlux_PeakEnergy(TString src);
		double GetSolarNeutrinoFlux_PeakEnergy(int src = 0);
		double GetSolarNeutrinoFlux_PeakFlux(TString src);
		double GetSolarNeutrinoFlux_PeakFlux(int src = 0);
		TF1*   GetTF_SolarNeutrinoFlux_NoPeak(TString src, double startE = 1.5, double endE = 9);
		TF1*   GetTF_SolarNeutrinoFlux_NoPeak(int src = 0, double startE = 1.5, double endE = 9);
	
	private:
		double CalSolNuFlux_Priv_NoPeak(double E);
		double CalSolNuFlux_Priv_NoPeak(double E, int src);

		vConstant* mvConstant;
		const int mNumSrc = 8;
		const int mNumSrcNoPeak = 6;
		double mE_PEP = 1.442; // MeV
		double mE_Be7_1 = 0.385; // MeV
		double mE_Be7_2 = 0.862; // MeV
};


class vSL_TF
{
	public:
		vSL_TF(vSolarFlux* vsl) { mvsl = vsl; }
		double operator()(double* x, double* p)
		{
			return mvsl->GetSolarNeutrinoFlux_NoPeak(x[0], (int)p[0]);
		}
	
	private:
		vSolarFlux* mvsl;
};
#endif

// Reference
// [1] A. Gutlein, Feasibility Study for a First Observation of CEvNS Using Low-Temperature Detectors
// [2] J.N.Bahcall, et al., New Solar Opacities, Abundances, Helioseismology, and Neutrino Fluxes, ApJ 621, L85(2005)
// [3] J.N.Bahcall, http://www.sns.ias.edu/~jnb/
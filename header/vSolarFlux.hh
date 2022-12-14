#ifndef VSOLARFLUX_HH
#define VSOLARFLUX_HH


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

private:
	double CalSolNuFlux_Priv_NoPeak(double E);
	double CalSolNuFlux_Priv_NoPeak(double E, int src);

	const int mNumSrc = 8;
	const int mNumSrcNoPeak = 6;
	double mE_PEP = 1.442; // MeV
	double mE_Be7_1 = 0.385; // MeV
	double mE_Be7_2 = 0.862; // MeV
};

#endif
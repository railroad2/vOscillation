#ifndef VSOLARFLUX_HH
#define VSOLARFLUX_HH


class vSolarFlux
{
public:
	double GetSolarNeutrinoFlux_NoPeak(double E) const;
	double GetSolarNeutrinoFlux_NoPeak(double E, TString src) const;
	double GetSolarNeutrinoFlux_NoPeak(double E, int src) const;
	double GetSolarNeutrinoFlux_PeakEnergy(TString src) const;
	double GetSolarNeutrinoFlux_PeakEnergy(int src = 0) const;
	double GetSolarNeutrinoFlux_PeakFlux(TString src) const;
	double GetSolarNeutrinoFlux_PeakFlux(int src = 0) const;

private:
	double CalSolNuFlux_Priv_NoPeak(double E) const;
	double CalSolNuFlux_Priv_NoPeak(double E, int src) const;

	constexpr static int fNumSrc = 8;
	constexpr static const int fNumSrcNoPeak = 6;
	constexpr static double fE_PEP = 1.442; // MeV
	constexpr static double fE_Be7_1 = 0.385; // MeV
	constexpr static double fE_Be7_2 = 0.862; // MeV
};

#endif
#ifndef VCE144SPECTRUM_HH
#define VCE144SPECTRUM_HH


#include "vBetaSpectrum.hh"


class vCe144Spectrum : public vBetaSpectrum
{
public:
	vCe144Spectrum()
	{
		SetVectorSize(2);
		SetQValues({ 2.9975 , 2.30099 });
		// 2997.5 keV, m_Pr144 - m_Nd144 (ground state) (only nuclear mass)
		// 2300.99 keV, m_Pr144 - m_Nd144 (first excited state) (only nuclear mass)
		SetZdaughter({ 60., 60. });
		SetContribution({ 0.979 / 2., 0.0104 / 2. });
		// Why devided by 2? : only half of the activity is the Pr144's one.
		// Ce144 -(285 days)-> Pr144 -(17 min)-> Nd144
		SetNormalization({ 50.17699342431172 , 16.17204881872361 });
	}
};

#endif
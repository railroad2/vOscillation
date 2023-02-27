#ifndef	VNEUTRINOSPECTRUM_HH
#define VNEUTRINOSPECTRUM_HH


class vNeutrinoSpectrum
{
public:
	virtual double GetCurrent(double E) const = 0; // /day, emitted neutrino number per day
	virtual void PrintInfo() const {}
};


#endif
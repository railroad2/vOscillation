#ifndef VMODELGENERATOR_HH
#define VMODELGENERATOR_HH


#include "vDetector.hh"
#include "vSource.hh"
#include "vEnergySpectrum.hh"


class vModelGenerator
{
public:
	vModelGenerator(vDetector* detector, vSource* source, vEnergySpectrum spectrum) 
		: fSpectrum(spectrum)
	{
		fDetector = detector;
		fSource = source;
	}
	virtual ~vModelGenerator() {}

	virtual void Initialization() {}

	virtual void FillHistogram(TH1D* oHistL, TH1D* oHistE, TH1D* oHistLoE, TH2D* oHistLE, int64_t& oIterNum, int64_t genNum) const = 0;

	virtual void PrintInfo() const;

	vDetector*			GetDetector() const { return fDetector; }
	vSource*			GetSource() const { return fSource; }
	double				GetDeltaX() const { return fDeltaX; }
	double				GetDeltaZ() const { return fDeltaZ; }
	vEnergySpectrum		GetSpectrum() const { return fSpectrum; }

	void				SetDetector(vDetector* detector) { fDetector = detector; }
	void				SetSource(vSource* source) { fSource = source; }
	void				SetDeltaX(double deltaX) { fDeltaX = deltaX; }
	void				SetDeltaZ(double deltaZ) { fDeltaZ = deltaZ; }
	void				SetSpectrum(vEnergySpectrum spectrum) { fSpectrum = spectrum; }

protected:
	double				CalculateL(double x, double y, double z) const;

	vDetector*			fDetector;
	vSource*			fSource;
	vEnergySpectrum		fSpectrum;
	double				fDeltaX;
	double				fDeltaZ;
};


#endif
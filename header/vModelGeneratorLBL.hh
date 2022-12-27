#ifndef VMODELGENERATORLBL_HH
#define VMODELGENERATORLBL_HH


#include "vModelGenerator.hh"
#include "vOscillating.hh"


class vModelGeneratorLBL : public vModelGenerator
{
public:
	vModelGeneratorLBL(vDetector* detector, vSource* source, vEnergySpectrum spectrum) : vModelGenerator(detector, source, spectrum) {}
	~vModelGeneratorLBL() {}

	void Initialization()
	{
		CalDistance();
	}

	void PrintInfo();

	void FillHistogram(TH1D* oHistL, TH1D* oHistE, TH1D* oHistLoE, TH2D* oHistLE, int64_t& oIterNum, int64_t genNum);
	
	void SetvOscillating(vOscillating* vosc) { fvosc = vosc; }
	vOscillating* GetvOscillating() { return fvosc; }
	double GetDistance() { return fDistance; }

private:
	void CalDistance();

	double fDistance;
	vOscillating* fvosc;
};

#endif
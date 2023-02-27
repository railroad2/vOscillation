#ifndef VMODELGENERATORLBL_HH
#define VMODELGENERATORLBL_HH


#include "vModelGenerator.hh"
#include "vOscillation.hh"


class vModelGeneratorLBL : public vModelGenerator
{
public:
	vModelGeneratorLBL(vDetector* detector, vSource* source, vEnergySpectrum spectrum) : vModelGenerator(detector, source, spectrum) {}
	~vModelGeneratorLBL() override {}

	void Initialization() override
	{
		CalDistance();
	}

	void FillHistogram(TH1D* oHistL, TH1D* oHistE, TH1D* oHistLoE, TH2D* oHistLE, int64_t& oIterNum, int64_t genNum) const override;
	
	void PrintInfo() const override;

	void SetvOscillation(vOscillation* vosc) { fvosc = vosc; }
	vOscillation* GetvOscillation() const { return fvosc; }
	double GetDistance() const { return fDistance; }

private:
	void CalDistance();

	double fDistance;
	vOscillation* fvosc;
};

#endif
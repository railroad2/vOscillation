#ifndef VMODELGENERATORSTERILEEE_HH
#define VMODELGENERATORSTERILEEE_HH


#include "vModelGenerator.hh"
#include "vSterileEE.hh"


class vModelGeneratorSterileEE : public vModelGenerator
{
public:
	vModelGeneratorSterileEE(vDetector* detector, vSource* source, vEnergySpectrum spectrum) : vModelGenerator(detector, source, spectrum) {}
	~vModelGeneratorSterileEE() {}

	void Initialization()
	{
		frmin = CalMinDistance();
	}

	void FillHistogram(TH1D* oHistL, TH1D* oHistE, TH1D* oHistLoE, TH2D* oHistLE, int64_t& oIterNum, int64_t genNum);
	void FillHistogramFast(TH1D** oHistLList, TH1D** oHistEList, TH1D** oHistLoEList, TH2D** oHistLEList,
		int listSize, std::vector<double> Dm2_List, int64_t genNum);

	void PrintInfo();

	void SetSterileEE(vSterileEE* vst) { fvst = vst; }
	vSterileEE* GetSterileEE() { return fvst; }
	double GetRmin() { return frmin; }

protected:
	

private:
	double CalMinDistance();
	double frmin;
	vSterileEE* fvst;
};


#endif
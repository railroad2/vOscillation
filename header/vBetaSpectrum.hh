#ifndef VBETASPECTRUM_HH
#define VBETASPECTRUM_HH


#include "vNeutrinoSpectrum.hh"
#include <vector>


class vBetaSpectrum : public vNeutrinoSpectrum
{
public:
	void PrintInfo();
	
	double GetCurrent(double E);
	
	void SetActivity(double activity) { fActivity = activity; } // The unit of Activity should be /day
	double GetActivity() { return fActivity; }

protected:
	double GetBetaSpectrum(double T, double Q, double Z_f, double normalization);
	
	void SetVectorSize(int size) { fVectorSize = size; }
	void SetQValues(std::vector<double> qValue) { fQValue = qValue; }
	void SetZdaughter(std::vector<double> Z_f) { fZdaughter = Z_f; }
	void SetContribution(std::vector<double> cont) { fContribution = cont; }
	void SetNormalization(std::vector<double> norm) { fNormalization = norm; }

private:
	double fActivity;
	
	int fVectorSize;
	std::vector<double> fQValue;
	std::vector<double> fZdaughter;
	std::vector<double> fContribution;
	std::vector<double> fNormalization;
};

#endif
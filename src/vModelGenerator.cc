#include "TMath.h"
#include "../header/vModelGenerator.hh"


void vModelGenerator::PrintInfo() const
{
	std::cout << "<vModelGenerator>" << std::endl;
	std::cout << "    Delta X          : " << fDeltaX << std::endl;
	std::cout << "    Delta Z          : " << fDeltaZ << std::endl;
	fDetector->PrintInfo();
	fSource->PrintInfo();
	fSpectrum.PrintInfo();
}


double vModelGenerator::CalculateL(double x, double y, double z) const
{
	return TMath::Sqrt(x * x + y * y + z * z);
}

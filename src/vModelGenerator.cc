#include "../header/vModelGenerator.hh"


void vModelGenerator::PrintInfo() const
{
	cout << "<vModelGenerator>" << endl;
	cout << "    Delta X          : " << fDeltaX << endl;
	cout << "    Delta Z          : " << fDeltaZ << endl;
	fDetector->PrintInfo();
	fSource->PrintInfo();
	fSpectrum.PrintInfo();
}


double vModelGenerator::CalculateL(double x, double y, double z) const
{
	return TMath::Sqrt(x * x + y * y + z * z);
}
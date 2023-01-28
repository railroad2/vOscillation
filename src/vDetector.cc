#include "../header/vDetector.hh"


void vDetector::Initialization()
{
	CalVolume();
	CalProtonNumber();
}


void vDetector::PrintInfo() const
{
	cout << "<vDetector>" << endl;
	cout << "    ShapeType                        : " << fShapeType << endl;
	cout << "    Volume                           : " << fVolume << endl;
	cout << "    Energy resolution @ 1 MeV (%)    : " << fResolutionE * 100 << endl;
	cout << "    Position resolution @ 1 MeV (cm) : " << fResolutionL * 100 << endl;
}


void vDetector::GetRandomResolutionPosition(double& oX, double& oY, double& oZ, double Enu) const
{
	oX = gRandom->Gaus(0, fResolutionL / TMath::Sqrt(Enu));
	oY = gRandom->Gaus(0, fResolutionL / TMath::Sqrt(Enu));
	oZ = gRandom->Gaus(0, fResolutionL / TMath::Sqrt(Enu));
}


void vDetector::GetRandomResolutionEnergy(double& oE, double Enu) const
{
	oE = gRandom->Gaus(0, fResolutionE * TMath::Sqrt(Enu));
}


void vDetector::CalProtonNumber()
{
	vector<double> Ratio = { 0.0047, 0.097, 0.3385, 0.3472, 0.2083, 0.0043 };
	vector<double> Cnum = { 15, 16, 17, 18, 19, 20 };
	vector<double> Hnum = { 24, 26, 28, 30, 32, 34 };

	double Cgram = 12.011;
	double Hgram = 1.008;

	double gramPerMol = 0;
	double HPerMol = 0;
	for (int i = 0; i <= 5; i++)
	{
		gramPerMol += Ratio[i] * (Cnum[i] * Cgram + Hnum[i] * Hgram);
		HPerMol += Ratio[i] * Hnum[i]; // #/mol
	}

	double LSdensity = 0.860; // g/ml
	double LSgram = fVolume * 1.e6 * LSdensity; // g
	double Abogadro = 6.02214076e23;

	fProtonNumber = LSgram / gramPerMol * HPerMol * Abogadro;
}
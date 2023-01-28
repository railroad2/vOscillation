#include "../header/vDetectorCylinder.hh"


void vDetectorCylinder::PrintInfo() const
{
	vDetector::PrintInfo();
	cout << "    fRadius (m)                      : " << fRadius << endl;
	cout << "    fHeight (m)                      : " << fHeight << endl;
}


void vDetectorCylinder::GetRandomPosition(double& oX, double& oY, double& oZ) const
{
	double theta = gRandom->Uniform(0, 2 * TMath::Pi());
	double r = fRadius * TMath::Sqrt(gRandom->Uniform());
	oX = r * TMath::Cos(theta);
	oY = r * TMath::Sin(theta);
	oZ = gRandom->Uniform(-fHeight / 2., fHeight / 2.);
}


void vDetectorCylinder::CalVolume()
{
	fVolume = TMath::Pi() * fRadius * fRadius * fHeight;
}
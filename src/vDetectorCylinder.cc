#include "../header/vDetectorCylinder.hh"


void vDetectorCylinder::PrintInfo() const
{
	vDetector::PrintInfo();
	std::cout << "    fRadius (m)                      : " << fRadius << std::endl;
	std::cout << "    fHeight (m)                      : " << fHeight << std::endl;
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
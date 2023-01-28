#include "../header/vSourceCylinder.hh"


void vSourceCylinder::PrintInfo() const
{
	vSource::PrintInfo();
	cout << "    fRadius   : " << fRadius << endl;
	cout << "    fHeight   : " << fHeight << endl;
}


void vSourceCylinder::GetRandomPosition(double& oX, double& oY, double& oZ) const
{
	double theta = gRandom->Uniform(0, 2 * TMath::Pi());
	double r = fRadius * TMath::Sqrt(gRandom->Uniform());
	oX = r * TMath::Cos(theta);
	oY = r * TMath::Sin(theta);
	oZ = gRandom->Uniform(-fHeight / 2., fHeight / 2.);
}
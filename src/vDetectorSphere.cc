#include "../header/vDetectorSphere.hh"


void vDetectorSphere::PrintInfo()
{
	vDetector::PrintInfo();
	cout << "    fRadius                          : " << fRadius << endl;
}


void vDetectorSphere::GetRandomPosition(double& oX, double& oY, double& oZ)
{
	double r = fRadius * TMath::Power(gRandom->Uniform(0., 1.), 1. / 3.);
	double phi = gRandom->Uniform(0., 2. * TMath::Pi());
	double theta = TMath::ACos(gRandom->Uniform(-1., 1.));
	oX = r * TMath::Sin(theta) * TMath::Cos(phi);
	oY = r * TMath::Sin(theta) * TMath::Sin(phi);
	oZ = r * TMath::Cos(theta);
}


void vDetectorSphere::CalVolume()
{
	fVolume = 4. / 3. * TMath::Pi() * fRadius * fRadius * fRadius;
}
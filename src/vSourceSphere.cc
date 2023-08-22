#include <iostream>
#include "TMath.h"
#include "TRandom.h"
#include "../header/vSourceSphere.hh"


void vSourceSphere::PrintInfo() const
{
	vSource::PrintInfo();
	std::cout << "    fRadius   : " << fRadius << std::endl;
}


void vSourceSphere::GetRandomPosition(double& oX, double& oY, double& oZ) const
{
	double r = fRadius * TMath::Power(gRandom->Uniform(0., 1.), 1. / 3.);
	double phi = gRandom->Uniform(0., 2. * TMath::Pi());
	double theta = TMath::ACos(gRandom->Uniform(-1., 1.));
	oX = r * TMath::Sin(theta) * TMath::Cos(phi);
	oY = r * TMath::Sin(theta) * TMath::Sin(phi);
	oZ = r * TMath::Cos(theta);
}

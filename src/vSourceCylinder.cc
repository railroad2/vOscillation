#include <iostream>
#include "TMath.h"
#include "TRandom.h"
#include "../header/vSourceCylinder.hh"


void vSourceCylinder::PrintInfo() const
{
	vSource::PrintInfo();
	std::cout << "    fRadius   : " << fRadius << std::endl;
	std::cout << "    fHeight   : " << fHeight << std::endl;
}


void vSourceCylinder::GetRandomPosition(double& oX, double& oY, double& oZ) const
{
	double theta = gRandom->Uniform(0, 2 * TMath::Pi());
	double r = fRadius * TMath::Sqrt(gRandom->Uniform());
	oX = r * TMath::Cos(theta);
	oY = r * TMath::Sin(theta);
	oZ = gRandom->Uniform(-fHeight / 2., fHeight / 2.);
}

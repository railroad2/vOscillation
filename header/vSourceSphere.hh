#ifndef VSOURCESPHERE_HH
#define VSOURCESPHERE_HH


#include "vSource.hh"


/**
 * This class is for the vModelGenerator which needs the spatial information of the neutrino source to work.
 *
 * This class only has the spatial information of the neutrino source.
 * If you want to know about the energy and flux information of the source, then check "vNeutrinoSpectrum.hh"
 *
 * This class has inheritance about "vSource". See also "vSource.hh"
 */
class vSourceSphere : public vSource
{
public:
	vSourceSphere() { SetShapeType("Sphere"); }

	void PrintInfo() const override;
	
	double GetRadius() const { return fRadius; }
	void GetRandomPosition(double& oX, double& oY, double& oZ) const override;
	void SetRadius(double radius) { fRadius = radius; }

private:
	double fRadius;
};

#endif
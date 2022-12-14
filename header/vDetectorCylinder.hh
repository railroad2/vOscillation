#ifndef VDETECTORCYLINDER_HH
#define VDETECTORCYLINDER_HH


#include "vDetector.hh"


class vDetectorCylinder : public vDetector
{
public:

	void PrintInfo();

	vDetectorCylinder() { SetShapeType("Cylinder"); }
	double GetRadius() { return fRadius; }
	double GetHeight() { return fHeight; }
	void GetRandomPosition(double& oX, double& oY, double& oZ);
	void SetRadius(double radius) { fRadius = radius; }
	void SetHeight(double height) { fHeight = height; }

protected:
	void CalVolume();

private:
	double fRadius;
	double fHeight;
};

#endif
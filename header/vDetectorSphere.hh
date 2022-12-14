#ifndef VDETECTORSPHERE_HH
#define VDETECTORSPHERE_HH


#include "vDetector.hh"


class vDetectorSphere : public vDetector
{
public:
	
	void PrintInfo();
	
	vDetectorSphere() { SetShapeType("Sphere"); }
	double GetRadius() { return fRadius; }
	void GetRandomPosition(double& oX, double& oY, double& oZ);
	void SetRadius(double radius) { fRadius = radius; }

protected:
	void CalVolume();

private:
	double fRadius;
};

#endif
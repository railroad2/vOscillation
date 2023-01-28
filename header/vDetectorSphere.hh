#ifndef VDETECTORSPHERE_HH
#define VDETECTORSPHERE_HH


#include "vDetector.hh"


class vDetectorSphere : public vDetector
{
public:
	vDetectorSphere() { SetShapeType("Sphere"); }

	void PrintInfo() const override;
	
	double GetRadius() const { return fRadius; }
	void GetRandomPosition(double& oX, double& oY, double& oZ) const override;
	void SetRadius(double radius) { fRadius = radius; }

protected:
	void CalVolume() override;

private:
	double fRadius;
};

#endif
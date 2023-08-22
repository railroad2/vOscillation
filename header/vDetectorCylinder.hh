#ifndef VDETECTORCYLINDER_HH
#define VDETECTORCYLINDER_HH


#include "vDetector.hh"


class vDetectorCylinder : public vDetector
{
public:
	vDetectorCylinder() { SetShapeType("Cylinder"); }

	void PrintInfo() const override;

	double GetRadius() const { return fRadius; }
	double GetHeight() const { return fHeight; }
	void GetRandomPosition(double& oX, double& oY, double& oZ) const override;
	void SetRadius(double radius) { fRadius = radius; }
	void SetHeight(double height) { fHeight = height; }
    double GetLDistribution(double L, double Xs, double Zs, int ndiv=1000, bool solid_angle=false);
    double GetArc(double L, double theta, double Xs, double Zs);

protected:
	void CalVolume() override;

private:
	double fRadius;
	double fHeight;
};

#endif

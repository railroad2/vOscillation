#ifndef VDETECTOR_HH
#define VDETECTOR_HH

#include "TString.h"

/**
 * This class is for the vModelGenerator which needs the spatial information of the detector to work.
 *
 * This class has the following information:
 *	1. Spatial information of the detector.
 *	2. Resolution information of the detector.
 *		2-1. Energy resolution: It is assumed that the energy resolution is proportional to Sqrt(energy). See also "fResolutionE" in this class.
 *		2-2. Position resolution: It is assumed that the position resolution is proportional to 1/Sqrt(energy). See also "fResolutionL" in this class.
 *	3. Proton Number of the detector.
 *		vModelGenerator class is a calculation tool for the neutrino detection experiment which uses Inverse Beta Decay to detect anti-electron neutrino.
 *		The number of the event of Inverse Beta Decay is proportional to the free proton number in the detector.
 *		In this class, it is assumed that the Liquid Scintillator in the detector is LABs(Linear Alkylbenzenes). See also "CalProtonNumber()" in this class.
 *
 * This class has the role of the interface of vDetectorCylinder, vDetectorSphere, etc.
 */
class vDetector
{
public:
	vDetector() { SetShapeType("Point"); };

	void Initialization();

	virtual void PrintInfo() const;

	/**
	 * Generate a random position vector (oX, oY, oZ) uniformly in the detector.
	 *
	 * In this class(vDetector), this method is not defined.
	 * If you want to make another class you made inherit this class, then you should override this function with new spatial parameters (radius, height, etc.).
	 */
	virtual void GetRandomPosition(double& oX, double& oY, double& oZ) const {}
	void GetRandomResolutionPosition(double& oX, double& oY, double& oZ, double Enu) const;
	void GetRandomResolutionEnergy(double& oE, double Enu) const;

	double GetResolutionE() const { return fResolutionE; }
	double GetResolutionL() const { return fResolutionL; }
	double GetVolume() const { return fVolume; } // m^3
	double GetProtonNumber() const { return fProtonNumber; }
	TString GetShapeType() const { return fShapeType; }

	void SetResolutionE(double resolution) { fResolutionE = resolution; } // @ 1 MeV, ex) 5% -> resolution = 0.05
	void SetResolutionL(double resolution) { fResolutionL = resolution; } // @ 1 MeV, ex) 12cm -> resolution = 0.12

protected:
	void SetShapeType(TString shapeType) { fShapeType = shapeType; }

	virtual void CalVolume() { fVolume = 0; }
	double fVolume;

private:
	void CalProtonNumber();

	double fResolutionE;
	double fResolutionL;
	double fProtonNumber;
	TString fShapeType;
};

#endif

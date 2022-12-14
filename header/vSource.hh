#ifndef VSOURCE_HH
#define VSOURCE_HH


/**
 * This class is for the vModelGenerator which needs the spatial information of the neutrino source to work.
 *
 * This class only has the spatial information of the neutrino source.
 * If you want to know about the energy and flux information of the source, then check "vNeutrinoSpectrum.hh"
 *
 * This class has the role of the interface of vSourceCylinder, vSourceSphere, etc., but you can use this class as the "point source".
 */
class vSource
{
public:
	vSource() { SetShapeType("Point"); }

	virtual void PrintInfo()
	{
		cout << "<vSource>" << endl;
		cout << "    ShapeType : " << fShapeType << endl;
	}

	/**
	 * Generate a random position vector (oX, oY, oZ) uniformly in the source.
	 *
	 * In this class(vSource), since there is no volume, the position is just to be a Zero Vector.
	 * If you want to make another class you made inherit this class, then you should override this function with new spatial parameters (radius, height, etc.).
	 */
	virtual void GetRandomPosition(double& oX, double& oY, double& oZ)
	{
		oX = 0; oY = 0; oZ = 0;
	}
	TString GetShapeType() { return fShapeType; }

protected:
	void SetShapeType(TString shapeType) { fShapeType = shapeType; }

private:
	/**
	 * String variable that means "which shape the source has"
	 *
	 * This variable is set by "SetShapeType", and this should be called at the constructor.
	 * In this class, fShapeType = "Point".
	 */
	TString fShapeType;
};

#endif
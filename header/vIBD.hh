#ifndef VIBD_HH
#define VIBD_HH


class vIBD
{
public:
	double GetCrossSection(double E) const;
	double GetDifCrossSection(double E, double theta) const;

private:
	double GetMomentum_Positron(double E) const;
};

#endif 


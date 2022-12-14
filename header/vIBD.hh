#ifndef VIBD_HH
#define VIBD_HH


class vIBD
{
public:
	double GetCrossSection(double E);
	double GetDifCrossSection(double E, double theta);

private:
	double GetMomentum_Positron(double E);
};

#endif 


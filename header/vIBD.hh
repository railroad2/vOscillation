#ifndef VIBD_HH
#define VIBD_HH


class vIBD
{
public:
	double GetCrossSection(double E) const;
	double GetCrossSection_0th(double E) const;
	double GetCrossSection_integral(double E, int npts=1001) const;

	double GetDifCrossSection(double E, double theta) const;
	double GetDifCrossSection_1st(double E, double theta) const;

private:
	double GetMomentum_Positron(double E) const;
};

#endif 


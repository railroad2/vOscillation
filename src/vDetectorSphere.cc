#include "../header/vDetectorSphere.hh"


void vDetectorSphere::PrintInfo() const
{
	vDetector::PrintInfo();
	std::cout << "    fRadius                          : " << fRadius << std::endl;
}


void vDetectorSphere::GetRandomPosition(double& oX, double& oY, double& oZ) const
{
	double r = fRadius * TMath::Power(gRandom->Uniform(0., 1.), 1. / 3.);
	double phi = gRandom->Uniform(0., 2. * TMath::Pi());
	double theta = TMath::ACos(gRandom->Uniform(-1., 1.));
	oX = r * TMath::Sin(theta) * TMath::Cos(phi);
	oY = r * TMath::Sin(theta) * TMath::Sin(phi);
	oZ = r * TMath::Cos(theta);
}


void vDetectorSphere::CalVolume()
{
	fVolume = 4. / 3. * TMath::Pi() * fRadius * fRadius * fRadius;
}

double vDetectorSphere::GetLDistribution(double L, double Xs, double Zs, int ndiv=1000, bool solid_angle=false)
{
    double theta = -TMath::Pi();
    double dtheta = TMath::Pi()/(ndiv - 1);
    double larc;
    double area;
    double sf = (solid_angle && L>0) ? 1./L/L : 1;

    for (int i=0; i<ndiv; i++) {
        larc = GetArc(L, theta, Xs, Zs);
        area += larc * L * dtheta * sf;
        theta = theta + dtheta;
    }

    return area;

}

double vDetectorSphere::GetArc(double L, double theta, double Xs, double Zs)
{
    double rho = L * TMath::Cos(theta);
    double z = L * TMath::Sin(theta);
    double Rd = fRadius;
    double Hd = fRadius;

    if (rho == 0) return 0;
    if (z + Zs < -Hd/2 || z + Zs > Hd/2) return 0;

    double Xs1 = Xs == 0 ? 1e-10 : Xs;
    double cosphi = (rho*rho + Xs*Xs - Rd*Rd) / 2 / rho / Xs1;

    if (cosphi >  1) cosphi =  1;
    if (cosphi < -1) cosphi = -1;

    double phi = TMath::ACos(cosphi);
    double arc = 2 * rho * phi;

    return arc;
}

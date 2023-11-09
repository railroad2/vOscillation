#include "../header/vDetectorCylinder.hh"


void vDetectorCylinder::PrintInfo() const
{
	vDetector::PrintInfo();
	std::cout << "    fRadius (m)                      : " << fRadius << std::endl;
	std::cout << "    fHeight (m)                      : " << fHeight << std::endl;
}


void vDetectorCylinder::GetRandomPosition(double& oX, double& oY, double& oZ) const
{
	double theta = gRandom->Uniform(0, 2 * TMath::Pi());
	double r = fRadius * TMath::Sqrt(gRandom->Uniform());
	oX = r * TMath::Cos(theta);
	oY = r * TMath::Sin(theta);
	oZ = gRandom->Uniform(-fHeight / 2., fHeight / 2.);
}


void vDetectorCylinder::CalVolume()
{
	fVolume = TMath::Pi() * fRadius * fRadius * fHeight;
}

double vDetectorCylinder::GetLDistribution(double L, double Xs, double Zs, int ndiv=1000, bool solid_angle=false) 
{
    double theta = -TMath::Pi()/2;
    double dtheta = TMath::Pi()/(ndiv - 1);
    double larc = 0;
    double area = 0;
    double sf = (solid_angle && L>0.) ? 1./L/L : 1;

    for (int i=0; i<ndiv; i++) {
        larc = GetArc(L, theta, Xs, Zs);
        area += larc * L * dtheta * sf;
        theta = theta + dtheta;
    }

    return area;
}

double vDetectorCylinder::GetArc(double L, double theta, double Xs, double Zs)
{
    double rho = L * TMath::Cos(theta);
    double z = L * TMath::Sin(theta);
    double Rd = fRadius;
    double Hd = fHeight;

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


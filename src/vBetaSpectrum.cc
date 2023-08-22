#include "../header/vBetaSpectrum.hh"
#include "../header/vConstant.hh"


void vBetaSpectrum::PrintInfo() const
{
	std::cout << "<vEnergySpectrum->vNeutrinoSpectrum->vBetaSpectrum>" << std::endl;
	std::cout << "    Activity (unit : user defined) : " << fActivity << std::endl;
}


TComplex vBetaSpectrum::gamma_complex(double zreal, double zimag) const
{

    static const int g = 7;
    static const int n = 9;
    static const double p[] = {
        0.99999999999980993,
        676.5203681218851,
        -1259.1392167224028,
        771.32342877765313,
        -176.61502916214059,
        12.507343278686905,
        -0.13857109526572012,
        9.9843695780195716e-6,
        1.5056327351493116e-7
    };

    TComplex Pi = TComplex(TMath::Pi());
    TComplex y;
    TComplex z = TComplex(zreal, zimag);

    if (zreal < 0.5) {
        y = Pi / TComplex::Sin(Pi * z) / gamma_complex(1.0-z.Re(), -z.Im());
    }
    else {
        z -= 1;
        TComplex x = TComplex(p[0]);
        int N = sizeof(p) / sizeof(*p);

        for (int i=1; i<n; i++) {
            x += TComplex(p[i]) / (z + TComplex(i));
            TComplex t = z + TComplex(g) + TComplex(0.5);
            y = TComplex::Sqrt(TComplex(2.*Pi)) * TComplex::Power(t, z+0.5) * TComplex::Exp(TComplex(-1)*t) * x;
        }
    }
    return y;
}
    

double vBetaSpectrum::gamma_complex_mag2(double zreal, double zimage) const
{
    TComplex g = gamma_complex(zreal, zimage);
    return g * TComplex::Conjugate(g);
    //return g * TComplex(g.Re(), -g.Im());
}


double vBetaSpectrum::GetFermiFunction(double T, double Z, double A, bool anti) const
{
	double m_e = MASSELECTRON;
	double E_e = (T + m_e);
	double fsc = 7.29735e-3;
	double p = TMath::Sqrt(E_e * E_e - m_e * m_e);
    double S = TMath::Sqrt(1 - TMath::Power(fsc * Z, 2));

	double eta;
	if (anti) eta = -Z * fsc * E_e / p;
	else      eta =  Z * fsc * E_e / p;

    double phi = TMath::ATan2(S, eta);
    double Seta = TMath::Sqrt(S*S + eta*eta);
    double F;

    switch (fFermiApproxMethod)
    {
        case EXACT:
            F = TMath::Power(p/m_e, 2*S-2) * TMath::Exp(TMath::Pi()*eta) * gamma_complex_mag2(S, eta);
            break;
        case HALL:
            F = 2 * TMath::Pi() * TMath::Power(p/m_e, 2*S - 2) * TMath::Power(Seta, S-0.5) \
                   * TMath::Exp(2*eta*phi - 2*S + S/6/Seta);
            break;
        case NONREL:
            F = 2 * TMath::Pi() * eta / (1 - TMath::Exp(-2 * TMath::Pi() * eta));
            break;
    }
   
    const double R0 = 1.2; // femto-meter
    const double hbarc = 197.3269804; // hbar*c in MeV fm
    double rho = R0 * TMath::Power(A, 1./3) * hbarc;
    double pre = 2*(1 + S) / TMath::Gamma(2*S+1) * TMath::Power(2*rho*m_e, 2*S-2);
    
    if (!fFFreduced) F *= pre;

    return F;
}


double vBetaSpectrum::GetCurrent(double E) const
{
	double Spectrum = 0;

	for (int i = 0; i < fVectorSize; i++)
	{
		double qValue = fQValue[i];
		double Z_f = fZdaughter[i];
        double A = fA[i];
		double cont = fContribution[i];
		double norm = fNormalization[i];
		Spectrum += cont * GetBetaSpectrum(qValue - E, qValue, Z_f, norm, A);
	}

	return fActivity * Spectrum;
}


double vBetaSpectrum::GetBetaSpectrum(double T, double Q, double Z_f, double normalization, double A, bool anti) const 
{
	double E_0 = MASSDELTA;
	double m_e = MASSELECTRON;
	double E_e = (T + m_e);
	double fsc = 7.29735e-3;
	double p = TMath::Sqrt(E_e * E_e - m_e * m_e);
	if (Q < T) return 0;
	double S_0 = p * E_e * (Q - T) * (Q - T);

    // Previous implementation 
    // Non-relativistic approximation (or low Z approximation - non official)
    /*
	double eta;
	if (anti) eta = -Z_f * fsc * E_e / p;
	else      eta =  Z_f * fsc * E_e / p;

	double F = 2 * TMath::Pi() * eta / (1 - TMath::Exp(-2 * TMath::Pi() * eta));
    */

    if (A == 0) A = 2*Z_f;
    double F = GetFermiFunction(T, Z_f, A, anti);

	if (p == 0) return 2 * TMath::Pi() * Z_f * fsc * m_e * m_e * Q * Q / normalization;
	if (p < 0) return 0;
	if (F * S_0 > 0) return F * S_0 / normalization;
	else return 0;
}

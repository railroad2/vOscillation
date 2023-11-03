#include "../header/vIBD.hh"
#include "../header/vConstant.hh"


// this use the zeroth order approximation of IBD cross section from Vogel's paper (1999).
double vIBD::GetCrossSection(double E) const
{
    return GetCrossSection_integral(E);
}

double vIBD::GetCrossSection_integral(double E, int npts=1001) const
{
    double costheta;
    double dcostheta = 2./(npts-1);
    double sig = 0;
    for (int i=0; i<npts; i++) {
        costheta = -1 + i*dcostheta;
        sig += GetDifCrossSection_costheta(E, costheta) * dcostheta;
    }

    return sig;
}

double vIBD::GetCrossSection_0th(double E) const
{
    double Delta = MASSDELTA;
    double E_e = E - MASSDELTA;
    double sigma_0 = 0.0952 * 1e-42; // cm^2 / MeV^2
    double M_e = MASSELECTRON;
    if (E_e < M_e) return 0;
    double P_e = TMath::Sqrt(E_e*E_e - M_e*M_e);

    double sigma_tot = sigma_0 * E_e * P_e;
    return sigma_tot;
}


/* 
 * this use the first order approximation of IBD cross section from Vogel's paper (1999)
 * with an assumption of E_nu > 5 MeV.
double vIBD::GetCrossSection(double E) const
{
    static double f = 1;
    static double g = 1.26;
    double f_sq = f * f;
    double g_sq = g * g;
    static double f2 = 3.706;

    double Delta = MASSDELTA;
    double E_e = E - MASSDELTA;
    double sigma_0 = 0.0952 / (f_sq + 3 * g_sq) * 1e-42; // cm^2 / MeV^2
    double M_e = MASSELECTRON;
    double M = MASSPROTON;

    if (E_e < M_e) return 0;
    else
    {
        double alpha = f_sq + 3 * g_sq;
        double beta = -(2 * (f + f2) * g + 2 * f_sq + 8 * g_sq);
        double gamma = -(4 * (f + f2) * g + 2 * f_sq + 10 * g_sq);
        double sigma_tot = sigma_0 * E_e * E_e * (alpha + beta * Delta / M + gamma * E_e / M);
        return sigma_tot;
    }
}


double vIBD::GetDifCrossSection(double E, double theta) const
{
    double result;

    static double f = 1;
    static double g = 1.26;
    double f_sq = f * f;
    double g_sq = g * g;
    static double f2 = 3.706;

    double Delta = MASSDELTA;
    double E_e = E - MASSDELTA;
    double sigma_0 = 0.0952 / (f_sq + 3 * g_sq) * 1e-42; // cm^2 / MeV^2
    double M_e = MASSELECTRON;
    double M = MASSPROTON;

    if (E_e < M_e) result = 0;
    else
    {
        double temp1 = 2 * (f + f2) * g * ((2 * E_e + Delta) * (1 - TMath::Cos(theta)));
        double temp2 = (f_sq + g_sq) * Delta * (1 + TMath::Cos(theta));
        double temp3 = (f_sq + 3 * g_sq) * (3 * (E_e + Delta) * (1 - TMath::Cos(theta)) - Delta);
        double temp4 = (f_sq - g_sq) * TMath::Cos(theta) * (3 * (E_e + Delta) * (1 - TMath::Cos(theta)) - Delta);
        double Gamma = temp1 + temp2 + temp3 + temp4;
        result = sigma_0 / 2 * E_e * E_e * ((f_sq + 3 * g_sq) + (f_sq - g_sq) * TMath::Cos(theta) - Gamma / M);
    }
    return result / 2 / TMath::Pi();
}
*/


double vIBD::GetMomentum_Positron(double E) const
{
    double E_e = E - MASSDELTA;
    double M_e = MASSELECTRON;
    if (E_e > M_e) return TMath::Sqrt(E_e * E_e - M_e * M_e);
    else return 0;
}

double vIBD::GetDifCrossSection(double E, double theta) const
{
    return GetDifCrossSection_costheta(E, TMath::Cos(theta));
}


double vIBD::GetEe1(double E, double theta) const
{
    double costheta = TMath::Cos(theta);
    double mp = MASSPROTON;
    double mn = MASSNEUTRON;
    double M = (mp + mn)/2;
    double me = MASSELECTRON;
    double Delta = MASSDELTA;
    double Ee0 = E - Delta;
    if (Ee0 < me) { return 0; }
    double pe0 = TMath::Sqrt(Ee0*Ee0 - me*me);
    double ve0 = pe0/Ee0;

    double d1 = E/M*(1 - ve0*costheta);
    double d2 = (Delta*Delta - me*me)/2/M;
    double Ee1 = Ee0*(1 - d1) - d2;
    if (Ee1*Ee1 - me*me < 0) { return 0; } 
    else { return Ee1; }
}

double vIBD::GetDifCrossSection_costheta(double E, double costheta) const
{
    double mp = MASSPROTON;
    double mn = MASSNEUTRON;
    double M = (mp + mn)/2;
    double me = MASSELECTRON;
    double Delta = MASSDELTA;
    double Ee0 = E - Delta;
    if (Ee0 < me) { return 0; }
    double pe0 = TMath::Sqrt(Ee0*Ee0 - me*me);
    double ve0 = pe0/Ee0;

    double f = 1;
    double g = 1.26;
    double f2 = 3.706;

    double c1 = 2*(f+f2)*g;
    double c2 = f*f + g*g;
    double c3 = f*f + 3*g*g;
    double c4 = f*f - g*g;

    double d1 = E/M*(1 - ve0*costheta);
    double d2 = (Delta*Delta - me*me)/2/M;
    double Ee1 = Ee0*(1 - d1) - d2;
    if (Ee1*Ee1 - me*me < 0) { return 0; } 
    double pe1 = TMath::Sqrt(Ee1*Ee1 - me*me);
    double ve1 = pe1/Ee1;

    double gamma = 0;
    gamma += c1*((2*Ee0 + Delta)*(1 - ve0*costheta) - me*me/Ee0);
    gamma += c2*(Delta*(1 + ve0*costheta) + me*me/Ee0);
    gamma += c3*((Ee0 + Delta)*(1 - ve0*costheta) - Delta);
    gamma += c4*((Ee0 + Delta)*(1 - ve0*costheta) - Delta) * ve0*costheta;

    double GF = 1.16637e-11;
    double Vud = 0.97373;
    double delta_inner = 0.024;
    double hbarc = 197.327053;

    double sig_0 = GF*GF * Vud*Vud / TMath::Pi() * (1. + delta_inner) * hbarc * hbarc * 1e-26;
    double dsig = (c3 + c4*ve1*costheta)*Ee1*pe1 - gamma*Ee0*pe0/M;
    dsig *= sig_0 / 2;

    return dsig;
}


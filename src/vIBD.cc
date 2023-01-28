#include "../header/vIBD.hh"
#include "../header/vConstant.hh"


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


double vIBD::GetMomentum_Positron(double E) const
{
    double E_e = E - MASSDELTA;
    double M_e = MASSELECTRON;
    if (E_e > M_e) return TMath::Sqrt(E_e * E_e - M_e * M_e);
    else return 0;
}

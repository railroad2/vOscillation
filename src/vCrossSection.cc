#include "vCrossSection.hh"


double vCrossSection::GetCrossSection_IBD(double E, int order=1)
{
    if (order == 1) return GetCrossSection_IBD_first(E);
    else if (order == 0) return GetCrossSection_IBD_zeroth(E);
    else return 0;
}


double vCrossSection::GetCrossSection_IBD_zeroth(double E)
{
    double E_e = E - mvConstant->GetMass("Delta");
    return 0.0952 * E_e * GetMomentum_Positron(E) * 1e-42;
}


double vCrossSection::GetCrossSection_IBD_first(double E)
{
    double f = 1;
    double g = 1.26;
    double f_sq = f * f;
    double g_sq = g * g;
    double f2 = 3.706;

    double Delta = mvConstant->GetMass("Delta");
    double E_e = E - Delta;
    double sigma_0 = 0.0952 / (f_sq + 3 * g_sq) * 1e-42; // cm^2 / MeV^2
    double M_e = mvConstant->GetMass("electron");
    double M = mvConstant->GetMass("proton");

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


double vCrossSection::GetMomentum_Positron(double E)
{
    double E_e = E - mvConstant->GetMass("Delta");
    double M_e = mvConstant->GetMass("electron");
    if (E_e > M_e) { return TMath::Sqrt(E_e * E_e - M_e * M_e); }
    else { return 0; }
}
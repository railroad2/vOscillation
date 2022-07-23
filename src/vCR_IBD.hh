#pragma once

#ifndef VCR_IBD_HH
#define VCR_IBD_HH


class vCR_IBD
{
    public:
        double operator()(double* x, double* p);
};


double vCR_IBD::operator()(double* x, double* p)
{
    double f = 1;
    double g = 1.26;
    double f_sq = f * f;
    double g_sq = g * g;
    double f2 = 3.706;

    double Delta = p[0]; // mvConstant->GetMass("Delta");
    double E_e = x[0] - Delta;
    double sigma_0 = 0.0952 / (f_sq + 3 * g_sq) * 1e-42; // cm^2 / MeV^2
    double M_e = p[1]; // mvConstant->GetMass("electron");
    double M = p[2]; //  mvConstant->GetMass("proton");

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


class vDifCR_IBD
{
public:
    double operator()(double* x, double* p);
};


double vDifCR_IBD::operator()(double* x, double* p)
{
    double result;

    double theta = x[0];

    double f = 1;
    double g = 1.26;
    double f_sq = f * f;
    double g_sq = g * g;
    double f2 = 3.706;

    double Delta = p[1]; // mvConstant->GetMass("Delta")
    double E_e = p[0] - Delta; // p[0] = E
    double sigma_0 = 0.0952 / (f_sq + 3 * g_sq) * 1e-42; // cm^2 / MeV^2
    double M_e = p[2]; // mvConstant->GetMass("electron")
    double M = p[3]; // mvConstant->GetMass("proton")

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
    return result;
}

#endif

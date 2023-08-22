#include <iostream>
#include "TMath.h"
#include "../header/vScatteringve.hh"
#include "../header/vConstant.hh"


double vScatteringve::GetDifCrossSection(double E, double T, TString vflavour) const
{
    // Bahcall - Neutrino electron scattering and solar neutrino experiments
    double sign_g_L = 0;
    if (vflavour == "e") sign_g_L = 1;
    else if (vflavour == "mu") sign_g_L = -1;
    else if (vflavour == "tau") sign_g_L = -1;
    else
    {
        std::cerr << " Wrong vflavour value : " << vflavour << ", should be e, mu, or tau." << std::endl;
        return 0;
    }

    static double sigma_0 = 1.7232659e-44; // cm^2 / MeV,  2 * G_F * G_F * m_e / pi
    static double SsqthW = 0.23121; // (4), PDG
    double g_L = SsqthW + 0.5 * sign_g_L;
    double g_R = SsqthW;
    double m_e = MASSELECTRON;

    double result = sigma_0 * (g_L * g_L + g_R * g_R * (1 - T / E) * (1 - T / E) - g_L * g_R * m_e * T / E / E);

    double T_max = E / (1 + m_e / 2 / E);
    if (T > T_max) result = 0;
    if (result < 0) result = 0;

    return result;
}


double vScatteringve::GetDifCrossSection_Correction(double E, double T, TString vflavour) const
{
    // Bahcall - Neutrino electron scattering and solar neutrino experiments

    double m_e = MASSELECTRON; // MeV
    static double sigma_0 = 1.7232659e-44; // cm^2 / MeV,  2 * G_F * G_F * m_e / pi
    static double SsqthW = 0.23121; // (4), PDG

    static double rho_NC_vl = 1.0126;
    double x = TMath::Sqrt(1 + 2 * m_e / T);
    double I = (1 / 3. + (3. - x * x) * (0.5 * x * TMath::Log((x + 1) / (x - 1)) - 1)) / 6.;
    double kappa_nue_e = 0.9791 + 0.0097 * I;
    double kappa_numu_e = 0.9970 - 0.00037 * I;

    double g_L_nue_e = rho_NC_vl * (0.5 - kappa_nue_e * SsqthW) - 1;
    double g_R_nue_e = -rho_NC_vl * kappa_nue_e * SsqthW;

    double g_L_numu_e = rho_NC_vl * (0.5 - kappa_numu_e * SsqthW);
    double g_R_numu_e = -rho_NC_vl * kappa_numu_e * SsqthW;

    double g_L, g_R;
    if (vflavour == "e")
    {
        g_L = g_L_nue_e;
        g_R = g_R_nue_e;
    }
    else if (vflavour == "mu" || vflavour == "tau")
    {
        g_L = g_L_numu_e;
        g_R = g_R_numu_e;
    }
    else
    {
        std::cerr << " Wrong vflavour value : " << vflavour << ", should be e, mu, or tau." << std::endl;
        return 0;
    }

    double q = E;
    double z = T / q;
    double E_e = T + m_e;
    double l = TMath::Sqrt(E_e * E_e - m_e * m_e);
    double beta = l / E_e;

    double L_z = -TMath::DiLog(z); // L(z), L(x) = -Li_2 (x)
    double L_beta = -TMath::DiLog(beta); // L(beta)
    double Logz = TMath::Log(z);

    static double alpha = 7.2973525693e-3; // (11) fine structure constant
    double term1 = E_e / l * TMath::Log((E_e + l) / m_e) - 1;
    double term2 = 2 * TMath::Log(1 - z - m_e / (E_e + l));
    double f_minus = term1 * (term2 - TMath::Log(1 - z) - 0.5 * Logz - 5. / 12.)
        + 0.5 * (L_z - L_beta) - 0.5 * TMath::Log(1 - z) * TMath::Log(1 - z) - (11. / 12. + z / 2) * TMath::Log(1 - z)
        + z * (Logz + 0.5 * TMath::Log(2 * q / m_e)) - (31. / 18. + Logz / 12.) * beta - 11. * z / 12. + z * z / 24.;
    double f_plus = (term1 * ((1 - z) * (1 - z) * (term2 - TMath::Log(1 - z) - 0.5 * Logz - 2. / 3.) - 0.5 * (z * z * Logz + 1 - z))
        - 0.5 * (1 - z) * (1 - z) * (TMath::Log(1 - z) * TMath::Log(1 - z) + beta * (-TMath::DiLog(1 - z) - Logz * TMath::Log(1 - z)))
        + TMath::Log(1 - z) * (0.5 * z * z * Logz + (1 - z) / 3. * (2 * z - 0.5)) + 0.5 * z * z * TMath::DiLog(1 - z) - z * (1 - 2 * z) / 3. * Logz - z * (1 - z) / 6.
        - beta / 12. * (Logz + (1 - z) * ((115. - 109. * z) / 6.))) / (1 - z) / (1 - z);

    double f_plusminus = term1 * term2;

    double Lterm = g_L * g_L * (1 + alpha / TMath::Pi() * f_minus);
    double Rterm = g_R * g_R * (1 - z) * (1 - z) * (1 + alpha / TMath::Pi() * f_plus);
    double LRterm = g_L * g_R * m_e / q * z * (1 + alpha / TMath::Pi() * f_plusminus);

    double result = sigma_0 * (Lterm + Rterm - LRterm);

    double T_max = E / (1 + m_e / 2 / E);
    if (T > T_max) result = 0;
    if (result < 0) result = 0;

    return result;
}

#include "vCrossSection.hh"


double vCrossSection::GetCrossSection_IBD(double E)
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


double vCrossSection::GetCrossSection_IBD_Zeroth(double E)
{
    double f = 1;
    double g = 1.26;
    double f_sq = f * f;
    double g_sq = g * g;
    double f2 = 3.706;

    double Delta = mvConstant->GetMass("Delta");
    double E_e = E - Delta;
    double sigma_0 = 0.0952 / (f_sq + 3 * g_sq) * 1e-42; // cm^2 / MeV^2

    double p_e = GetMomentum_Positron(E);
    return 0.0952 * 1e-42 * E_e * p_e;
}


TF1* vCrossSection::GetCrossSection_IBD_TF(double startE, double endE)
{
    TF1* f = new TF1("IBD", mCR_IBD, startE, endE, 3);
    f->SetParNames("Delta", "M_e", "M_p");
    f->SetParameter(0, mvConstant->GetMass("Delta"));
    f->SetParameter(1, mvConstant->GetMass("electron"));
    f->SetParameter(2, mvConstant->GetMass("proton"));
    cout << f << endl;
    return f;
}


double vCrossSection::GetDifCrossSection_IBD(double E, double theta)
{
    double result;
    
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

TF1* vCrossSection::GetDifCrossSection_IBD_TF(double starttheta, double endtheta)
{
    TF1* f = new TF1("dif IBD", mDifCR_IBD, starttheta, endtheta, 4);
    f->SetParNames("E_nu", "Delta", "M_e", "M_p");
    f->SetParameter(1, mvConstant->GetMass("Delta"));
    f->SetParameter(2, mvConstant->GetMass("electron"));
    f->SetParameter(3, mvConstant->GetMass("proton"));
    return f;
}


double vCrossSection::GetDifCrossSection_ve_Scattering(double E, double T, TString vflavour = "e")
{
    // Bahcall - Neutrino electron scattering and solar neutrino experiments
    double sign_g_L = 0;
    if (vflavour == "e") sign_g_L = 1;
    else if (vflavour == "mu") sign_g_L = -1;
    else if (vflavour == "tau") sign_g_L = -1;
    else
    {
        cerr << " Wrong vflavour value : " << vflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }
    
    double sigma_0 = 1.7232659e-44; // cm^2 / MeV,  2 * G_F * G_F * m_e / pi
    double SsqthW = 0.23121; // (4), PDG
    double g_L = SsqthW + 0.5 * sign_g_L;
    double g_R = SsqthW;
    double m_e = mvConstant->GetMass("electron");
    
    double result = sigma_0 * (g_L * g_L + g_R * g_R * (1 - T / E) * (1 - T / E) - g_L * g_R * m_e * T / E / E);

    double T_max = E / (1 + m_e / 2 / E);
    if (T > T_max) result = 0;
    if (result < 0) result = 0;

    return result;
}


double vCrossSection::GetDifCrossSection_ve_Scattering_Correction(double E, double T, TString vflavour)
{
    // Bahcall - Neutrino electron scattering and solar neutrino experiments

    double m_e = mvConstant->GetMass("electron"); // MeV
    double sigma_0 = 1.7232659e-44; // cm^2 / MeV,  2 * G_F * G_F * m_e / pi
    double SsqthW = 0.23121; // (4), PDG
    
    double rho_NC_vl = 1.0126;
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
        cerr << " Wrong vflavour value : " << vflavour << ", should be e, mu, or tau." << endl;
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

    double alpha = 7.2973525693e-3; // (11) fine structure constant
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


double vCrossSection::GetMomentum_Positron(double E)
{
    double E_e = E - mvConstant->GetMass("Delta");
    double M_e = mvConstant->GetMass("electron");
    if (E_e > M_e) { return TMath::Sqrt(E_e * E_e - M_e * M_e); }
    else { return 0; }
}
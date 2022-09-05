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
    double* x = new double[0];
    x[0] = E;
    double* p = new double[3];
    p[0] = Delta;
    p[1] = M_e;
    p[2] = M;
    // return mCR_IBD().operator(x, p);
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
    
    double sigma_0 = 8.8083e-45; // cm^2
    double SsqthW = 0.23;
    double g_L = SsqthW + 0.5 * sign_g_L;
    double g_R = SsqthW;
    double m_e = mvConstant->GetMass("electron");
    
    double result = sigma_0 * (g_L * g_L + g_R * g_R * (1 - T / E) * (1 - T / E) - g_L * g_R * m_e * T / E / E);

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
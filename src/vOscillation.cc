#include "../header/vOscillation.hh"
#include <stdexcept>


vOscillation::vOscillation()
{
    Settheta();
    SetDm2();
};
vOscillation::~vOscillation() {};


double vOscillation::GetProbability(double L, double E, TString iflavour, TString fflavour, bool anti) const
{
    // distance : m, energy : MeV
    int alpha;
    int beta;

    if (iflavour == "e") alpha = 1;
    else if (iflavour == "mu") alpha = 2;
    else if (iflavour == "tau") alpha = 3;
    else
    {
        std::cerr << " Wrong iflavour value : " << iflavour << ", should be e, mu, or tau." << std::endl;
        return 0;
    }

    if (fflavour == "e") beta = 1;
    else if (fflavour == "mu") beta = 2;
    else if (fflavour == "tau") beta = 3;
    else
    {
        std::cerr << " Wrong fflavour value : " << fflavour << ", should be e, mu, or tau." << std::endl;
        return 0;
    }

    double delta_ab;
    if (alpha == beta) delta_ab = 1.;
    else delta_ab = 0.;

    TComplex U_i1 = GetPMNSmatrix(alpha, 1);
    TComplex U_i2 = GetPMNSmatrix(alpha, 2);
    TComplex U_i3 = GetPMNSmatrix(alpha, 3);
    TComplex U_f1 = GetPMNSmatrix(beta, 1);
    TComplex U_f2 = GetPMNSmatrix(beta, 2);
    TComplex U_f3 = GetPMNSmatrix(beta, 3);

    TComplex UUUU_12 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i2) * U_f2;
    TComplex UUUU_13 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i3) * U_f3;
    TComplex UUUU_23 = U_i2 * TComplex::Conjugate(U_f2) * TComplex::Conjugate(U_i3) * U_f3;

    double unitconst = 1.2669328;

    double sin2_dm2_21 = TMath::Sin(unitconst * fDm2_21 * L / E) * TMath::Sin(unitconst * fDm2_21 * L / E);
    double sin2_dm2_31 = TMath::Sin(unitconst * fDm2_31 * L / E) * TMath::Sin(unitconst * fDm2_31 * L / E);
    double sin2_dm2_32 = TMath::Sin(unitconst * fDm2_32 * L / E) * TMath::Sin(unitconst * fDm2_32 * L / E);

    double sin_2dm2_21 = TMath::Sin(unitconst * 2 * fDm2_21 * L / E);
    double sin_2dm2_31 = TMath::Sin(unitconst * 2 * fDm2_31 * L / E);
    double sin_2dm2_32 = TMath::Sin(unitconst * 2 * fDm2_32 * L / E);

    double Sympart = UUUU_12.Re() * sin2_dm2_21
        + UUUU_13.Re() * sin2_dm2_31
        + UUUU_23.Re() * sin2_dm2_32;
    double Asympart = UUUU_12.Im() * sin_2dm2_21
        + UUUU_13.Im() * sin_2dm2_31
        + UUUU_23.Im() * sin_2dm2_32;

    if (anti) return delta_ab - 4 * Sympart - 2 * Asympart;
    else      return delta_ab - 4 * Sympart + 2 * Asympart;
}


double vOscillation::GetProbability_Smear(TString iflavour, TString fflavour) const
{
    // distance : m, energy : MeV
    int alpha;
    int beta;

    if (iflavour == "e") alpha = 1;
    else if (iflavour == "mu") alpha = 2;
    else if (iflavour == "tau") alpha = 3;
    else
    {
        std::cerr << " Wrong iflavour value : " << iflavour << ", should be e, mu, or tau." << std::endl;
        return 0;
    }

    if (fflavour == "e") beta = 1;
    else if (fflavour == "mu") beta = 2;
    else if (fflavour == "tau") beta = 3;
    else
    {
        std::cerr << " Wrong fflavour value : " << fflavour << ", should be e, mu, or tau." << std::endl;
        return 0;
    }

    double delta_ab;
    if (alpha == beta) delta_ab = 1;
    else delta_ab = 0;

    TComplex U_i1 = GetPMNSmatrix(alpha, 1);
    TComplex U_i2 = GetPMNSmatrix(alpha, 2);
    TComplex U_i3 = GetPMNSmatrix(alpha, 3);
    TComplex U_f1 = GetPMNSmatrix(beta, 1);
    TComplex U_f2 = GetPMNSmatrix(beta, 2);
    TComplex U_f3 = GetPMNSmatrix(beta, 3);

    TComplex UUUU_12 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i2) * U_f2;
    TComplex UUUU_13 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i3) * U_f3;
    TComplex UUUU_23 = U_i2 * TComplex::Conjugate(U_f2) * TComplex::Conjugate(U_i3) * U_f3;

    double Sympart = UUUU_12.Re() + UUUU_13.Re() + UUUU_23.Re();

    return delta_ab - 2 * Sympart;
}


TComplex vOscillation::GetPMNSmatrix(int row, int column) const
{
    double rad_delta_CP = fdelta_CP * TMath::Pi() / 180;

    double s_12 = TMath::Sin(frad_12);
    double s_13 = TMath::Sin(frad_13);
    double s_23 = TMath::Sin(frad_23);
    double c_12 = TMath::Cos(frad_12);
    double c_13 = TMath::Cos(frad_13);
    double c_23 = TMath::Cos(frad_23);
    double s_delta_CP = TMath::Sin(rad_delta_CP);
    double c_delta_CP = TMath::Cos(rad_delta_CP);

    if (row == 1)
    {
        if (column == 1)
        {
            return TComplex(c_12 * c_13);
        }
        else if (column == 2)
        {
            return TComplex(s_12 * c_13);
        }
        else if (column == 3)
        {
            double real = s_13 * c_delta_CP;
            double imag = -s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else
        {
            return 0;
        }
    }
    else if (row == 2)
    {
        if (column == 1)
        {
            double real = -s_12 * c_23 - c_12 * s_23 * s_13 * c_delta_CP;
            double imag = -c_12 * s_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if (column == 2)
        {
            double real = c_12 * c_23 - s_12 * s_23 * s_13 * c_delta_CP;
            double imag = -s_12 * s_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if (column == 3)
        {
            double real = s_23 * c_13;
            return TComplex(real);
        }
        else
        {
            return 0;
        }
    }
    else if (row == 3)
    {
        if (column == 1)
        {
            double real = s_12 * s_23 - c_12 * c_23 * s_13 * c_delta_CP;
            double imag = -c_12 * c_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if (column == 2)
        {
            double real = -c_12 * s_23 - s_12 * c_23 * s_13 * c_delta_CP;
            double imag = -s_12 * c_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if (column == 3)
        {
            double real = c_23 * c_13;
            return TComplex(real);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}


void vOscillation::LoadStdData(bool IO)
{
    if (IO == false)
    {
        double sin2_12 = PDGNO_sin2_12;
        double sin2_13 = PDGNO_sin2_13;
        double sin2_23 = PDGNO_sin2_23;
        double dm21 = PDGNO_Dm2_21;
        double dm31 = PDGNO_Dm2_31;
        double dcp = PDGNO_delta_CP;
        double r12 = TMath::ASin(TMath::Sqrt(sin2_12));
        double r13 = TMath::ASin(TMath::Sqrt(sin2_13));
        double r23 = TMath::ASin(TMath::Sqrt(sin2_23));
        Setradian(r12, r13, r23);
        SetDm2(dm21, dm31);
        Setdelta_CP(dcp);
    }
    else
    {
        double sin2_12 = PDGIO_sin2_12;
        double sin2_13 = PDGIO_sin2_13;
        double sin2_23 = PDGIO_sin2_23;
        double dm21 = PDGIO_Dm2_21;
        double dm31 = PDGIO_Dm2_31;
        double dcp = PDGIO_delta_CP;
        double r12 = TMath::ASin(TMath::Sqrt(sin2_12));
        double r13 = TMath::ASin(TMath::Sqrt(sin2_13));
        double r23 = TMath::ASin(TMath::Sqrt(sin2_23));
        Setradian(r12, r13, r23);
        SetDm2(dm21, dm31);
        Setdelta_CP(dcp);
    }

}


void vOscillation::Settheta(double theta_12, double theta_13, double theta_23)
{
    ftheta_12 = theta_12;
    ftheta_13 = theta_13;
    ftheta_23 = theta_23;
    frad_12 = theta_12 / 180 * TMath::Pi();
    frad_13 = theta_13 / 180 * TMath::Pi();
    frad_23 = theta_23 / 180 * TMath::Pi();
}


void vOscillation::Setradian(double rad_12, double rad_13, double rad_23)
{
    frad_12 = rad_12;
    frad_13 = rad_13;
    frad_23 = rad_23;
    ftheta_12 = rad_12 / TMath::Pi() * 180;
    ftheta_13 = rad_13 / TMath::Pi() * 180;
    ftheta_23 = rad_23 / TMath::Pi() * 180;
}


void vOscillation::SetDm2(double Dm2_21, double Dm2_31)
{
    fDm2_21 = Dm2_21;
    fDm2_31 = Dm2_31;
    fDm2_32 = Dm2_31 - Dm2_21;
}

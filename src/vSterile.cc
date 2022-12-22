#include "../header/vSterile.hh"


double vSterile::GetProbability(double L, double E, TString iflavour, TString fflavour, bool anti)
{
    // distance : m, energy : MeV
    int alpha;
    int beta;

    if (iflavour == "e") alpha = 1;
    else if (iflavour == "mu") alpha = 2;
    else if (iflavour == "tau") alpha = 3;
    else
    {
        cerr << " Wrong iflavour value : " << iflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }

    if (fflavour == "e") beta = 1;
    else if (fflavour == "mu") beta = 2;
    else if (fflavour == "tau") beta = 3;
    else
    {
        cerr << " Wrong fflavour value : " << fflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }

    double delta_ab;
    if (alpha == beta) delta_ab = 1.;
    else delta_ab = 0.;

    TComplex U_i1 = GetPMNSmatrix(alpha, 1);
    TComplex U_i2 = GetPMNSmatrix(alpha, 2);
    TComplex U_i3 = GetPMNSmatrix(alpha, 3);
    TComplex U_i4 = GetPMNSmatrix_Truncated(alpha, 4);
    TComplex U_f1 = GetPMNSmatrix(beta, 1);
    TComplex U_f2 = GetPMNSmatrix(beta, 2);
    TComplex U_f3 = GetPMNSmatrix(beta, 3);
    TComplex U_f4 = GetPMNSmatrix_Truncated(beta, 4);

    TComplex UUUU_12 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i2) * U_f2;
    TComplex UUUU_13 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i3) * U_f3;
    TComplex UUUU_23 = U_i2 * TComplex::Conjugate(U_f2) * TComplex::Conjugate(U_i3) * U_f3;
    TComplex UUUU_14 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i4) * U_f4;
    TComplex UUUU_24 = U_i2 * TComplex::Conjugate(U_f2) * TComplex::Conjugate(U_i4) * U_f4;
    TComplex UUUU_34 = U_i3 * TComplex::Conjugate(U_f3) * TComplex::Conjugate(U_i4) * U_f4;

    double unitconst = 1.2669328;

    double sin2_dm2_21 = TMath::Sin(unitconst * fDm2_21 * L / E) * TMath::Sin(unitconst * fDm2_21 * L / E);
    double sin2_dm2_31 = TMath::Sin(unitconst * fDm2_31 * L / E) * TMath::Sin(unitconst * fDm2_31 * L / E);
    double sin2_dm2_32 = TMath::Sin(unitconst * fDm2_32 * L / E) * TMath::Sin(unitconst * fDm2_32 * L / E);
    double sin2_dm2_41 = TMath::Sin(unitconst * fDm2_41 * L / E) * TMath::Sin(unitconst * fDm2_41 * L / E);
    double sin2_dm2_42 = TMath::Sin(unitconst * fDm2_42 * L / E) * TMath::Sin(unitconst * fDm2_42 * L / E);
    double sin2_dm2_43 = TMath::Sin(unitconst * fDm2_43 * L / E) * TMath::Sin(unitconst * fDm2_43 * L / E);

    double sin_2dm2_21 = TMath::Sin(unitconst * 2 * fDm2_21 * L / E);
    double sin_2dm2_31 = TMath::Sin(unitconst * 2 * fDm2_31 * L / E);
    double sin_2dm2_32 = TMath::Sin(unitconst * 2 * fDm2_32 * L / E);
    double sin_2dm2_41 = TMath::Sin(unitconst * 2 * fDm2_41 * L / E);
    double sin_2dm2_42 = TMath::Sin(unitconst * 2 * fDm2_42 * L / E);
    double sin_2dm2_43 = TMath::Sin(unitconst * 2 * fDm2_43 * L / E);

    double Sympart  = UUUU_12.Re() * sin2_dm2_21
                    + UUUU_13.Re() * sin2_dm2_31
                    + UUUU_23.Re() * sin2_dm2_32
                    + UUUU_14.Re() * sin2_dm2_41
                    + UUUU_24.Re() * sin2_dm2_42
                    + UUUU_34.Re() * sin2_dm2_43;
    double Asympart = UUUU_12.Im() * sin_2dm2_21
                    + UUUU_13.Im() * sin_2dm2_31
                    + UUUU_23.Im() * sin_2dm2_32
                    + UUUU_14.Im() * sin_2dm2_41
                    + UUUU_24.Im() * sin_2dm2_42
                    + UUUU_34.Im() * sin_2dm2_43;

    if (anti) return delta_ab - 4 * Sympart - 2 * Asympart;
    else      return delta_ab - 4 * Sympart + 2 * Asympart;
}


double vSterile::GetProbability_Smear(TString iflavour, TString fflavour)
{
    // distance : m, energy : MeV
    int alpha;
    int beta;

    if (iflavour == "e") alpha = 1;
    else if (iflavour == "mu") alpha = 2;
    else if (iflavour == "tau") alpha = 3;
    else
    {
        cerr << " Wrong iflavour value : " << iflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }

    if (fflavour == "e") beta = 1;
    else if (fflavour == "mu") beta = 2;
    else if (fflavour == "tau") beta = 3;
    else
    {
        cerr << " Wrong fflavour value : " << fflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }

    double delta_ab;
    if (alpha == beta) delta_ab = 1.;
    else delta_ab = 0.;

    TComplex U_i1 = GetPMNSmatrix(alpha, 1);
    TComplex U_i2 = GetPMNSmatrix(alpha, 2);
    TComplex U_i3 = GetPMNSmatrix(alpha, 3);
    TComplex U_i4 = GetPMNSmatrix_Truncated(alpha, 4);
    TComplex U_f1 = GetPMNSmatrix(beta, 1);
    TComplex U_f2 = GetPMNSmatrix(beta, 2);
    TComplex U_f3 = GetPMNSmatrix(beta, 3);
    TComplex U_f4 = GetPMNSmatrix_Truncated(beta, 4);

    TComplex UUUU_12 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i2) * U_f2;
    TComplex UUUU_13 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i3) * U_f3;
    TComplex UUUU_23 = U_i2 * TComplex::Conjugate(U_f2) * TComplex::Conjugate(U_i3) * U_f3;
    TComplex UUUU_14 = U_i1 * TComplex::Conjugate(U_f1) * TComplex::Conjugate(U_i4) * U_f4;
    TComplex UUUU_24 = U_i2 * TComplex::Conjugate(U_f2) * TComplex::Conjugate(U_i4) * U_f4;
    TComplex UUUU_34 = U_i3 * TComplex::Conjugate(U_f3) * TComplex::Conjugate(U_i4) * U_f4;

    double unitconst = 1.2669328;

    double Sympart  = UUUU_12.Re() + UUUU_13.Re() + UUUU_23.Re()
                    + UUUU_14.Re() + UUUU_24.Re() + UUUU_34.Re();

    return delta_ab - 2 * Sympart;
}


TComplex vSterile::GetPMNSmatrix_Truncated(int row, int column)
{
	if (column == 4)
	{
		double s_14 = TMath::Sin(frad_14);
		double c_14 = TMath::Cos(frad_14);
		double s_24 = TMath::Sin(frad_24);
		double c_24 = TMath::Cos(frad_24);
		double s_34 = TMath::Sin(frad_34);
		if (row == 1) return TComplex(s_14, 0);
		else if (row == 2) return TComplex(c_14 * s_24, 0);
		else if (row == 3) return TComplex(c_14 * c_24 * s_34, 0);
		else return 0;
	}
	else return GetPMNSmatrix(row, column);
}


void vSterile::Load4StdData()
{
    Set4radian( TMath::ASin(0.1),               // v_e disappearence global fit, sin_14 ~ 0.1
                TMath::ASin(TMath::Sqrt(0.15)), // v_mu -> v_e oscillating global fit, 4|U_e4|^2|U_m4|^2 ~ 0.6
                0);                             // constraint : |U_tau,4|^2 < 0.13
    Set4Dm2(1.3); // v_e disappearence global fit

    // reference
    // Mona Dentler, et al., Updated global analysis of neutrino oscillations in the presence of eV-scale sterile neutrinos, Mar 2018, arXiv:1803.10661v1
}


void vSterile::Set4theta(double theta_14, double theta_24, double theta_34)
{
    ftheta_14 = theta_14;
    ftheta_24 = theta_24;
    ftheta_34 = theta_34;
    frad_14 = theta_14 / 180. * TMath::Pi();
    frad_24 = theta_24 / 180. * TMath::Pi();
    frad_34 = theta_34 / 180. * TMath::Pi();
}


void vSterile::Set4radian(double rad_14, double rad_24, double rad_34)
{
    frad_14 = rad_14;
    frad_24 = rad_24;
    frad_34 = rad_34;
    ftheta_14 = rad_14 / TMath::Pi() * 180;
    ftheta_24 = rad_24 / TMath::Pi() * 180;
    ftheta_34 = rad_34 / TMath::Pi() * 180;
}


void vSterile::Set4Dm2(double Dm2_41)
{
    fDm2_41 = Dm2_41;
    fDm2_42 = Dm2_41 - fDm2_21;
    fDm2_43 = Dm2_41 - fDm2_31;
}

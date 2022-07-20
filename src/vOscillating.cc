#include"vOscillating.hh"
#include <fstream>
#include <stdexcept>


using namespace std;


vOscillating::vOscillating()
{
    Settheta();
    SetDm2();
};
vOscillating::~vOscillating(){};


double vOscillating::GetProbability(double L, double E, TString iflavour, TString fflavour, bool anti)
{
    // dist : m, energy : MeV
    int alpha;
    int beta;
    
    if(iflavour=="e") alpha = 1;
    else if(iflavour=="mu") alpha = 2;
    else if(iflavour=="tau") alpha = 3;
    else
    {
        cerr << " Wrong iflavour value : " << iflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }

    if(fflavour=="e") beta = 1;
    else if(fflavour=="mu") beta = 2;
    else if(fflavour=="tau") beta = 3;
    else
    {
        cerr << " Wrong fflavour value : " << fflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }


    double delta_ab;
    if(alpha == beta) delta_ab = 1;
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
    
    double unitconst = 1.2669328;

    double sin2_dm2_21 = TMath::Sin(unitconst * mDm2_21 * L / E) * TMath::Sin(unitconst * mDm2_21 * L / E);
    double sin2_dm2_31 = TMath::Sin(unitconst * mDm2_31 * L / E) * TMath::Sin(unitconst * mDm2_31 * L / E);
    double sin2_dm2_32 = TMath::Sin(unitconst * mDm2_32 * L / E) * TMath::Sin(unitconst * mDm2_32 * L / E);
    
    double sin_2dm2_21 = TMath::Sin(unitconst * 2 * mDm2_21 * L / E);
    double sin_2dm2_31 = TMath::Sin(unitconst * 2 * mDm2_31 * L / E);
    double sin_2dm2_32 = TMath::Sin(unitconst * 2 * mDm2_32 * L / E);

    double Sympart  = UUUU_12.Re() * sin2_dm2_21
                    + UUUU_13.Re() * sin2_dm2_31
                    + UUUU_23.Re() * sin2_dm2_32;
    double Asympart = UUUU_12.Im() * sin_2dm2_21
                    + UUUU_13.Im() * sin_2dm2_31
                    + UUUU_23.Im() * sin_2dm2_32;

    if(anti)
    {
        return delta_ab - 4 * Sympart - 2 * Asympart;
    }
    else
    {
        return delta_ab - 4 * Sympart + 2 * Asympart;
    }
}


TComplex vOscillating::GetPMNSmatrix(int row, int column)
{
    double rad_12       = mtheta_12 * TMath::Pi() / 180; 
    double rad_13       = mtheta_13 * TMath::Pi() / 180; 
    double rad_23       = mtheta_23 * TMath::Pi() / 180;
    double rad_delta_CP = mdelta_CP * TMath::Pi() / 180;

    double s_12 = TMath::Sin(rad_12);
    double s_13 = TMath::Sin(rad_13);
    double s_23 = TMath::Sin(rad_23);
    double c_12 = TMath::Cos(rad_12);
    double c_13 = TMath::Cos(rad_13);
    double c_23 = TMath::Cos(rad_23);
    double s_delta_CP = TMath::Sin(rad_delta_CP);
    double c_delta_CP = TMath::Cos(rad_delta_CP);

    if(row == 1)
    {
        if(column == 1)
        {
            return TComplex(c_12 * c_13);
        }
        else if(column == 2)
        {
            return TComplex(s_12 * c_13);
        }
        else if(column == 3)
        {
            double real = s_13 * c_delta_CP;
            double imag = - s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else
        {
            return 0;
        }
    }
    else if(row == 2)
    {
        if(column == 1)
        {
            double real = - s_12 * c_23 - c_12 * s_23 * s_13 * c_delta_CP;
            double imag = - c_12 * s_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if(column == 2)
        {
            double real = c_12 * c_23 - s_12 * s_23 * s_13 * c_delta_CP;
            double imag = - s_12 * s_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if(column == 3)
        {
            double real = s_23 * c_13;
            return TComplex(real);
        }
        else
        {
            return 0;
        }
    }
    else if(row == 3)
    {
        if(column == 1)
        {
            double real = s_12 * s_23 - c_12 * c_23 * s_13 * c_delta_CP;
            double imag = - c_12 * c_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if(column == 2)
        {
            double real = - c_12 * s_23 - s_12 * c_23 * s_13 * c_delta_CP;
            double imag = - s_12 * c_23 * s_13 * s_delta_CP;
            return TComplex(real, imag);
        }
        else if(column == 3)
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


double vOscillating::GetCPAsymmetry(double L, double E, TString iflavour, TString fflavour)
{
	int alpha;
    int beta;
    
    if(iflavour=="e") alpha = 1;
    else if(iflavour=="mu") alpha = 2;
    else if(iflavour=="tau") alpha = 3;
    else
    {
        cerr << " Wrong iflavour value : " << iflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }

    if(fflavour=="e") beta = 1;
    else if(fflavour=="mu") beta = 2;
    else if(fflavour=="tau") beta = 3;
    else
    {
        cerr << " Wrong fflavour value : " << fflavour << ", should be e, mu, or tau." << endl;
        return 0;
    }
	
	if(alpha == beta) return 0;
	else
	{
		int epsilon = 0;
		if(alpha==1 and beta==2) epsilon = 1;
		else if(alpha==2 and beta==1) epsilon = -1;
		else if(alpha==1 and beta==3) epsilon = -1;
		else if(alpha==3 and beta==1) epsilon = 1;
		else if(alpha==2 and beta==3) epsilon = 1;
		else if(alpha==3 and beta==2) epsilon = -1;
		
		TComplex U_e1 = GetPMNSmatrix(1, 1);
		TComplex U_m1 = GetPMNSmatrix(2, 1);
		TComplex U_e2 = GetPMNSmatrix(1, 2);
		TComplex U_m2 = GetPMNSmatrix(2, 2);
		double J = (U_e1 * TComplex::Conjugate(U_m1) * TComplex::Conjugate(U_e2) * U_m2).Im();
		
		double unitconst = 1.2669328;
		
		double sin_dm2_21 = TMath::Sin(unitconst * mDm2_21 * L / E);
		double sin_dm2_31 = TMath::Sin(unitconst * mDm2_31 * L / E);
		double sin_dm2_32 = TMath::Sin(unitconst * mDm2_32 * L / E);
		
		return 16 * epsilon * J * sin_dm2_21 * sin_dm2_31 * sin_dm2_32;
	}
}


void vOscillating::LoadStdData(bool IO, bool withSK)
{
    if(IO == false)
    {
        if(withSK == false)
        {
            double t12  = stdNO_theta_12;
            double t13  = stdNO_theta_13;
            double t23  = stdNO_theta_23;
            double dm21 = stdNO_Dm2_21;
            double dm31 = stdNO_Dm2_31;
            double dcp  = stdNO_delta_CP;
            Settheta(t12, t13, t23);
            SetDm2(dm21, dm31, false);
            Setdelta_CP(dcp);
        }
        else
        {
            double t12  = stdNO_SKatm_theta_12;
            double t13  = stdNO_SKatm_theta_13;
            double t23  = stdNO_SKatm_theta_23;
            double dm21 = stdNO_SKatm_Dm2_21;
            double dm31 = stdNO_SKatm_Dm2_31;
            double dcp  = stdNO_SKatm_delta_CP;
            Settheta(t12, t13, t23);
            SetDm2(dm21, dm31, false);
            Setdelta_CP(dcp);
        }
    }
    else
    {
        if(withSK == false)
        {
            double t12  = stdIO_theta_12;
            double t13  = stdIO_theta_13;
            double t23  = stdIO_theta_23;
            double dm21 = stdIO_Dm2_21;
            double dm31 = stdIO_Dm2_31;
            double dcp  = stdIO_delta_CP;
            Settheta(t12, t13, t23);
            SetDm2(dm21, dm31, true);
            Setdelta_CP(dcp);
        }
        else
        {
            double t12  = stdIO_SKatm_theta_12;
            double t13  = stdIO_SKatm_theta_13;
            double t23  = stdIO_SKatm_theta_23;
            double dm21 = stdIO_SKatm_Dm2_21;
            double dm31 = stdIO_SKatm_Dm2_31;
            double dcp  = stdIO_SKatm_delta_CP;
            Settheta(t12, t13, t23);
            SetDm2(dm21, dm31, true);
            Setdelta_CP(dcp);
        }
    }
}


void vOscillating::Settheta(double theta_12, double theta_13, double theta_23)
{
    mtheta_12 = theta_12;
    mtheta_13 = theta_13;
    mtheta_23 = theta_23;
    mrad_12 = theta_12 / 180 * TMath::Pi();
    mrad_13 = theta_13 / 180 * TMath::Pi();
    mrad_23 = theta_23 / 180 * TMath::Pi();
}


void vOscillating::Setradian(double rad_12, double rad_13, double rad_23)
{
    mrad_12 = rad_12;
    mrad_13 = rad_13;
    mrad_23 = rad_23;
    mtheta_12 = rad_12 / TMath::Pi() * 180;
    mtheta_13 = rad_13 / TMath::Pi() * 180;
    mtheta_23 = rad_23 / TMath::Pi() * 180;
}


void vOscillating::SetDm2(double Dm2_21, double Dm2_31, bool IO)
{
    // Error Handling
    
    try
    {
        if(Dm2_21 < 0) throw invalid_argument("Dm2_21 should be positive.");
        if (IO)
        {
            if (Dm2_31 > 0) throw invalid_argument("With Inverse Ordering, Dm2_31 should be negative.");
            else cout << "vOscillating : Inverse Ordering is selected." << endl;
        }
        else
        {
            if(Dm2_31 < 0) throw invalid_argument("With Normal Ordering, Dm2_31 should be positive.");
            else cout << "vOscillating : Normal Ordering is selected." << endl;
        }
    }
    catch(invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }

    //Setter
    mDm2_21 = Dm2_21;
    mDm2_31 = Dm2_31;
    mDm2_32 = Dm2_31 - Dm2_21;
}


void vOscillating::Setdelta_CP(double delta_CP)
{
    mdelta_CP = delta_CP;
}


std::vector<double> vOscillating::Gettheta()
{
    return {mtheta_12, mtheta_13, mtheta_23};
}


std::vector<double> vOscillating::Getradian()
{
    return {mrad_12, mrad_13, mrad_23};
}


std::vector<double> vOscillating::GetDm2()
{
    return {mDm2_21, mDm2_31, mDm2_32};
}


double vOscillating::Getdelta_CP()
{
    return mdelta_CP;
}


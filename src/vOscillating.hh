#pragma once

#ifndef vOscillating_hh
#define vOscillating_hh

#include <iostream>
#include <vector>

#include "TComplex.h"
#include "TMath.h"
#include "TString.h"


class vOscillating
{
    public:
        vOscillating();
        virtual ~vOscillating();
    
    // Main Method
        double   GetProbability(double L, double E, TString iflavour, TString fflavour, bool anti=false);
        TComplex GetPMNSmatrix(int row, int column);
		double   GetCPAsymmetry(double L, double E, TString iflavour, TString fflavour);
    
    // DataLoader (Setter)
        void LoadStdData(bool IO=false, bool withSK=false);

    // Setter and Getter
        void Settheta(double theta_12=33.44, double theta_13=8.57, double theta_23=49.2);
        void Setradian(double rad_12, double rad_13, double rad_23);
        void SetDm2(double Dm2_21=0.0000759, double Dm2_31=0.00232, bool IO=false);
        void Setdelta_CP(double delta_CP);
        std::vector<double> Gettheta();
        std::vector<double> Getradian();
        std::vector<double> GetDm2();
        double Getdelta_CP();


    private:
        double mtheta_12 = 33.44;     // degree
        double mtheta_13 = 8.57;      // degree
        double mtheta_23 = 49.2;      // degree
        double mrad_12;               // radian
        double mrad_13;               // radian
        double mrad_23;               // radian
        double mDm2_21   = 0.0000742; // eV^2
        double mDm2_31   = 0.002515;  // eV^2
        double mDm2_32;               // eV^2
        double mdelta_CP  = 194;      // degree

    // Standard Value
    // Reference:
    // [1] JHEP 09 (2020) 178 [arXiv:2007.14792] 
    // [2] NuFIT 5.1 (2021), www.nu-fit.org
        // without SK atmospheric v data
        //   Normal Ordering
        double stdNO_theta_12 = 33.44;
        double stdNO_theta_13 = 8.57;
        double stdNO_theta_23 = 49.2;
        double stdNO_Dm2_21 = 0.0000742;
        double stdNO_Dm2_31 = 0.002515;
        double stdNO_Dm2_32 = 0.002515 - 0.0000742;
        double stdNO_delta_CP = 194;
        //   Inverse Ordering 
        double stdIO_theta_12 = 33.45;
        double stdIO_theta_13 = 8.60;
        double stdIO_theta_23 = 49.5;
        double stdIO_Dm2_21 = 0.0000742;
        double stdIO_Dm2_31 = -0.002498;
        double stdIO_Dm2_32 = -0.002498 - 0.0000742;
        double stdIO_delta_CP = 287;
        // with SK atmospheric v data
        //   Normal Ordering
        double stdNO_SKatm_theta_12 = 33.45;
        double stdNO_SKatm_theta_13 = 8.62;
        double stdNO_SKatm_theta_23 = 42.1;
        double stdNO_SKatm_Dm2_21 = 0.0000742;
        double stdNO_SKatm_Dm2_31 = 0.002510;
        double stdNO_SKatm_Dm2_32 = 0.002510 - 0.0000742;
        double stdNO_SKatm_delta_CP = 230;
        //   Inverse Ordering
        double stdIO_SKatm_theta_12 = 33.45;
        double stdIO_SKatm_theta_13 = 8.61;
        double stdIO_SKatm_theta_23 = 49.0;
        double stdIO_SKatm_Dm2_21 = 0.0000742;
        double stdIO_SKatm_Dm2_31 = -0.002490;
        double stdIO_SKatm_Dm2_32 = -0.002490 - 0.0000742;
        double stdIO_SKatm_delta_CP = 278;
        
};

#endif


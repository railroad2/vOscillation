#pragma once

#ifndef VOSCILLATING_HH
#define VOSCILLATING_HH

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
        double   GetProbability_Smear(TString iflavour, TString fflavour);
        TComplex GetPMNSmatrix(int row, int column);
		double   GetCPAsymmetry(double L, double E, TString iflavour, TString fflavour);
    
    // DataLoader (Setter)
        void LoadStdData_PDG(bool IO = false);
        void LoadStdData_NuFit(bool IO = false, bool withSK = false);

    // Setter and Getter
        void Settheta(double theta_12 = 33.44, double theta_13 = 8.57, double theta_23 = 49.2);
        void Setradian(double rad_12, double rad_13, double rad_23);
        void SetDm2(double Dm2_21 = 0.0000742, double Dm2_31 = 0.002515, bool IO = false);
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
    // [1] PDG, www.pdg.org
        // Normal Ordering
        double PDGNO_sin2_12 = 0.307;
        double PDGNO_sin2_13 = 0.0220;
        double PDGNO_sin2_23 = 0.546;
        double PDGNO_Dm2_21 = 0.0000753;
        double PDGNO_Dm2_31 = 0.002453 + 0.0000753;
        double PDGNO_Dm2_32 = 0.002453;
        double PDGNO_delta_CP = 1.36 * 180;

        // Inverse Ordering
        double PDGIO_sin2_12 = 0.307;
        double PDGIO_sin2_13 = 0.0220;
        double PDGIO_sin2_23 = 0.539;
        double PDGIO_Dm2_21 = 0.0000753;
        double PDGIO_Dm2_31 = -0.002536 + 0.0000753;
        double PDGIO_Dm2_32 = -0.002536;
        double PDGIO_delta_CP = 1.36 * 180;

    // [2] JHEP 09 (2020) 178 [arXiv:2007.14792] 
    // [3] NuFIT 5.1 (2021), www.nu-fit.org
        // without SK atmospheric v data
        //   Normal Ordering
        double NuFitNO_theta_12 = 33.44;
        double NuFitNO_theta_13 = 8.57;
        double NuFitNO_theta_23 = 49.2;
        double NuFitNO_Dm2_21 = 0.0000742;
        double NuFitNO_Dm2_31 = 0.002515;
        double NuFitNO_Dm2_32 = 0.002515 - 0.0000742;
        double NuFitNO_delta_CP = 194;
        //   Inverse Ordering 
        double NuFitIO_theta_12 = 33.45;
        double NuFitIO_theta_13 = 8.60;
        double NuFitIO_theta_23 = 49.5;
        double NuFitIO_Dm2_21 = 0.0000742;
        double NuFitIO_Dm2_31 = -0.002498;
        double NuFitIO_Dm2_32 = -0.002498 - 0.0000742;
        double NuFitIO_delta_CP = 287;
        // with SK atmospheric v data
        //   Normal Ordering
        double NuFitNO_SKatm_theta_12 = 33.45;
        double NuFitNO_SKatm_theta_13 = 8.62;
        double NuFitNO_SKatm_theta_23 = 42.1;
        double NuFitNO_SKatm_Dm2_21 = 0.0000742;
        double NuFitNO_SKatm_Dm2_31 = 0.002510;
        double NuFitNO_SKatm_Dm2_32 = 0.002510 - 0.0000742;
        double NuFitNO_SKatm_delta_CP = 230;
        //   Inverse Ordering
        double NuFitIO_SKatm_theta_12 = 33.45;
        double NuFitIO_SKatm_theta_13 = 8.61;
        double NuFitIO_SKatm_theta_23 = 49.0;
        double NuFitIO_SKatm_Dm2_21 = 0.0000742;
        double NuFitIO_SKatm_Dm2_31 = -0.002490;
        double NuFitIO_SKatm_Dm2_32 = -0.002490 - 0.0000742;
        double NuFitIO_SKatm_delta_CP = 278;
        
};

#endif


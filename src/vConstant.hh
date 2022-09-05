#pragma once

#ifndef VCONSTANT_HH
#define VCONSTANT_HH

#include "TString.h"
#include <vector>

class vConstant
{
    public:
        double GetMass(TString particleName);
        std::vector<double> GetGutleinConstant(int iso);
        std::vector<double> GetHuberMuellerConstant(int iso);

    private:
        const double mM_e = 0.51099895000; // (15) MeV/c^2
        const double mM_p = 938.27208816; // (29) MeV/c^2
        const double mM_n = 939.56542052; // (54) MeV/c^2
        const double u    = 931.49410242; // (28) MeV/c^2 
        double mDelta = mM_n - mM_p;
        const std::vector<double> mGutleinConstant_U235 = { 1.72254, 10.5200, 896.017, 1054.50, 945.390 };
        const std::vector<double> mGutleinConstant_U238 = { 10.4669, 25.1948, 854.174, 856.805, 864.198 };
        const std::vector<double> mGutleinConstant_Pu239 = { 1.52535, 10.3982, 799.199, 938.927, 842.464 };
        const std::vector<double> mHuberMuellerConstant_U235 = { 4.367, -4.577, 2.100, -0.5294, 0.06186, -0.002777 }; // Huber Data
        const std::vector<double> mHuberMuellerConstant_U238 = { 0.4833, 0.1927, -0.1283, -0.006762, 0.002233, -0.0001536 }; // Mueller Data
        const std::vector<double> mHuberMuellerConstant_Pu239 = { 4.757, -5.392, 2.563, -0.6596, 0.07820, -0.003536 }; // Huber Data
        const std::vector<double> mHuberMuellerConstant_Pu241 = { 2.990, -2.882, 1.278, -0.3343, 0.03905, -0.001754 }; // Huber Data
};
#endif

// Reference
// [1] Particle Data Group, https://pdg.lbl.gov/
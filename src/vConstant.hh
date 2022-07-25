#pragma once

#ifndef VCONSTANT_HH
#define VCONSTANT_HH

#include "TString.h"
#include <vector>

class vConstant
{
    public:
        vConstant();
        ~vConstant();
        double GetMass(TString particleName);
        std::vector<double> GetGutleinConstant(int iso);
        std::vector<double> GetHuberMuellerConstant(int iso);

    private:
        const double mM_e = 0.5109989461;
        const double mM_p = 938.272029;
        const double mM_n = 939.565560;
        double mDelta = mM_n - mM_p;
        const std::vector<double> mGutleinConstant_U235 = { 1.72254, 10.5200, 896.017, 1054.50, 945.390 };
        const std::vector<double> mGutleinConstant_U238 = { 10.4669, 25.1948, 854.174, 856.805, 864.198 };
        const std::vector<double> mGutleinConstant_Pu239 = { 1.52535, 10.3982, 799.199, 938.927, 842.464 };
        const std::vector<double> mHuberMuellerConstant_U235 = {3.217, -3.111, 1.395, -0.3690, 0.04445, -0.002053}; // Mueller Data
        const std::vector<double> mHuberMuellerConstant_U238 = {0.4833, 0.1927, -0.1283, -0.006762, 0.002233, -0.0001536}; // Mueller Data
        // const std::vector<double> mHuberMuellerConstant_Pu239 = {6.413, -7.432, 3.535, -0.8820, 0.1025, -0.004550}; // Muella Data
        // const std::vector<double> mHuberMuellerConstant_Pu241 = {3.251, -3.204, 1.428, -0.3675, 0.04254, -0.001896}; // Muella Data
        const std::vector<double> mHuberMuellerConstant_Pu239 = { 4.367, -5.392, 2.563, -0.6596, 0.07820, -0.003536 }; // Huber Data
        const std::vector<double> mHuberMuellerConstant_Pu241 = { 2.990, -2.882, 1.278, -0.3343, 0.03905, -0.001754 }; // Huber Data
};
#endif
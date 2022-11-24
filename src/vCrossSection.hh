#pragma once

#ifndef VCROSSSECTION_HH
#define VCROSSSECTION_HH

#include "vConstant.hh"
#include "vCR_IBD.hh"


class vCrossSection
{
    public:
        vCrossSection() { mvConstant = new vConstant; }
        ~vCrossSection() { delete mvConstant; }
        // Inverse Beta Decay
        double GetCrossSection_IBD(double E);
        TF1* GetCrossSection_IBD_TF(double startE = 0, double endE = 10);
        double GetCrossSection_IBD_Zeroth(double E);
        double GetDifCrossSection_IBD(double E, double theta);
        TF1* GetDifCrossSection_IBD_TF(double starttheta = 0, double endtheta = TMath::Pi());
        // Nu_e Scattering
        double GetDifCrossSection_ve_Scattering(double E, double T, TString vflavour = "e");
        double GetDifCrossSection_ve_Scattering_Correction(double E, double T, TString vflavour = "e");

    private:
        double GetMomentum_Positron(double E);

        vConstant* mvConstant;
        vCR_IBD mCR_IBD = vCR_IBD();
        vDifCR_IBD mDifCR_IBD = vDifCR_IBD();
};
#endif

// Reference
// [1] P. Vogel, L. Wen and C. Zhang, Neutrino Oscillation Studies with Reactors, Nature Commun. 6 (2015) 6935 [1503.01059].
// [2] J. N. Bahcall, Neutrino-electron scattering and solar neutrino experiments, Reviews of Modern Physics, Vol. 59, No. 2, April 1987
// [3] 't Hooft, G., 1971,Phys. Lett. B 37, 195.


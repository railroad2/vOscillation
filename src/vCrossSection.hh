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
        double GetCrossSection_IBD(double E);
        TF1* GetCrossSection_IBD_TF(double startE = 0, double endE = 10);
        double GetDifferentialCrossSection_IBD(double E, double theta);
        TF1* GetDifferentialCrossSection_IBD_TF(double starttheta = 0, double endtheta = TMath::Pi());

    private:
        double GetMomentum_Positron(double E);

        vConstant* mvConstant;
        vCR_IBD mCR_IBD = vCR_IBD();
        vDifCR_IBD mDifCR_IBD = vDifCR_IBD();
};
#endif

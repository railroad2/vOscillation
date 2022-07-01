#pragma once

#ifndef FLUXCALCULATOR_HH
#define FLUXCALCULATOR_HH

#include <iostream>

#include "../../CGenerator/src/CGenerator.cc"
#include "../src/vOscillating.cc"

#include "TMath.h"
#include "TString.h"


class FluxCalculator{
    public:
        FluxCalculator(){fDelta = fm_n - fm_p;};
        virtual ~FluxCalculator();
        
        double getEnergy_e(double E);
        double getMomentum_e(double E);
        
        double sigma_IBD(double E);
        double integral_Flux_const(CGenerator * gen);
        double integral_sigma_Flux_const(CGenerator * gen);
        double integral_P_Flux(double L, TString beta, CGenerator * gen, vOscillating * vosc);
        double integral_sigma_P_Flux(double L, TString beta, CGenerator * gen, vOscillating * vosc);

        double getm_e(){return fm_e;}
        double getm_n(){return fm_n;}
        double getm_p(){return fm_p;}
        double getDelta(){return fDelta;}
        
        void setint_N(int int_N){fint_N = int_N;}
        void setint_a(int int_a){fint_a = int_a;}
        void setint_b(int int_b){fint_b = int_b;}
        int getint_N(){return fint_N;}
        double getint_a(){return fint_a;}
        double getint_b(){return fint_b;}

    private:
        double fm_e = 0.5109989461;
        double fm_n = 939.565560;
        double fm_p = 938.272029;
        double fDelta;

        int fint_N = 1000;
        double fint_a = 0.1;
        double fint_b = 20000;
};

#endif

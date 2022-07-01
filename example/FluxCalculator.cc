#include <fstream>

#include "FluxCalculator.hh"


double FluxCalculator::getMomentum_e(double E){
    // unit : MeV
    double E_e = E - fDelta;
    if(E_e > fm_e) return TMath::Sqrt(E_e * E_e - fm_e * fm_e);
    else return 0;
}


double FluxCalculator::sigma_IBD(double E){
    // unit : MeV
    double E_e = E - fDelta;
    return 0.0952 * E_e * getMomentum_e(E) * 1e-42;
}


double FluxCalculator::integral_Flux_const(CGenerator * gen){
    // Simpsons Rule
    // unit : keV
    
    int N = fint_N;
    double a = fint_a;
    double b = fint_b;

    double h = (b - a) / N;
    
    double E;
    double F;
    double S = 0;

    for(int i=0; i<=N; i++){
        E = a + h * i;
        F = gen -> CalReactorNeutrinoFlux(E);
        if     (i==0 or i==N) S += F;
        else if(i % 2 == 0)   S += 2 * F;
        else                  S += 4 * F;
    }
    return h * S / 3;
}


double FluxCalculator::integral_sigma_Flux_const(CGenerator * gen){
    // Simpsons Rule
    // unit : keV

    int N = fint_N;
    int a = TMath::Max((fm_n - fm_p + fm_e) * 1000, fint_a);
    int b = fint_b;

    double h = (b - a) / N;
    
    double E;
    double F;
    double sigma;
    double S = 0;

    for (int i=0; i<=N; i++){
        E = a + h * i;
        F = gen -> CalReactorNeutrinoFlux(E);
        sigma = sigma_IBD(E / 1000);
        if     (i==0 or i==N) S += F*sigma;
        else if(i % 2 == 0)   S += 2 * F*sigma;
        else                  S += 4 * F*sigma;
    }
    return h * S / 3;
}


double FluxCalculator::integral_P_Flux(double L, TString beta, CGenerator * gen, vOscillating * vosc){
    // Simpsons Rule
    // unit : keV

    int N = fint_N;
    double a = fint_a;
    double b = fint_b;

    double h = (b - a) / N;

    double E;
    double F;
    double S = 0;

    for(int i=0; i<=N; i++){
        E = a + h * i;
        F = (gen -> CalReactorNeutrinoFlux(E)) * (vosc -> getProbability(L, E / 1000, "e", beta, true));
        if      (i==0 or i==N) S += F;
        else if (i % 2 == 0)   S += 2 * F;
        else                   S += 4 * F;
    }
    return h * S / 3;
}


double FluxCalculator::integral_sigma_P_Flux(double L, TString beta, CGenerator * gen, vOscillating * vosc){
    // Simpsons Ruel
    // unit : keV

    int N = fint_N;
    int a = TMath::Max((fm_n - fm_p + fm_e) * 1000, fint_a);
    int b = fint_b;

    double h = (b - a) / N;
    
    double E;
    double F;
    double sigma;
    double S = 0;

    for (int i=0; i<=N; i++){
        E = a + h * i;
        F = (gen -> CalReactorNeutrinoFlux(E)) * (vosc -> getProbability(L, E / 1000, "e", beta, true));
        sigma = sigma_IBD(E / 1000);
        if     (i==0 or i==N) S += F*sigma;
        else if(i % 2 == 0)   S += 2 * F*sigma;
        else                  S += 4 * F*sigma;
    }
    return h * S / 3;
}

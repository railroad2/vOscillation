#include"../header/vSterileEE.hh"
#include "TMath.h"


vSterileEE::vSterileEE()
{
    fS22t14 = 1.;
    fDm2_41 = 1.;
};
vSterileEE::~vSterileEE() {};


double vSterileEE::GetProbability_SBL(double LoE) const
{
    static double unitconst = 1.2669328;
    double sinValue = TMath::Sin(unitconst * fDm2_41 * LoE);
    return 1. - fS22t14 * sinValue * sinValue;
}

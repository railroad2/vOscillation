#include "vConstant.hh"


vConstant::vConstant() {}
vConstant::~vConstant() {}


double vConstant::GetMass(TString particleName)
{
    if (particleName == "electron" || particleName == "e" || particleName == "Electron") return mM_e;
    else if (particleName == "proton" || particleName == "p" || particleName == "Proton") return mM_p;
    else if (particleName == "neutron" || particleName == "n" || particleName == "Neutron") return mM_n;
    else if (particleName == "Delta") return mDelta;
    else return 0;
}


std::vector<double> vConstant::GetGutleinConstant(int iso)
{
    if (iso == 1) return mGutleinConstant_U235;
    else if (iso == 2) return mGutleinConstant_U238;
    else if (iso == 3) return mGutleinConstant_Pu239;
    else return {};
}


std::vector<double> vConstant::GetHuberMullerConstant(int iso)
{
    if (iso == 1) return mHuberMullerConstant_U235;
    else if (iso == 2) return mHuberMullerConstant_U238;
    else if (iso == 3) return mHuberMullerConstant_Pu239;
    else if (iso == 4) return mHuberMullerConstant_Pu241;
    else return {};
}
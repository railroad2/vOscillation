#include"vSterile.hh"


using namespace std;


vSterile::vSterile()
{
    fS22t14 = 1;
    fDm2_41 = 1;
};
vSterile::~vSterile(){};


double vSterile::GetProbability_SBL_ee(double LoE)
{
    double unitconst = 1.2669328;
    double sinValue = TMath::Sin(unitconst * fDm2_41 * LoE);
    return 1 - fS22t14 * sinValue * sinValue;
}

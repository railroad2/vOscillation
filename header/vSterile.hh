#ifndef VSTERILE_HH
#define VSTERILE_HH


#include "vOscillating.hh"


class vSterile : public vOscillating
{
public:
    vSterile() : vOscillating()
    {
        Set4radian(0, 0, 0);
        Set4Dm2(0);
    }
    ~vSterile() {}

    // Main Method
    double   GetProbability(double L, double E, TString iflavour, TString fflavour, bool anti = false);
    double   GetProbability_Smear(TString iflavour, TString fflavour);
    TComplex GetPMNSmatrix_Truncated(int row, int column);

    // DataLoader (Setter)
    void Load4StdData();

    // Setter
    void Set4theta(double theta_14, double theta_24, double theta_34);
    void Set4radian(double rad_14, double rad_24, double rad_34);
    void Set4Dm2(double Dm2_41);

    //Getter
    std::vector<double> Get4theta() { return { ftheta_14, ftheta_24, ftheta_34 }; }
    std::vector<double> Get4radian() { return { frad_14, frad_24, frad_34 }; }
    std::vector<double> Get4Dm2() { return { fDm2_41, fDm2_42, fDm2_43 }; }


private:
    double ftheta_14 = 0;
    double ftheta_24 = 0;
    double ftheta_34 = 0;
    double frad_14;
    double frad_24;
    double frad_34;
    double fDm2_41;
    double fDm2_42;
    double fDm2_43;

};


#endif
#ifndef VOSCILLATION_HH
#define VOSCILLATION_HH


#include <iostream>
#include <vector>
#include "TString.h"
#include "TComplex.h"


/**
 * This class is for the calculation of the survival probability of neutrino with 3v-Model.
 *
 * If you want to get the survival probability of a certain flavor neutrino, then you can use the "GetProbability" method.
 * 
 * On the 3v-Oscillating model, there are 7 parameters : 3 mixing angles, 3 differences of mass square, and CP-violation phase
 * 
 * "vSterile" class is the child class of this class. See also "vSterile.hh"
 */
class vOscillation
{
public:
    vOscillation();
    virtual ~vOscillation();

    // Main Method
    virtual double GetProbability(double L, double E, TString iflavour, TString fflavour, bool anti = false) const;
    virtual double GetProbability_Smear(TString iflavour, TString fflavour) const;
    TComplex GetPMNSmatrix(int row, int column) const;

    // DataLoader (Setter)
    void LoadStdData(bool IO=false);

    // Setter
    void Settheta(double theta_12 = 33.44, double theta_13 = 8.57, double theta_23 = 49.2);
    void Setradian(double rad_12, double rad_13, double rad_23);
    void SetDm2(double Dm2_21 = 0.0000742, double Dm2_31 = 0.002515);
    void Setdelta_CP(double delta_CP) { fdelta_CP = delta_CP; }

    //Getter
    std::vector<double> Gettheta() const  { return { ftheta_12, ftheta_13, ftheta_23 }; }
    std::vector<double> Getradian() const { return { frad_12, frad_13, frad_23 }; }
    std::vector<double> GetDm2() const    { return { fDm2_21, fDm2_31, fDm2_32 }; }
    double Getdelta_CP() const { return fdelta_CP; }


protected:
    double ftheta_12 = 33.44;   // degree
    double ftheta_13 = 8.57;    // degree
    double ftheta_23 = 49.2;    // degree
    double frad_12;             // radian
    double frad_13;             // radian
    double frad_23;             // radian
    double fDm2_21 = 0.0000753; // eV^2
    double fDm2_31 = 0.0025283; // eV^2
    double fDm2_32;             // eV^2
    double fdelta_CP = 194;     // degree

private:
// Standard Value
// Reference:
// [1] PDG, www.pdg.org
    // Normal Ordering
    constexpr static double PDGNO_sin2_12  = 0.307;
    constexpr static double PDGNO_sin2_13  = 0.0220;
    constexpr static double PDGNO_sin2_23  = 0.546;
    constexpr static double PDGNO_Dm2_21   = 0.0000753;
    constexpr static double PDGNO_Dm2_31   = 0.002453 + 0.0000753;
    constexpr static double PDGNO_Dm2_32   = 0.002453;
    constexpr static double PDGNO_delta_CP = 1.36 * 180;

    // Inverse Ordering
    constexpr static double PDGIO_sin2_12  = 0.307;
    constexpr static double PDGIO_sin2_13  = 0.0220;
    constexpr static double PDGIO_sin2_23  = 0.539;
    constexpr static double PDGIO_Dm2_21   = 0.0000753;
    constexpr static double PDGIO_Dm2_31   = -0.002536 + 0.0000753;
    constexpr static double PDGIO_Dm2_32   = -0.002536;
    constexpr static double PDGIO_delta_CP = 1.36 * 180;
};

#endif


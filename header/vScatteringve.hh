#ifndef VSCATTERINGVE_HH
#define VSCATTERINGVE_HH


class vScatteringve
{
public:
    double GetDifCrossSection(double E, double T, TString vflavour = "e") const;
    double GetDifCrossSection_Correction(double E, double T, TString vflavour = "e") const;
};

#endif
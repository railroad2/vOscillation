#include "vSolarFlux.hh"


double vSolarFlux::GetSolarNeutrinoFlux_NoPeak(double E)
{
    return GetSolarNeutrinoFlux_NoPeak(E, 0);
}


double vSolarFlux::GetSolarNeutrinoFlux_NoPeak(double E, TString src)
{
    if      (src == "pp"  || src == "PP")  return GetSolarNeutrinoFlux_NoPeak(E, 1);
    else if (src == "hep" || src == "HEP") return GetSolarNeutrinoFlux_NoPeak(E, 2);
    else if (src == "B8"  || src == "B")   return GetSolarNeutrinoFlux_NoPeak(E, 3);
    else if (src == "N13" || src == "N")   return GetSolarNeutrinoFlux_NoPeak(E, 4);
    else if (src == "O15" || src == "O")   return GetSolarNeutrinoFlux_NoPeak(E, 5);
    else if (src == "F17" || src == "F")   return GetSolarNeutrinoFlux_NoPeak(E, 6);
    else return 0;
}


double vSolarFlux::GetSolarNeutrinoFlux_NoPeak(double E, int src = 0)
{
    double enu = E * 1000;
    double flux = 0;
    if (src == 0) flux = CalSolNuFlux_Priv_NoPeak(E);
    else if (src > 0) flux = CalSolNuFlux_Priv_NoPeak(E, src-1);
    else flux = CalSolNuFlux_Priv_NoPeak(E);

    double day2Sec = 86400.;
    return flux * day2Sec;
}


double vSolarFlux::GetSolarNeutrinoFlux_PeakEnergy(TString src)
{
    if      (src == "pep"   || src == "PEP")  return GetSolarNeutrinoFlux_PeakEnergy(7);
    else if (src == "Be7_1" || src == "Be_1") return GetSolarNeutrinoFlux_PeakEnergy(8);
    else if (src == "Be7_2" || src == "Be_2") return GetSolarNeutrinoFlux_PeakEnergy(9);
    else return 0;
}


double vSolarFlux::GetSolarNeutrinoFlux_PeakEnergy(int src = 0)
{
    if (src == 6) // pep
    {
        return mE_PEP;
    }
    else if (src == 7) // Be7_firstpeak
    {
        return mE_Be7_1;
    }
    else if (src == 8) // Be7_secondpeak
    {
        return mE_Be7_2;
    }
    else
    {
        return 0;
    }
}


double vSolarFlux::GetSolarNeutrinoFlux_PeakFlux(TString src)
{
    if      (src == "pep"   || src == "PEP")  return GetSolarNeutrinoFlux_PeakFlux(7);
    else if (src == "Be7_1" || src == "Be_1") return GetSolarNeutrinoFlux_PeakFlux(8);
    else if (src == "Be7_2" || src == "Be_2") return GetSolarNeutrinoFlux_PeakFlux(9);
    else return 0;
}


double vSolarFlux::GetSolarNeutrinoFlux_PeakFlux(int src = 0)
{
    double flux = 0;
    if (src == 6) // pep
    {
        flux =  1.41E+8; // /cm^2/sec
    }
    else if (src == 7) // Be7_firstpeak
    {
        flux = 4.84E+9 * 0.103; // /cm^2/sec
    }
    else if (src == 8) // Be7_secondpeak
    {
        flux = 4.84E+9 * 0.897; // /cm^2/sec
    }
    return flux * 86400.;
}


TF1* vSolarFlux::GetTF_SolarNeutrinoFlux_NoPeak(TString src, double startE = 1.5, double endE = 9)
{
    if      (src == "pp"  || src == "PP")  return GetTF_SolarNeutrinoFlux_NoPeak(1, startE, endE);
    else if (src == "hep" || src == "HEP") return GetTF_SolarNeutrinoFlux_NoPeak(2, startE, endE);
    else if (src == "B8"  || src == "B")   return GetTF_SolarNeutrinoFlux_NoPeak(3, startE, endE);
    else if (src == "N13" || src == "N")   return GetTF_SolarNeutrinoFlux_NoPeak(4, startE, endE);
    else if (src == "O15" || src == "O")   return GetTF_SolarNeutrinoFlux_NoPeak(5, startE, endE);
    else if (src == "F17" || src == "F")   return GetTF_SolarNeutrinoFlux_NoPeak(6, startE, endE);
    else return 0;
}


TF1* vSolarFlux::GetTF_SolarNeutrinoFlux_NoPeak(int src = 0, double startE = 1.5, double endE = 9)
{
    vSolarFlux* vcf = new vSolarFlux();
    vSL_TF* SL_TF = new vSL_TF(vcf);
    TF1* f = new TF1("flux", SL_TF, startE, endE, 1);
    f->SetParameter(0, src);
    return f;
}


double vSolarFlux::CalSolNuFlux_Priv_NoPeak(double E)
{
    double totflux = 0;
    for (int i = 0; i < mNumSrcNoPeak; i++)
    {
        totflux += CalSolNuFlux_Priv_NoPeak(E, i);
    }

    if (totflux < 0) return 0;
    else return totflux;
}


double vSolarFlux::CalSolNuFlux_Priv_NoPeak(double E, int src)
{
    const int numSrcNoPeak = 6;

    double preflux[numSrcNoPeak] = { 5.54E+10, 7.88E+03, 5.74E+06, 5.70E+08, 4.98E+08, 5.87E+06 };
    double emax[numSrcNoPeak] = { 0.428, 18.790, 14.880, 1.201, 1.733, 1.740 }; // MeV
    double par[numSrcNoPeak][9]
        = { -2.87034E-01, 1.63559E+02, -1.22253E+03,  1.55085E+04, -1.465140E+05,  7.843750E+05, -2.35724E+06,  3.71082E+06, -2.38308E+06,
            -2.04975E-06, 4.22577E-03, -4.70817E-04,  2.55332E-05, -2.817140E-06,  3.069610E-07, -1.87479E-08,  6.01396E-10, -7.88874E-12,
             6.01473E-04, 1.49699E-02, -2.64810E-03, -2.41410E-05,  6.223250E-05, -9.843290E-06,  7.51311E-07, -2.86060E-08,  4.31573E-10,
            -2.59522E-02, 1.05228E+01, -3.23440E+01,  1.33211E+02, -4.118480E+02,  7.284050E+02, -7.26105E+02,  3.81370E+02, -8.21149E+01,
            -1.36811E-02, 3.94221E+00, -8.55431E+00,  2.36712E+01, -5.004770E+01,  6.075420E+01, -4.15278E+01,  1.49462E+01, -2.20367E+00,
            -6.74473E-02, 4.63141E+00, -1.15350E+01,  2.85067E+01, -5.116640E+01,  5.511020E+01, -3.45332E+01,  1.16550E+01, -1.63814E+00 };
    
    double normSolar[mNumSrcNoPeak];
    for (int i = 0; i < mNumSrcNoPeak; i++)
    {
        normSolar[i] = 0;
        for (int j = 0; j < 9; j++)
        {
            normSolar[i] += 1. / (j + 2) * par[i][j] * TMath::Power(emax[i], j + 2);
        }
        normSolar[i] /= preflux[i];
    }

    if (E >= emax[src]) return 0;

    double flux = 0;
    for (int i = 0; i < 9; i++)
    {
        flux += par[src][i] * TMath::Power(E, i + 1) / normSolar[src];
    }
    if (flux < 0) return 0;
    else return flux;
}
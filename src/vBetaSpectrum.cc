#include "../header/vBetaSpectrum.hh"
#include "../header/vConstant.hh"


void vBetaSpectrum::PrintInfo()
{
	cout << "<vEnergySpectrum->vNeutrinoSpectrum->vBetaSpectrum>" << endl;
	cout << "    Activity (unit : user defined) : " << fActivity << endl;
}


double vBetaSpectrum::GetCurrent(double E)
{
	double Spectrum = 0;

	for (int i = 0; i < fVectorSize; i++)
	{
		double qValue = fQValue[i];
		double Z_f = fZdaughter[i];
		double cont = fContribution[i];
		double norm = fNormalization[i];
		Spectrum += cont * GetBetaSpectrum(qValue - E, qValue, Z_f, norm);
	}

	return fActivity * Spectrum;
}


double vBetaSpectrum::GetBetaSpectrum(double T, double Q, double Z_f, double normalization)
{
	double E_0 = MASSDELTA;
	double m_e = MASSELECTRON;
	double E_e = (T + m_e);
	double fsc = 7.29735e-3;
	double p = TMath::Sqrt(E_e * E_e - m_e * m_e);
	if (Q < T) return 0;
	double S_0 = p * E_e * (Q - T) * (Q - T);
	double eta = Z_f * fsc * E_e / p;
	double F = 2 * TMath::Pi() * eta / (1 - TMath::Exp(-2 * TMath::Pi() * eta));

	if (p == 0) return 2 * TMath::Pi() * Z_f * fsc * m_e * m_e * Q * Q / normalization;
	if (p < 0) return 0;
	if (F * S_0 > 0) return F * S_0 / normalization;
	else return 0;
}
// Detected Solar Flux + Resolution + C12, C14 background
#include "../vClass.hh"

vBetaSpectrum* vbs = new vBetaSpectrum();

double BetaSpectrum_C11(double T)
{
	// -BetaSpectrum(-Z_f) -> beta+ decay
	return - vbs->GetBetaSpectrum(T, 0.960, -5., 0.1099013900669717);
}


double BetaSpectrum_C14(double T)
{
	return vbs->GetBetaSpectrum(T, 0.1565, 7., 0.0002089169740292279);
}


double BetaSpectrum_C11_Resolution(double Tdet, double resolution, double endE)
{
	double result = 0;

	int N = 100;
	double a = 0.000001;
	double b = endE;
	double h = (b - a) / (double)N / 2.;

	double T;
	double integrand;
	double sigma;
	for (int i = 0; i <= 2 * N; i++)
	{
		T = a + h * (double)i;
		sigma = resolution / 100. * TMath::Sqrt(T);
		integrand = BetaSpectrum_C11(T - 2 * MASSELECTRON) * TMath::Gaus(Tdet - T, 0, sigma, kTRUE);
		if (i == 0 or i == 2 * N) result += integrand;
		else if (i % 2 == 0)      result += 2. * integrand;
		else                      result += 4. * integrand;
	}

	return h * result / 3.;
}


double integral_dcs_spectrum(double T, int N, double a, double b, vOscillating* vosc, vScatteringve* vcs, vSolarFlux* vsf, int iso)
{
	// integral ds/dT * flux from a to b with stepsize (b-a) / 2N

	double h = (b - a) / 2. / (double)N;

	double P_ee = vosc->GetProbability_Smear("e", "e");
	double P_em = 1 - P_ee;

	double E, dcs, spectrum;
	double resultIntegral = 0.;
	for (int i = 0; i <= 2 * N; i++)
	{
		E = a + h * (double)i;
		dcs = vcs->GetDifCrossSection_Correction(E, T, "e") * P_ee + vcs->GetDifCrossSection_Correction(E, T, "mu") * P_em; // cm^2 / MeV
		spectrum = vsf->GetSolarNeutrinoFlux_NoPeak(E, iso);         // / cm^2 / keV / day
		if (i == 0 or i == 2 * N) resultIntegral += dcs * spectrum;
		else if (i % 2 == 0)      resultIntegral += 2. * dcs * spectrum;
		else                      resultIntegral += 4. * dcs * spectrum; // / MeV^2 / day
	}
	return h * resultIntegral / 3; // / MeV / day
}


void PlotFullSolar()
{
	// 100keV ~ 2600keV, 2501 point

	gStyle->SetOptStat(kFALSE);

	double electronNumberDensity = 2.89673e23; // #/ml
	double LSgram = 1.e8; // g, 2e9 : 2kT
	double LSdensity = 0.860; // g/ml
	double LSVolume = LSgram / LSdensity; // ml
	double totElectronNumber = LSVolume * electronNumberDensity;

	double rate_PC = 1.94;
	double rate_PXE = 9.1;
	double rate_PCDodecane = 3.84;
	double rate_LABs = 24.8;

	double rateC14C12 = 1.e-18 * rate_LABs;

	double halfLife = 5730 * 365.2425; // halflife of C14, day
	double betaRate = TMath::Log(2) / halfLife; // #/day/C14

	double numberDensityC12 = 3.7855e22; // #/ml
	double totNumberC12 = numberDensityC12 * LSVolume;
	double totNumberC14 = totNumberC12 * rateC14C12;
	double totBetaRate = betaRate * totNumberC14;

	// double totBetaRateC11 = 107. * totNumberC12 / 4.31e30; // #/day, KamLAND=LSC : 107, 
	double totBetaRateC11 = 28.5; // #/day, Borexino : 14.55;
	cout << "totBetaRateC11 : " << totBetaRateC11 << endl;

	vOscillating* vosc = new vOscillating();
	vScatteringve* vcs = new vScatteringve();
	vSolarFlux* vsf = new vSolarFlux();

	double m_e = MASSELECTRON;

	double P_ee = vosc->GetProbability_Smear("e", "e");
	double P_em = 1 - P_ee;

	TGraph* gPP = new TGraph();
	TGraph* gHEP = new TGraph();
	TGraph* gBe7 = new TGraph();
	TGraph* gCNO = new TGraph();
	TGraph* gPEP = new TGraph();
	TGraph* gB8 = new TGraph();
	TGraph* gC14 = new TGraph();
	TGraph* gC11 = new TGraph();

	gPP->SetName("PP");
	gHEP->SetName("HEP");
	gBe7->SetName("Be7");
	gCNO->SetName("CNO");
	gPEP->SetName("PEP");
	gB8->SetName("B8");
	gC14->SetName("C14");
	gC11->SetName("C11");

	double fPEP_Enu = 1.442;
	double fBe7_Enu1 = .385;
	double fBe7_Enu2 = .862;
	double fPEP_Flux = 86400. * 1.41e08;
	double fBe7_Flux1 = 86400. * 4.84e+09 * 0.103;
	double fBe7_Flux2 = 86400. * 4.84e+09 * 0.897;

	int N = 100;
	double a = 0.000001;
	double b;
	double T;
	double dcs;
	double flux_PP, flux_HEP, flux_Be7, flux_N13, flux_O15, flux_F17, flux_PEP, flux_B8, flux_C14, flux_C11;
	double dcs_PEP, dcs_Be7_1, dcs_Be7_2;
	for (int i = 0; i <= 2500; i++)
	{
		T = (double)i * 0.001 + 0.1;

		b = 0.428;
		flux_PP = totElectronNumber * integral_dcs_spectrum(T, N, a, b, vosc, vcs, vsf, 1);
		b = 18.790;
		flux_HEP = totElectronNumber * integral_dcs_spectrum(T, N, a, b, vosc, vcs, vsf, 2);
		b = 14.880;
		flux_B8 = totElectronNumber * integral_dcs_spectrum(T, N, a, b, vosc, vcs, vsf, 3);
		b = 1.201;
		flux_N13 = totElectronNumber * integral_dcs_spectrum(T, N, a, b, vosc, vcs, vsf, 4);
		b = 1.733;
		flux_O15 = totElectronNumber * integral_dcs_spectrum(T, N, a, b, vosc, vcs, vsf, 5);
		b = 1.740;
		flux_F17 = totElectronNumber * integral_dcs_spectrum(T, N, a, b, vosc, vcs, vsf, 6);

		flux_C14 = totBetaRate * BetaSpectrum_C14(T);
		flux_C11 = totBetaRateC11 * BetaSpectrum_C11_Resolution(T, 5., 2.5);

		dcs_PEP = vcs->GetDifCrossSection_Correction(fPEP_Enu, T, "e") * P_ee + vcs->GetDifCrossSection_Correction(fPEP_Enu, T, "mu") * P_em;
		dcs_Be7_1 = vcs->GetDifCrossSection_Correction(fBe7_Enu1, T, "e") * P_ee + vcs->GetDifCrossSection_Correction(fBe7_Enu1, T, "mu") * P_em;
		dcs_Be7_2 = vcs->GetDifCrossSection_Correction(fBe7_Enu2, T, "e") * P_ee + vcs->GetDifCrossSection_Correction(fBe7_Enu2, T, "mu") * P_em;

		flux_PEP = totElectronNumber * fPEP_Flux * dcs_PEP;
		flux_Be7 = totElectronNumber * (fBe7_Flux1 * dcs_Be7_1 + fBe7_Flux2 * dcs_Be7_2);

		gPP->SetPoint(i, T, flux_PP / 1000.);
		gHEP->SetPoint(i, T, flux_HEP / 1000.);
		gB8->SetPoint(i, T, flux_B8 / 1000.);
		gCNO->SetPoint(i, T, (flux_N13 + flux_O15 + flux_F17) / 1000.);
		gPEP->SetPoint(i, T, flux_PEP / 1000.);
		gBe7->SetPoint(i, T, flux_Be7 / 1000.);

		gC14->SetPoint(i, T, flux_C14 / 1000.);
		gC11->SetPoint(i, T, flux_C11 / 1000.);
	}



	TCanvas* can1 = new TCanvas("SolarFlux", "SolarFlux", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame = new TH1D("hFrame", "", 100, 0.1, 2.6);
	hFrame->GetXaxis()->SetTitle("Electron Kinetic Energy(MeV)");
	hFrame->GetYaxis()->SetTitle("Detected Neutrino Spectrum (# / day / keV / 100 tons)");
	gPad->SetLogy();
	hFrame->GetYaxis()->SetRangeUser(1e-5, 1);
	hFrame->Draw();

	gPP->SetLineColor(2);
	gPP->Draw("SAMEl");
	gHEP->SetLineColor(2);
	gHEP->Draw("SAMEl");
	gB8->SetLineColor(2);
	gB8->Draw("SAMEl");
	gCNO->SetLineColor(2);
	gCNO->Draw("SAMEl");
	gPEP->SetLineColor(2);
	gPEP->Draw("SAMEl");
	gBe7->SetLineColor(2);
	gBe7->Draw("SAMEl");

	gC14->SetLineColor(14);
	gC14->Draw("SAMEl");
	gC11->SetLineColor(8);
	gC11->Draw("SAMEl");

	TLatex* latPP = new TLatex(0.25, 1100, "pp");
	latPP->SetTextColor(2);
	latPP->SetTextSize(0.03);
	latPP->SetTextFont(42);
	latPP->Draw("SAME");

	//TLatex* latHEP = new TLatex(0.25, 1100, "hep");
	//latHEP->SetTextColor(2);
	//latHEP->SetTextSize(0.03);
	//latHEP->SetTextFont(42);
	//latHEP->Draw("SAME");

	TLatex* latB8 = new TLatex(0.25, 1100, "B8");
	latB8->SetTextColor(2);
	latB8->SetTextSize(0.03);
	latB8->SetTextFont(42);
	latB8->Draw("SAME");

	TLatex* latCNO = new TLatex(0.25, 1100, "CNO");
	latCNO->SetTextColor(2);
	latCNO->SetTextSize(0.03);
	latCNO->SetTextFont(42);
	latCNO->Draw("SAME");

	TLatex* latPEP = new TLatex(0.25, 1100, "pep");
	latPEP->SetTextColor(2);
	latPEP->SetTextSize(0.03);
	latPEP->SetTextFont(42);
	latPEP->Draw("SAME");

	TLatex* latBe7 = new TLatex(0.25, 1100, "Be7");
	latBe7->SetTextColor(2);
	latBe7->SetTextSize(0.03);
	latBe7->SetTextFont(42);
	latBe7->Draw("SAME");

	TLatex* latC14 = new TLatex(0.25, 1100, "C14");
	latC14->SetTextColor(14);
	latC14->SetTextSize(0.03);
	latC14->SetTextFont(42);
	latC14->Draw("SAME");

}

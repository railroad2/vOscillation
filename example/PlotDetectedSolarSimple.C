// Detected Solar Flux (no resolution, no background)
#include "../vClass.hh"


double integral_dcs_spectrum(double T, int N, double a, double b, vScatteringve* vcs, vSolarFlux* vsf, int iso, TString vflavour)
{
	double h = (b - a) / 2. / (double)N;

	double E, dcs, spectrum;
	double resultIntegral = 0.;
	for (int i = 0; i <= 2 * N; i++)
	{
		E = a + h * (double)i;
		dcs = vcs->GetDifCrossSection_Correction(E, T, vflavour); // cm^2 / MeV
		spectrum = vsf->GetSolarNeutrinoFlux_NoPeak(E, iso);         // / cm^2 / keV / day
		if (i == 0 or i == 2 * N) resultIntegral += dcs * spectrum;
		else if (i % 2 == 0)      resultIntegral += 2. * dcs * spectrum;
		else                      resultIntegral += 4. * dcs * spectrum; // / MeV^2 / day
	}
	return h * resultIntegral / 3; // / MeV / day
}


void PlotDetectedSolarSimple()
{
	gStyle->SetOptStat(kFALSE);
	vOscillation* vosc = new vOscillation();
	vScatteringve* vcs = new vScatteringve();
	vSolarFlux* vsf = new vSolarFlux();

	TGraph* gSolar_pp  = new TGraph(); // 1
	TGraph* gSolar_hep = new TGraph(); // 2
	TGraph* gSolar_B8  = new TGraph(); // 3
	TGraph* gSolar_N13 = new TGraph(); // 4
	TGraph* gSolar_O15 = new TGraph(); // 5
	TGraph* gSolar_F17 = new TGraph(); // 6
	TGraph* gSolar_pep = new TGraph(); // 7
	TGraph* gSolar_Be7 = new TGraph(); // 8

	// "Smear" : All of sin(L/E) terms become 1/2.
	double P_ee = vosc->GetProbability_Smear("e", "e");
	double P_em = 1 - P_ee; // P(ve->vm) + P(ve->vt)

	double gN = 1000.; // the number of point of each graph
	double ga = 0.01; // energy min in plot
	double gb = 1;

	double a, b, T, F, E;
	a = 0; // energy min in integral
	int iso;
	int N = 100; // integral parameter (how exact the integration be)

	iso = 1;
	b = 0.428; // energy max in integral
	gb = b; // energy max in plot
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);
		F = integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "e") * P_ee;
		F += integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "mu") * P_em;
		gSolar_pp->SetPoint(i, T, F);
	}

	iso = 2;
	b = 18.790;
	gb = b;
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);
		F = integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "e") * P_ee;
		F += integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "mu") * P_em;
		gSolar_hep->SetPoint(i, T, F);
	}

	iso = 3;
	b = 14.880;
	gb = b;
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);
		F = integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "e") * P_ee;
		F += integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "mu") * P_em;
		gSolar_B8->SetPoint(i, T, F);
	}

	iso = 4;
	b = 1.201;
	gb = b;
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);
		F = integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "e") * P_ee;
		F += integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "mu") * P_em;
		gSolar_N13->SetPoint(i, T, F);
	}

	iso = 5;
	b = 1.733;
	gb = b;
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);
		F = integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "e") * P_ee;
		F += integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "mu") * P_em;
		gSolar_O15->SetPoint(i, T, F);
	}

	iso = 6;
	b = 1.740;
	gb = b;
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);
		F = integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "e") * P_ee;
		F += integral_dcs_spectrum(T, N, a, b, vcs, vsf, iso, "mu") * P_em;
		gSolar_F17->SetPoint(i, T, F);
	}

	gb = 20;
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);
		E = vsf->GetSolarNeutrinoFlux_PeakEnergy(7);
		F = vcs->GetDifCrossSection_Correction(E, T, "e") * P_ee;
		F += vcs->GetDifCrossSection_Correction(E, T, "mu") * P_em;
		F *= vsf->GetSolarNeutrinoFlux_PeakFlux(7);
		gSolar_pep->SetPoint(i, T, F);
	}

	gb = 20;
	for (int i = 0; i < gN; i++)
	{
		T = TMath::Exp(TMath::Log(ga) + (TMath::Log(gb) - TMath::Log(ga)) * (double)i / gN);

		E = vsf->GetSolarNeutrinoFlux_PeakEnergy(8);
		double F1 = vsf->GetSolarNeutrinoFlux_PeakFlux(8) * vcs->GetDifCrossSection_Correction(E, T, "e") * P_ee;
		F1 += vsf->GetSolarNeutrinoFlux_PeakFlux(8) * vcs->GetDifCrossSection_Correction(E, T, "mu") * P_em;

		E = vsf->GetSolarNeutrinoFlux_PeakEnergy(9);
		double F2 = vsf->GetSolarNeutrinoFlux_PeakFlux(9) * vcs->GetDifCrossSection_Correction(E, T, "e") * P_ee;
		F2 += vsf->GetSolarNeutrinoFlux_PeakFlux(9) * vcs->GetDifCrossSection_Correction(E, T, "mu") * P_em;

		gSolar_Be7->SetPoint(i, T, F1 + F2);
	}


	TCanvas* can1 = new TCanvas("DetectedSolarFlux", "DetectedSolarFlux", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame = new TH1D("hFrame", "", 100, 0.01, 20);
	hFrame->GetXaxis()->SetTitle("Electron Kinetic Energy (MeV)");
	hFrame->GetYaxis()->SetTitle("Detected Solar Flux (/day/MeV/electron)");
	gPad->SetLogx(1);
	gPad->SetLogy(1);
	hFrame->GetYaxis()->SetRangeUser(1e-37, 1e-28);
	hFrame->Draw();

	gSolar_pp->SetLineColor(1);
	gSolar_pp->SetName("pp");
	gSolar_pp->Draw("SAMEl");
	gSolar_hep->SetLineColor(2);
	gSolar_hep->SetName("hep");
	gSolar_hep->Draw("SAMEl");
	gSolar_B8->SetLineColor(3);
	gSolar_B8->SetName("B8");
	gSolar_B8->Draw("SAMEl");
	gSolar_N13->SetLineColor(4);
	gSolar_N13->SetName("N13");
	gSolar_N13->Draw("SAMEl");
	gSolar_O15->SetLineColor(5);
	gSolar_O15->SetName("O15");
	gSolar_O15->Draw("SAMEl");
	gSolar_F17->SetLineColor(6);
	gSolar_F17->SetName("F17");
	gSolar_F17->Draw("SAMEl");
	gSolar_pep->SetLineColor(7);
	gSolar_pep->SetName("pep");
	gSolar_pep->Draw("SAMEl");
	gSolar_Be7->SetLineColor(8);
	gSolar_Be7->SetName("Be7");
	gSolar_Be7->Draw("SAMEl");

	TLegend* leg1 = new TLegend();
	leg1->AddEntry("pp", "pp", "l");
	leg1->AddEntry("hep", "hep", "l");
	leg1->AddEntry("B8", "B8", "l");
	leg1->AddEntry("N13", "N13", "l");
	leg1->AddEntry("O15", "O15", "l");
	leg1->AddEntry("F17", "F17", "l");
	leg1->AddEntry("pep", "pep", "l");
	leg1->AddEntry("Be7", "Be7", "l");
	leg1->Draw();

}

#include "../vClass.hh"


void PlotReactorFlux()
{
	gStyle->SetOptStat(kFALSE);

	double thermalPower = 36;

	vReactorSpectrum* vrf = new vReactorSpectrum("HuberMueller");
	vrf->SetThermalPower(thermalPower);


	double Emin = 1.5;
	double Emax = 10;
	int gN = 1000;

	TGraph* gRF = new TGraph();
	for (int i = 0; i < gN; i++)
	{
		double E = Emin + (Emax - Emin) * (double)i / (double)(gN - 1);

		gRF->SetPoint(i, E, vrf->GetCurrent(E)); 
	}

	// How many neutrinos are producted at the reactor?

	TCanvas* can1 = new TCanvas("ReactorFlux", "ReactorFlux", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame1 = new TH1D("hFrame1", "", 100, 0, Emax);
	hFrame1->GetXaxis()->SetTitle("Neutrino Energy (MeV)");
	hFrame1->GetYaxis()->SetTitle("Current(/MeV/day)");
	hFrame1->GetYaxis()->SetRangeUser(0, 2e26);
	hFrame1->Draw();
	gRF->Draw("SAMEl");

}
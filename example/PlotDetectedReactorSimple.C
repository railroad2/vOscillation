#include "../vClass.hh"


void PlotDetectedReactorSimple()
{
	gStyle->SetOptStat(kFALSE);

	double thermalPower = 36;

	vReactorSpectrum* vrf = new vReactorSpectrum("HuberMueller");
	vrf->SetThermalPower(thermalPower);

	double Emin = 1.5;
	double Emax = 10.;
	vEnergySpectrum* ves = new vEnergySpectrum(vrf, Emin, Emax);

	double distance = 60000.; // m
	distance *= 100.; // m -> cm

	TF1* tfEnergy = new TF1("tfEnergy", ves, Emin, Emax, 0);
	tfEnergy->SetNpx(500);

	int gN = 1000;
	TGraph* gRF = new TGraph();
	for (int i = 0; i < gN; i++)
	{
		double E = Emin + (Emax - Emin) * (double)i / (double)(gN - 1);

		gRF->SetPoint(i, E, tfEnergy->Eval(E)/4./TMath::Pi()/distance/distance);
	}

	// How many neutrinos are detected per proton in the detector?

	TCanvas* can1 = new TCanvas("ReactorFlux", "ReactorFlux", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame1 = new TH1D("hFrame1", "", 100, 0, Emax);
	hFrame1->GetXaxis()->SetTitle("Neutrino Energy (MeV)");
	hFrame1->GetYaxis()->SetTitle("Detected Number(/MeV/day/proton)");
	hFrame1->GetYaxis()->SetRangeUser(0, 4.e-32);
	hFrame1->Draw();
	gRF->Draw("SAMEl");
}
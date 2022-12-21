#include "../vClass.hh"

void PlotIBD()
{
	vIBD* vibd = new vIBD();

	TGraph* gCS = new TGraph();
	TGraph* gDCS_3 = new TGraph();
	TGraph* gDCS_5 = new TGraph();

	double Emin = 0;
	double Emax = 8;
	double Thetamin = 0;
	double Thetamax = TMath::Pi();
	int gN = 1000;

	for (int i = 0; i < gN; i++)
	{
		double E = Emin + (Emax - Emin) * (double)i / (double)(gN - 1);
		double theta = Thetamin + (Thetamax - Thetamin) * (double)i / (double)(gN - 1);

		gCS->SetPoint(i, E, vibd->GetCrossSection(E));
		gDCS_3->SetPoint(i, theta, vibd->GetDifCrossSection(3., theta));
		gDCS_5->SetPoint(i, theta, vibd->GetDifCrossSection(5., theta));
	}

	TCanvas* can1 = new TCanvas("CrossSection", "CrossSection", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame1 = new TH1D("hFrame1", "", 100, Emin, Emax);
	hFrame1->GetXaxis()->SetTitle("Neutrino Energy (MeV)");
	hFrame1->GetYaxis()->SetTitle("Cross Section (cm^2)");
	hFrame1->GetYaxis()->SetRangeUser(0, 4.e-42);
	hFrame1->Draw();
	gCS->Draw("SAMEl");


	TCanvas* can2 = new TCanvas("Differential CrossSection", "Differential CrossSection", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame2 = new TH1D("hFrame2", "", 100, Thetamin, Thetamax);
	hFrame2->GetXaxis()->SetTitle("Recoiled Angle of Positron (radian)");
	hFrame2->GetYaxis()->SetTitle("Differential Cross Section (cm^2)");
	hFrame2->GetYaxis()->SetRangeUser(0, 1.5e-43);
	hFrame2->Draw();
	gDCS_3->SetLineColor(2);
	gDCS_3->Draw("SAMEl");
	gDCS_5->SetLineColor(3);
	gDCS_5->Draw("SAMEl");
}
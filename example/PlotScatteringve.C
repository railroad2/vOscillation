#include "../vClass.hh"

void PlotScatteringve()
{
	gStyle->SetOptStat(kFALSE);

	vScatteringve* vsc = new vScatteringve();
	TGraph* gdsdT_E_1_e = new TGraph();
	TGraph* gdsdT_E_1_m = new TGraph();
	TGraph* gdsdT_E_2_e = new TGraph();
	TGraph* gdsdT_E_2_m = new TGraph();
	TGraph* gdsdT_E_3_e = new TGraph();
	TGraph* gdsdT_E_3_m = new TGraph();
	gdsdT_E_1_e->SetName("#nu_{e} - e^{-}, T = 0.1 MeV");
	gdsdT_E_1_m->SetName("#nu_{#mu} - e^{-}, T = 0.1 MeV");
	gdsdT_E_2_e->SetName("#nu_{e} - e^{-}, T = 0.2 MeV");
	gdsdT_E_2_m->SetName("#nu_{#mu} - e^{-}, T = 0.2 MeV");
	gdsdT_E_3_e->SetName("#nu_{e} - e^{-}, T = 0.3 MeV");
	gdsdT_E_3_m->SetName("#nu_{#mu} - e^{-}, T = 0.3 MeV");

	TGraph* gdsdT_T_1_e = new TGraph();
	TGraph* gdsdT_T_1_m = new TGraph();
	TGraph* gdsdT_T_2_e = new TGraph();
	TGraph* gdsdT_T_2_m = new TGraph();
	TGraph* gdsdT_T_3_e = new TGraph();
	TGraph* gdsdT_T_3_m = new TGraph();
	gdsdT_T_1_e->SetName("#nu_{e} - e^{-}, E = 0.1 MeV");
	gdsdT_T_1_m->SetName("#nu_{#mu} - e^{-}, E = 0.1 MeV");
	gdsdT_T_2_e->SetName("#nu_{e} - e^{-}, E = 0.2 MeV");
	gdsdT_T_2_m->SetName("#nu_{#mu} - e^{-}, E = 0.2 MeV");
	gdsdT_T_3_e->SetName("#nu_{e} - e^{-}, E = 0.3 MeV");
	gdsdT_T_3_m->SetName("#nu_{#mu} - e^{-}, E = 0.3 MeV");


	double gN = 1000.;
	double a = 0.00001;
	double b = 1;
	
	double E, T, F;
	for (int i = 0; i < gN; i++)
	{
		E = a + (b - a) * (double)i / gN;
		gdsdT_E_1_e->SetPoint(i, E, vsc->GetDifCrossSection_Correction(E, .1, "e"));
		gdsdT_E_2_e->SetPoint(i, E, vsc->GetDifCrossSection_Correction(E, .2, "e"));
		gdsdT_E_3_e->SetPoint(i, E, vsc->GetDifCrossSection_Correction(E, .3, "e"));
		gdsdT_E_1_m->SetPoint(i, E, vsc->GetDifCrossSection_Correction(E, .1, "mu"));
		gdsdT_E_2_m->SetPoint(i, E, vsc->GetDifCrossSection_Correction(E, .2, "mu"));
		gdsdT_E_3_m->SetPoint(i, E, vsc->GetDifCrossSection_Correction(E, .3, "mu"));
	}

	b = 0.3;
	for (int i = 0; i < gN; i++)
	{
		T = a + (b - a) * (double)i / gN;
		gdsdT_T_1_e->SetPoint(i, T, vsc->GetDifCrossSection_Correction(.1, T, "e"));
		gdsdT_T_2_e->SetPoint(i, T, vsc->GetDifCrossSection_Correction(.2, T, "e"));
		gdsdT_T_3_e->SetPoint(i, T, vsc->GetDifCrossSection_Correction(.3, T, "e"));
		gdsdT_T_1_m->SetPoint(i, T, vsc->GetDifCrossSection_Correction(.1, T, "mu"));
		gdsdT_T_2_m->SetPoint(i, T, vsc->GetDifCrossSection_Correction(.2, T, "mu"));
		gdsdT_T_3_m->SetPoint(i, T, vsc->GetDifCrossSection_Correction(.3, T, "mu"));
	}


	TCanvas* can1 = new TCanvas("dsdT_E", "dsdT_E", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame1 = new TH1D("hFrame1", "", 100, 0, 1);
	hFrame1->GetXaxis()->SetTitle("Neutrino Energy (MeV)");
	hFrame1->GetYaxis()->SetTitle("Differential Cross Section (cm^2 / MeV)");
	hFrame1->GetXaxis()->SetTitleSize(0.047);
	hFrame1->GetYaxis()->SetTitleSize(0.047);
	hFrame1->GetXaxis()->SetTitleOffset(1.1);
	hFrame1->GetYaxis()->SetTitleOffset(1.1);
	hFrame1->GetXaxis()->CenterTitle();
	hFrame1->GetYaxis()->CenterTitle();
	hFrame1->GetXaxis()->SetLabelSize(0.038);
	hFrame1->GetYaxis()->SetLabelSize(0.038);
	hFrame1->GetYaxis()->SetNdivisions(505);
	hFrame1->GetYaxis()->SetRangeUser(0, 12e-45);
	hFrame1->Draw();

	gdsdT_E_1_e->SetLineColor(1);
	gdsdT_E_1_e->Draw("SAMEl");
	gdsdT_E_2_e->SetLineColor(2);
	gdsdT_E_2_e->Draw("SAMEl");
	gdsdT_E_3_e->SetLineColor(3);
	gdsdT_E_3_e->Draw("SAMEl");
	gdsdT_E_1_m->SetLineColor(1);
	gdsdT_E_1_m->SetLineStyle(7);
	gdsdT_E_1_m->Draw("SAMEl");
	gdsdT_E_2_m->SetLineColor(2);
	gdsdT_E_2_m->SetLineStyle(7);
	gdsdT_E_2_m->Draw("SAMEl");
	gdsdT_E_3_m->SetLineColor(3);
	gdsdT_E_3_m->SetLineStyle(7);
	gdsdT_E_3_m->Draw("SAMEl");

	TLegend* leg1 = new TLegend();
	leg1->AddEntry("#nu_{e} - e^{-}, T = 0.1 MeV", "#nu_{e} - e^{-}, T = 0.1 MeV", "l");
	leg1->AddEntry("#nu_{#mu} - e^{-}, T = 0.1 MeV", "#nu_{#mu} - e^{-}, T = 0.1 MeV", "l");
	leg1->AddEntry("#nu_{e} - e^{-}, T = 0.2 MeV", "#nu_{e} - e^{-}, T = 0.2 MeV", "l");
	leg1->AddEntry("#nu_{#mu} - e^{-}, T = 0.2 MeV", "#nu_{#mu} - e^{-}, T = 0.2 MeV", "l");
	leg1->AddEntry("#nu_{e} - e^{-}, T = 0.3 MeV", "#nu_{e} - e^{-}, T = 0.3 MeV", "l");
	leg1->AddEntry("#nu_{#mu} - e^{-}, T = 0.3 MeV", "#nu_{#mu} - e^{-}, T = 0.3 MeV", "l");
	leg1->Draw();




	TCanvas* can2 = new TCanvas("dsdT_T", "dsdT_T", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame2 = new TH1D("hFrame2", "", 100, 0, 0.3);
	hFrame2->GetXaxis()->SetTitle("Electron Kinetic Energy (MeV)");
	hFrame2->GetYaxis()->SetTitle("Differential Cross Section (cm^2 / MeV)");
	hFrame2->GetXaxis()->SetTitleSize(0.047);
	hFrame2->GetYaxis()->SetTitleSize(0.047);
	hFrame2->GetXaxis()->SetTitleOffset(1.1);
	hFrame2->GetYaxis()->SetTitleOffset(1.1);
	hFrame2->GetXaxis()->CenterTitle();
	hFrame2->GetYaxis()->CenterTitle();
	hFrame2->GetXaxis()->SetLabelSize(0.038);
	hFrame2->GetYaxis()->SetLabelSize(0.038);
	hFrame2->GetYaxis()->SetNdivisions(505);
	hFrame2->GetYaxis()->SetRangeUser(0, 12e-45);
	hFrame2->Draw();

	gdsdT_T_1_e->SetLineColor(1);
	gdsdT_T_1_e->Draw("SAMEl");
	gdsdT_T_2_e->SetLineColor(2);
	gdsdT_T_2_e->Draw("SAMEl");
	gdsdT_T_3_e->SetLineColor(3);
	gdsdT_T_3_e->Draw("SAMEl");
	gdsdT_T_1_m->SetLineColor(1);
	gdsdT_T_1_m->SetLineStyle(7);
	gdsdT_T_1_m->Draw("SAMEl");
	gdsdT_T_2_m->SetLineColor(2);
	gdsdT_T_2_m->SetLineStyle(7);
	gdsdT_T_2_m->Draw("SAMEl");
	gdsdT_T_3_m->SetLineColor(3);
	gdsdT_T_3_m->SetLineStyle(7);
	gdsdT_T_3_m->Draw("SAMEl");

	TLegend* leg2 = new TLegend();
	leg2->AddEntry("#nu_{e} - e^{-}, E = 0.1 MeV", "#nu_{e} - e^{-}, E = 0.1 MeV", "l");
	leg2->AddEntry("#nu_{#mu} - e^{-}, E = 0.1 MeV", "#nu_{#mu} - e^{-}, E = 0.1 MeV", "l");
	leg2->AddEntry("#nu_{e} - e^{-}, E = 0.2 MeV", "#nu_{e} - e^{-}, E = 0.2 MeV", "l");
	leg2->AddEntry("#nu_{#mu} - e^{-}, E = 0.2 MeV", "#nu_{#mu} - e^{-}, E = 0.2 MeV", "l");
	leg2->AddEntry("#nu_{e} - e^{-}, E = 0.3 MeV", "#nu_{e} - e^{-}, E = 0.3 MeV", "l");
	leg2->AddEntry("#nu_{#mu} - e^{-}, E = 0.3 MeV", "#nu_{#mu} - e^{-}, E = 0.3 MeV", "l");
	leg2->Draw();

}
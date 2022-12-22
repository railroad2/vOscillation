// Solar Flux
#include "../vClass.hh"

void PlotSolarFlux()
{
	gStyle->SetOptStat(kFALSE);

	vSolarFlux* vsf = new vSolarFlux();
	TGraph* gSolarPP  = new TGraph(); // continuous
	TGraph* gSolarHEP = new TGraph(); // continuous
	TGraph* gSolarB8  = new TGraph(); // continuous
	TGraph* gSolarN13 = new TGraph(); // continuous
	TGraph* gSolarO15 = new TGraph(); // continuous
	TGraph* gSolarF17 = new TGraph(); // continuous
	TGraph* gSolarPEP = new TGraph(); // discontinuous
	TGraph* gSolarBE7 = new TGraph(); // discontinuous

	int N = 1001;
	double a = 0.1;
	double b = 10;

	for (int i = 0; i < N; i++)
	{
		double E = a + (b - a) * (double)i / (double)(N - 1);

		gSolarPP ->SetPoint(i, E, vsf->GetSolarNeutrinoFlux_NoPeak(E, 1));
		gSolarHEP->SetPoint(i, E, vsf->GetSolarNeutrinoFlux_NoPeak(E, 2));
		gSolarB8 ->SetPoint(i, E, vsf->GetSolarNeutrinoFlux_NoPeak(E, 3));
		gSolarN13->SetPoint(i, E, vsf->GetSolarNeutrinoFlux_NoPeak(E, 4));
		gSolarO15->SetPoint(i, E, vsf->GetSolarNeutrinoFlux_NoPeak(E, 5));
		gSolarF17->SetPoint(i, E, vsf->GetSolarNeutrinoFlux_NoPeak(E, 6));
	}

	gSolarPEP->SetPoint(0, vsf->GetSolarNeutrinoFlux_PeakEnergy(7), 0);
	gSolarPEP->SetPoint(1, vsf->GetSolarNeutrinoFlux_PeakEnergy(7), vsf->GetSolarNeutrinoFlux_PeakFlux(7));
	gSolarPEP->SetPoint(2, vsf->GetSolarNeutrinoFlux_PeakEnergy(7), 0);
	gSolarBE7->SetPoint(0, vsf->GetSolarNeutrinoFlux_PeakEnergy(8), 0);
	gSolarBE7->SetPoint(1, vsf->GetSolarNeutrinoFlux_PeakEnergy(8), vsf->GetSolarNeutrinoFlux_PeakFlux(8));
	gSolarBE7->SetPoint(2, vsf->GetSolarNeutrinoFlux_PeakEnergy(8), 0);
	gSolarBE7->SetPoint(3, vsf->GetSolarNeutrinoFlux_PeakEnergy(9), 0);
	gSolarBE7->SetPoint(4, vsf->GetSolarNeutrinoFlux_PeakEnergy(9), vsf->GetSolarNeutrinoFlux_PeakFlux(9));
	gSolarBE7->SetPoint(5, vsf->GetSolarNeutrinoFlux_PeakEnergy(9), 0);

	TCanvas* can1 = new TCanvas("SolarFlux", "SolarFlux", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame = new TH1D("hFrame", "", 100, 0, 10);
	hFrame->GetXaxis()->SetTitle("Neutrino Energy (MeV)");
	hFrame->GetYaxis()->SetTitle("Solar Neutrino Flux (/cm^2/day/MeV  or  /cm^2/day)");
	gPad->SetLogy();
	gPad->SetLogx();
	hFrame->GetYaxis()->SetRangeUser(1.e4, 1.e17);
	hFrame->Draw();

	gSolarPP ->SetLineColor(1);
	gSolarHEP->SetLineColor(2);
	gSolarB8 ->SetLineColor(3);
	gSolarN13->SetLineColor(4);
	gSolarO15->SetLineColor(5);
	gSolarF17->SetLineColor(6);
	gSolarPEP->SetLineColor(7);
	gSolarBE7->SetLineColor(8);

	gSolarPP ->Draw("SAMEl");
	gSolarHEP->Draw("SAMEl");
	gSolarB8 ->Draw("SAMEl");
	gSolarN13->Draw("SAMEl");
	gSolarO15->Draw("SAMEl");
	gSolarF17->Draw("SAMEl");
	gSolarPEP->Draw("SAMEl");
	gSolarBE7->Draw("SAMEl");


	TLatex* latPP = new TLatex(0.2, 7.e15, "pp");
	latPP->SetTextColor(1);
	latPP->SetTextSize(0.03);
	latPP->SetTextFont(42);
	latPP->Draw("SAME");

	TLatex* latHEP = new TLatex(5., 1.e7, "hep");
	latHEP->SetTextColor(2);
	latHEP->SetTextSize(0.03);
	latHEP->SetTextFont(42);
	latHEP->Draw("SAME");

	TLatex* latB8 = new TLatex(5., 1.e11, "B8");
	latB8->SetTextColor(3);
	latB8->SetTextSize(0.03);
	latB8->SetTextFont(42);
	latB8->Draw("SAME");

	TLatex* latN13 = new TLatex(0.5, 5.e13, "N13");
	latN13->SetTextColor(4);
	latN13->SetTextSize(0.03);
	latN13->SetTextFont(42);
	latN13->Draw("SAME");

	TLatex* latO15 = new TLatex(0.5, 3.e12, "O15");
	latO15->SetTextColor(5);
	latO15->SetTextSize(0.03);
	latO15->SetTextFont(42);
	latO15->Draw("SAME");

	TLatex* latF17 = new TLatex(0.5, 1.e11, "F17");
	latF17->SetTextColor(6);
	latF17->SetTextSize(0.03);
	latF17->SetTextFont(42);
	latF17->Draw("SAME");

	TLatex* latPEP = new TLatex(1.5, 7.e12, "pep");
	latPEP->SetTextColor(7);
	latPEP->SetTextSize(0.03);
	latPEP->SetTextFont(42);
	latPEP->Draw("SAME");

	TLatex* latBe7 = new TLatex(0.8, 1.e15, "Be7");
	latBe7->SetTextColor(8);
	latBe7->SetTextSize(0.03);
	latBe7->SetTextFont(42);
	latBe7->Draw("SAME");
}
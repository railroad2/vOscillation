#include "../vClass.hh"

void PlotOscillating()
{
	gStyle->SetOptStat(kFALSE);

	TGraph* gve2ve = new TGraph(); // v_e -> v_e
	gve2ve->SetLineColor(1);
	gve2ve->SetName("Pee");
	TGraph* gve2vm = new TGraph(); // v_e -> v_mu
	gve2vm->SetLineColor(2);
	gve2vm->SetName("Pem");
	TGraph* gve2vt = new TGraph(); // v_e -> v_tau
	gve2vt->SetLineColor(3);
	gve2vt->SetName("Pet");
	TGraph* gvm2ve = new TGraph(); // v_mu -> v_e
	gvm2ve->SetLineColor(1);
	gvm2ve->SetName("Pme");
	TGraph* gvm2vm = new TGraph(); // v_mu -> v_mu
	gvm2vm->SetLineColor(2);
	gvm2vm->SetName("Pmm");
	TGraph* gvm2vt = new TGraph(); // v_mu -> v_tau
	gvm2vt->SetLineColor(3);
	gvm2vt->SetName("Pmt");
	TGraph* gvt2ve = new TGraph(); // v_tau -> v_e
	gvt2ve->SetLineColor(1);
	gvt2ve->SetName("Pte");
	TGraph* gvt2vm = new TGraph(); // v_tau -> v_mu
	gvt2vm->SetLineColor(2);
	gvt2vm->SetName("Ptm");
	TGraph* gvt2vt = new TGraph(); // v_tau -> v_tau
	gvt2vt->SetLineColor(3);
	gvt2vt->SetName("Ptt");

	bool whetherIO = false; // false : Normal Ordering, true : Inversed Ordering
	vOscillating* vosc = new vOscillating();
	vosc->LoadStdData(whetherIO); // load PDG data for 3v-oscillating parameters

	bool whetherAnti = false; // false -> neutrino, true -> anti neutrino
	double endLoE = 25000; // m/MeV


	int gN = 500;
	for (int i = 0; i < gN; i++)
	{
		double LoE = endLoE * (double)i / (double)(gN-1);
		gve2ve->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "e", "e", whetherAnti));
		gve2vm->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "e", "mu", whetherAnti));
		gve2vt->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "e", "tau", whetherAnti));
		gvm2ve->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "mu", "e", whetherAnti));
		gvm2vm->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "mu", "mu", whetherAnti));
		gvm2vt->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "mu", "tau", whetherAnti));
		gvt2ve->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "tau", "e", whetherAnti));
		gvt2vm->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "tau", "mu", whetherAnti));
		gvt2vt->SetPoint(i, LoE, vosc->GetProbability(LoE, 1, "tau", "tau", whetherAnti));
	}


	// Plot

	TCanvas* can1 = new TCanvas("Electron Neutrino Survival Probability", "Electron Neutrino Survival Probability", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame1 = new TH1D("hFrame1", "", 100, 0, endLoE);
	hFrame1->GetXaxis()->SetTitle("L/E (m/MeV)");
	hFrame1->GetYaxis()->SetTitle("Probability");
	hFrame1->GetYaxis()->SetRangeUser(0, 1);
	hFrame1->Draw();
	gve2ve->Draw("SAMEl");
	gve2vm->Draw("SAMEl");
	gve2vt->Draw("SAMEl");

	TLegend* leg1 = new TLegend();
	leg1->AddEntry("Pee", "P(#nu_{e}->#nu_{e})", "l");
	leg1->AddEntry("Pem", "P(#nu_{e}->#nu_{#mu})", "l");
	leg1->AddEntry("Pet", "P(#nu_{e}->#nu_{#tau})", "l");
	leg1->Draw();



	TCanvas* can2 = new TCanvas("Muon Neutrino Survival Probability", "Muon Neutrino Survival Probability", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame2 = new TH1D("hFrame2", "", 100, 0, endLoE);
	hFrame2->GetXaxis()->SetTitle("L/E (m/MeV)");
	hFrame2->GetYaxis()->SetTitle("Probability");
	hFrame2->GetYaxis()->SetRangeUser(0, 1);
	hFrame2->Draw();
	gvm2ve->Draw("SAMEl");
	gvm2vm->Draw("SAMEl");
	gvm2vt->Draw("SAMEl");

	TLegend* leg2 = new TLegend();
	leg2->AddEntry("Pme", "P(#nu_{#mu}->#nu_{e})", "l");
	leg2->AddEntry("Pmm", "P(#nu_{#mu}->#nu_{#mu})", "l");
	leg2->AddEntry("Pmt", "P(#nu_{#mu}->#nu_{#tau})", "l");
	leg2->Draw();



	TCanvas* can3 = new TCanvas("Tau Neutrino Survival Probability", "Tau Neutrino Survival Probability", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	TH1D* hFrame3 = new TH1D("hFrame3", "", 100, 0, endLoE);
	hFrame3->GetXaxis()->SetTitle("L/E (m/MeV)");
	hFrame3->GetYaxis()->SetTitle("Probability");
	hFrame3->GetYaxis()->SetRangeUser(0, 1);
	hFrame3->Draw();
	gvt2ve->Draw("SAMEl");
	gvt2vm->Draw("SAMEl");
	gvt2vt->Draw("SAMEl");

	TLegend* leg3 = new TLegend();
	leg3->AddEntry("Pte", "P(#nu_{#tau}->#nu_{e})", "l");
	leg3->AddEntry("Ptm", "P(#nu_{#tau}->#nu_{#mu})", "l");
	leg3->AddEntry("Ptt", "P(#nu_{#tau}->#nu_{#tau})", "l");
	leg3->Draw();
}
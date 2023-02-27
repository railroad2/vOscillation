#include "../vClass.hh"


void ModelGenerator_Reactor()
{
	gStyle->SetOptStat(kFALSE);
	gRandom->SetSeed(0);


	// Source Spatial Information Setting (point, Volume = 0)
	vSource* source = new vSource();


	// Detector Information Setting
	double R_det = 7.5; // LSC : 7.5 m
	double H_det = 15; // LSC : 15 m
	vDetectorCylinder* detector = new vDetectorCylinder();
	detector->SetRadius(R_det);
	detector->SetHeight(H_det);
	double ResolutionE = 0.05;
	double ResolutionL = 0.12;
	detector->SetResolutionE(ResolutionE);
	detector->SetResolutionL(ResolutionL);
	detector->Initialization();
	double N_p = detector->GetProtonNumber();


	// Energy Spectrum TF assign
	double thermalPower = 24.84;
	vReactorSpectrum* vrf = new vReactorSpectrum("HuberMueller");
	vrf->SetThermalPower(thermalPower);
	double Emin = 1.5;
	double Emax = 10.;
	vEnergySpectrum ves = vEnergySpectrum(vrf, Emin, Emax);


	// Set Oscillating Model
	vOscillation* vosc = new vOscillation();
	vosc->LoadStdData();


	// Set Model Generator Parameter
	vModelGeneratorLBL* vmg = new vModelGeneratorLBL(detector, source, ves);
	double delta_X = 53000.;
	double delta_Z = 0;
	vmg->SetDeltaX(delta_X);
	vmg->SetDeltaZ(delta_Z);
	vmg->SetvOscillation(vosc);
	vmg->Initialization();


	// Set Histogram Parameter

	int binNum = 500;
	TH1D* histL = new TH1D("histL_NoOsc", "", binNum, delta_X - R_det, delta_X + R_det);
	TH1D* histE = new TH1D("histE_NoOsc", "", binNum, 0, Emax);
	TH1D* histLoE = new TH1D("histLoE_NoOsc", "", binNum, (delta_X - R_det) / Emax, (delta_X + R_det) / Emin);
	TH2D* histLE = new TH2D("histLE_NoOsc", "", binNum, delta_X - R_det, delta_X + R_det, binNum, 0, Emax);


	// Get the Monte Carlo Result

	int64_t N = 10000000;
	int64_t iterNum;
	vmg->FillHistogram(histL, histE, histLoE, histLE, iterNum, N);


	// Print Information
	cout << "iterNum : " << iterNum << endl;
	vmg->PrintInfo();


	// Plot the Histogram

	TCanvas* can1 = new TCanvas("Distance", "Distance", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	histL->GetXaxis()->SetTitle("Detected Distance (m)");
	histL->GetYaxis()->SetTitle("Count");
	histL->GetXaxis()->SetTitleSize(0.047);
	histL->GetYaxis()->SetTitleSize(0.047);
	histL->GetXaxis()->SetTitleOffset(1.1);
	histL->GetYaxis()->SetTitleOffset(1.1);
	histL->GetXaxis()->CenterTitle();
	histL->GetYaxis()->CenterTitle();
	histL->GetXaxis()->SetLabelSize(0.038);
	histL->GetYaxis()->SetLabelSize(0.038);
	histL->GetYaxis()->SetNdivisions(505);
	histL->Draw();


	TCanvas* can2 = new TCanvas("Energy", "Energy", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	histE->GetXaxis()->SetTitle("Prompt Energy (MeV)");
	histE->GetYaxis()->SetTitle("Count");
	histE->GetXaxis()->SetTitleSize(0.047);
	histE->GetYaxis()->SetTitleSize(0.047);
	histE->GetXaxis()->SetTitleOffset(1.1);
	histE->GetYaxis()->SetTitleOffset(1.1);
	histE->GetXaxis()->CenterTitle();
	histE->GetYaxis()->CenterTitle();
	histE->GetXaxis()->SetLabelSize(0.038);
	histE->GetYaxis()->SetLabelSize(0.038);
	histE->GetYaxis()->SetNdivisions(505);
	histE->Draw();


	TCanvas* can3 = new TCanvas("LoverE", "LoverE", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	histLoE->GetXaxis()->SetTitle("LoverE (m/MeV)");
	histLoE->GetYaxis()->SetTitle("Count");
	histLoE->GetXaxis()->SetTitleSize(0.047);
	histLoE->GetYaxis()->SetTitleSize(0.047);
	histLoE->GetXaxis()->SetTitleOffset(1.1);
	histLoE->GetYaxis()->SetTitleOffset(1.1);
	histLoE->GetXaxis()->CenterTitle();
	histLoE->GetYaxis()->CenterTitle();
	histLoE->GetXaxis()->SetLabelSize(0.038);
	histLoE->GetYaxis()->SetLabelSize(0.038);
	histLoE->GetYaxis()->SetNdivisions(505);
	histLoE->Draw();


	TCanvas* can4 = new TCanvas("LE 2d Histogram", "LE 2d Histogram", 1200, 800);
	gPad->SetLeftMargin(0.12);
	gPad->SetBottomMargin(0.12);
	gPad->SetRightMargin(0.08);
	gPad->SetTopMargin(0.05);

	histLE->GetXaxis()->SetTitle("Distance (m)");
	histLE->GetYaxis()->SetTitle("Energy (MeV)");
	histLE->GetZaxis()->SetTitle("Count");
	histLE->GetXaxis()->SetTitleSize(0.047);
	histLE->GetYaxis()->SetTitleSize(0.047);
	histLE->GetXaxis()->SetTitleOffset(1.1);
	histLE->GetYaxis()->SetTitleOffset(1.1);
	histLE->GetXaxis()->CenterTitle();
	histLE->GetYaxis()->CenterTitle();
	histLE->GetXaxis()->SetLabelSize(0.038);
	histLE->GetYaxis()->SetLabelSize(0.038);
	histLE->GetYaxis()->SetNdivisions(505);
	histLE->Draw("COL4Z");

}
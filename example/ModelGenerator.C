#include "../vClass.hh"


void ModelGenerator()
{
	gStyle->SetOptStat(kFALSE);
	gRandom->SetSeed(0);	

	// Set expDays and Source Activity Information Setting

	double expDays = 500.; // day
	double halflife_Ce = 285.; // day
	double lifetime_Ce = halflife_Ce / TMath::Log(2);
	double Activity = 150. * 1.e3 * 3.7e10;
	// double int_Activ = Activity * lifetime_Ce * 8.64e4 * (1 - TMath::Exp(-expDays / lifetime_Ce));
	double int_Activ = Activity * expDays * 8.64e4;

	// Source Spatial Information Setting	
	double R_source = 0.085;
	double H_source = 0.17;
	vSourceCylinder* source = new vSourceCylinder();
	source->SetRadius(R_source);
	source->SetHeight(H_source);


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


	// Energy Spectrum TF assign
	vCe144Spectrum* vbs = new vCe144Spectrum();
	vbs->SetActivity(int_Activ);
	double Emin = 1.8;
	double Emax = 3.0;
	vEnergySpectrum fobj = vEnergySpectrum(vbs, Emin, Emax);


	// Set Sterile Model For No Osc
	vSterileEE* vst = new vSterileEE();
	vst->Sets22t14(0);
	vst->SetDm2_41(0);

	// Set Model Generator Parameter
	vModelGeneratorSterileEE* vmg = new vModelGeneratorSterileEE(detector, source, fobj);
	double delta_X = 9.4;
	double delta_Z = 0;
	vmg->SetDeltaX(delta_X);
	vmg->SetDeltaZ(delta_Z);
	vmg->SetSterileEE(vst);
	vmg->Initialization();
	double rmin = vmg->GetRmin();
	

	// Get L_max
	double Lmax = (double)(int)(TMath::Sqrt(delta_X * delta_X + delta_Z * delta_Z) + R_det + H_det / 2.) + 1.;
	cout << "Lmax : " << Lmax << endl;


	// PrintInfo
	vmg->PrintInfo();


	// Set Histogram Parameter

	int binNum = 500;
	TH1D* histL = new TH1D("histL_NoOsc", "", binNum, 0, Lmax);
	TH1D* histE = new TH1D("histE_NoOsc", "", binNum, 0, 2.5);
	TH1D* histLoE = new TH1D("histLoE_NoOsc", "", binNum, 0, Lmax);
	TH2D* histLE = new TH2D("histLE_NoOsc", "", binNum, 0, Lmax, binNum, 0, 2.5);

	// Get the Monte Carlo Result

	int64_t N = 10000000;
	int64_t iterNum;
	vmg->FillHistogram(histL, histE, histLoE, histLE, iterNum, N);


	// Save the Original Histogram and iterNum
	TFile* file = new TFile(Form("Model_NoOsc_dx_%.2f_resol_E%.3fL%.3f.root", delta_X, ResolutionE, ResolutionL), "recreate");
	histL->Write();
	histE->Write();
	histLoE->Write();
	histLE->Write();
	TVector3* onlyFirstIsIterNum = new TVector3(0, 0, 0);
	onlyFirstIsIterNum->SetX(iterNum);
	onlyFirstIsIterNum->Write();
	file->Close();

	TString modelFileName = Form("Model_NoOsc_dx_%.2f_resol_E%.3fL%.3f.root", delta_X, ResolutionE, ResolutionL);
	TFile* readFile = new TFile(modelFileName, "read");
	TVector3* temp = (TVector3*)readFile->Get("TVector3");
	cout << temp->X() << endl;


	// Print Information

	cout << "expDays (day)                         : " << expDays << endl;
	cout << "Source Radius (m)                     : " << R_source << endl;
	cout << "       Height (m)                     : " << H_source << endl;
	cout << "       Activity (/s)                  : " << Activity << endl;
	cout << "       Time Integral of Activity      : " << int_Activ << endl;
	cout << "Detector Radius (m)                   : " << R_det << endl;
	cout << "         Height (m)                   : " << H_det << endl;
	// cout << "         Proton Number                : " << N_p << endl;
	cout << "Center to Center Distance (m)         : " << delta_X << endl;
	// cout << "Minimum of Distance (m)               : " << rmin << endl;
	// cout << "Spectrum-Averaged Cross Section (m^2) : " << intg_Spectrum << endl;
	cout << "iterNum                               : " << iterNum << endl;
	


	// cout << "Total Detected Event Number : " << coef * N << endl;
	// cout << "Expected Event Number       : " << effIBD * N_p * intg_Spectrum * int_Activ / 8. / TMath::Pi() / delta_X / delta_X;

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
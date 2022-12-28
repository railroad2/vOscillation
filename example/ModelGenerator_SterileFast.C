#include "../vClass.hh"


void ModelGenerator_SterileFast()
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

	double R_det = 7.5;
	double H_det = 15;
	double delta_X = 9.5; // 조정가능
	double delta_Z = 0; // 조사해야함
	vDetectorCylinder* detector = new vDetectorCylinder();
	detector->SetRadius(R_det);
	detector->SetHeight(H_det);
	double ResolutionE = 0.05;
	double ResolutionL = 0.12;
	detector->SetResolutionE(ResolutionE);
	detector->SetResolutionL(ResolutionL);
	detector->Initialization();


	// Get L_max

	double Lmax = (double)(int)(delta_X + delta_Z + H_det / 2 + R_det) + 1.;
	cout << "Lmax : " << Lmax << endl;


	// Energy Spectrum TF assign

	vCe144Spectrum* vbs = new vCe144Spectrum();
	vbs->SetActivity(int_Activ);
	double Emin = 1.8;
	double Emax = 3.0;
	vEnergySpectrum fobj = vEnergySpectrum(vbs, Emin, Emax);


	// Set Sterile Model Parameter
	vSterileEE* vst = new vSterileEE();
	vst->Sets22t14(1.);
	

	// Set Model Generator Parameter
	vModelGeneratorSterileEE* vmg = new vModelGeneratorSterileEE(detector, source, fobj);
	vmg->SetDeltaX(delta_X);
	vmg->SetDeltaZ(delta_Z);
	vmg->Initialization();
	cout << "Rmin : " << vmg->GetRmin() << endl;
	

	int binNum = 500;
	int startIndex = 0;
	int listSize = 20;
	int64_t N = 1000000;
	int64_t iterNum;
	double minDm2 = 1.e-2;
	double maxDm2 = 1.e2;
	double logMinDm2 = TMath::Log(minDm2);
	double logMaxDm2 = TMath::Log(maxDm2);
	std::vector<double> Dm2list(listSize);
	TH1D* histL[listSize];
	TH1D* histE[listSize];
	TH1D* histLoE[listSize];
	TH2D* histLE[listSize];


	for (int i = startIndex; i < listSize; i++)
	{
		Dm2list[i] = TMath::Exp(logMinDm2 + (logMaxDm2 - logMinDm2) * (double)i / (double)(listSize - 1));
		histL[i] = new TH1D(Form("histL_%d", i), "", binNum, 0, Lmax);
		histE[i] = new TH1D(Form("histE_%d", i), "", binNum, 0, 2.5);
		histLoE[i] = new TH1D(Form("histLoE_%d", i), "", binNum, 0, Lmax / 1.5);
		histLE[i] = new TH2D(Form("histLE_%d", i), "", binNum, 0, Lmax, binNum, 0, 2.5);
	}

	vmg->FillHistogramFast(histL, histE, histLoE, histLE, listSize, Dm2list, N);

	TFile* file;
	TString modelFileName;
	TFile* readFile;

	for (int i = startIndex; i < listSize; i++)
	{
		file = new TFile(Form("Model_Sterile_dx_%.2f_resol_E%.3fL%.3f_Dm2_%.2e.root", delta_X, ResolutionE, ResolutionL, Dm2list[i]), "recreate");
		histL[i]->Write();
		histE[i]->Write();
		histLoE[i]->Write();
		histLE[i]->Write();
		file->Close();

		modelFileName = Form("Model_Sterile_dx_%.2f_resol_E%.3fL%.3f_Dm2_%.2e.root", delta_X, ResolutionE, ResolutionL, Dm2list[i]);
		readFile = new TFile(modelFileName, "read");
	}
}
#include "../header/vModelGeneratorLBL.hh"
#include "TF1.h"


void vModelGeneratorLBL::FillHistogram(TH1D* oHistL, TH1D* oHistE, TH1D* oHistLoE, TH2D* oHistLE, int64_t& oIterNum, int64_t genNum) const
{
	// Energy Spectrum TF assign
	TF1* tfEnergy = new TF1("tfEnergy", fSpectrum, fSpectrum.GetEmin(), fSpectrum.GetEmax(), 0);
	tfEnergy->SetNpx(500);

	// Prompt Energy Threshold
	double DeltaEnergy = MASSDELTA - MASSELECTRON;

	// Call Resolution Information
	double ResolutionE = fDetector->GetResolutionE();

	double X_det, Y_det, Z_det, X_source, Y_source, Z_source;
	double resolX, resolY, resolZ, resolE;
	oIterNum = 0;
	for (int i = 0; i < genNum; i++)
	{
		// Get X, Y, Z
		fSource->GetRandomPosition(X_source, Y_source, Z_source);
		fDetector->GetRandomPosition(X_det, Y_det, Z_det);
		double L = CalculateL(X_source - X_det + fDeltaX, Y_source - Y_det, Z_source - Z_det + fDeltaZ);

		// Get E_nu
		double E_nu = tfEnergy->GetRandom();

		// Get Survival Probability
		double P = fvosc->GetProbability(L, E_nu, "e", "e", true);

		if (gRandom->Uniform(0, 1) < P)
		{
			fDetector->GetRandomResolutionEnergy(resolE, E_nu);
			fDetector->GetRandomResolutionPosition(resolX, resolY, resolZ, E_nu);

			double L_det = CalculateL(-X_det + fDeltaX + resolX, -Y_det + resolY, -Z_det + fDeltaZ + resolZ);
			double E_prompt = E_nu - DeltaEnergy;
			double E_det = E_prompt + resolE;

			oHistL->Fill(L_det);
			oHistE->Fill(E_det);
			oHistLoE->Fill(L_det / E_det);
			oHistLE->Fill(L_det, E_det);

			if (i % (int)(genNum / 10) == 0) std::cout << (int)((double)i / (double)genNum * 100) << "%" << std::endl;
		}
		else
		{
			i--;
		}
		oIterNum++;
	}
	double AveragedCrossSection = tfEnergy->Integral(fSpectrum.GetEmin(), fSpectrum.GetEmax());
	double N_p = fDetector->GetProtonNumber();
	double Coef = AveragedCrossSection * N_p / 4 / TMath::Pi() / fDistance / fDistance / (double)oIterNum;
	oHistL->Scale(Coef, "nosw2");
	oHistE->Scale(Coef, "nosw2");
	oHistLoE->Scale(Coef, "nosw2");
	oHistLE->Scale(Coef, "nosw2");
}


void vModelGeneratorLBL::PrintInfo() const
{
	cout << "<vModelGenerator>" << endl;
	cout << "    Delta X          : " << fDeltaX << endl;
	cout << "    Delta Z          : " << fDeltaZ << endl;
	fDetector->PrintInfo();
	fSource->PrintInfo();
	fSpectrum.PrintInfo();
}


void vModelGeneratorLBL::CalDistance()
{
	double delta_X = this->GetDeltaX();
	double delta_Z = this->GetDeltaZ();
	fDistance = TMath::Sqrt(delta_X * delta_X + delta_Z * delta_Z);
}
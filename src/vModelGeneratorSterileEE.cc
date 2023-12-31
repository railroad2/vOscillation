#include "../header/vModelGeneratorSterileEE.hh"
#include "../header/vConstant.hh"
#include "../header/vDetector.hh"
#include "../header/vDetectorCylinder.hh"
#include "../header/vDetectorSphere.hh"
#include "../header/vSource.hh"
#include "../header/vSourceCylinder.hh"
#include "../header/vSourceSphere.hh"


void vModelGeneratorSterileEE::FillHistogram(TH1D* oHistL, TH1D* oHistE, TH1D* oHistLoE, TH2D* oHistLE, int64_t& oIterNum, int64_t genNum) const
{
	// Energy Spectrum TF assign
	TF1* tfEnergy = new TF1("tfEnergy", fSpectrum, fSpectrum.GetEmin(), fSpectrum.GetEmax(), 0);
	tfEnergy->SetNpx(500);
	tfEnergy->Draw();

	// Prompt Energy Threshold
	double DeltaEnergy = MASSDELTA - MASSELECTRON; // m_n - m_p - m_e

	// Call Resolution Information
	double ResolutionL = fDetector->GetResolutionL();
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

		if (gRandom->Uniform(0, 1) < frmin * frmin / L / L)
		{
			// Get E_nu
			double E_nu = tfEnergy->GetRandom();

			// Get Survival Probability
			double P = fvst->GetProbability_SBL(L / E_nu);

			if (gRandom->Uniform(0, 1) < P)
			{
				fDetector->GetRandomResolutionPosition(resolX, resolY, resolZ, E_nu);
				fDetector->GetRandomResolutionEnergy(resolE, E_nu);

				double L_det = CalculateL(-X_det + fDeltaX + resolX, -Y_det + resolY, -Z_det + fDeltaZ + resolZ);
				double E_prompt = E_nu - DeltaEnergy;
				double E_det = E_prompt + resolE;

				oHistL->Fill(L_det);
				oHistE->Fill(E_det);
				oHistLoE->Fill(L_det / E_det);
				oHistLE->Fill(L_det, E_det);

				if (i % (int)(genNum / 10) == 0) std::cout << (int)((double)i / (double)genNum * 100) << "%" << std::endl;
			}
			else i--;
		}
		else i--;
		oIterNum++;
	}
	double IntegralCurrentCrossSection = tfEnergy->Integral(fSpectrum.GetEmin(), fSpectrum.GetEmax());
	double N_p = fDetector->GetProtonNumber();
	double Coef = IntegralCurrentCrossSection * N_p / 4 / TMath::Pi() / frmin / frmin / (double)oIterNum;
	oHistL->Scale(Coef, "nosw2");
	oHistE->Scale(Coef, "nosw2");
	oHistLoE->Scale(Coef, "nosw2");
	oHistLE->Scale(Coef, "nosw2");
}


void vModelGeneratorSterileEE::FillHistogramFast(TH1D** oHistLList, TH1D** oHistEList, TH1D** oHistLoEList, TH2D** oHistLEList,
	int listSize, std::vector<double> Dm2_List, int64_t genNum) const
{
	// Energy Spectrum TF assign
	TF1* tfEnergy = new TF1("tfEnergy", fSpectrum, fSpectrum.GetEmin(), fSpectrum.GetEmax(), 0);
	tfEnergy->SetNpx(500);
	tfEnergy->Draw();

	// Prompt Energy Threshold
	double DeltaEnergy = MASSDELTA - MASSELECTRON; // m_n - m_p - m_e

	// Call Resolution Information
	double ResolutionL = fDetector->GetResolutionL();
	double ResolutionE = fDetector->GetResolutionE();

	vSterileEE* vst = new vSterileEE();
	vst->Sets22t14(1.);

	std::vector<int64_t> genNumList(listSize);
	std::vector<int64_t> iterNumList(listSize);
	int64_t minGenNum = 0;

	double X_det, Y_det, Z_det, X_source, Y_source, Z_source;
	double resolX, resolY, resolZ, resolE;
	for (int i = 0; i < genNum; i++)
	{
		// Get X, Y, Z
		fSource->GetRandomPosition(X_source, Y_source, Z_source);
		fDetector->GetRandomPosition(X_det, Y_det, Z_det);
		double L = CalculateL(X_source - X_det + fDeltaX, Y_source - Y_det, Z_source - Z_det + fDeltaZ);

		// Get E_nu
		double E_nu = tfEnergy->GetRandom();

		fDetector->GetRandomResolutionPosition(resolX, resolY, resolZ, E_nu);
		fDetector->GetRandomResolutionEnergy(resolE, E_nu);

		double L_det = CalculateL(-X_det + fDeltaX + resolX, -Y_det + resolY, -Z_det + fDeltaZ + resolZ);
		double E_prompt = E_nu - DeltaEnergy;
		double E_det = E_prompt + resolE;

		minGenNum = genNum;
		for (int j = 0; j < listSize; j++)
		{
			if (genNumList[j] != genNum)
			{
				// Get Survival Probability
				vst->SetDm2_41(Dm2_List[j]);
				double P = vst->GetProbability_SBL(L / E_nu);

				if (gRandom->Uniform(0, 1) < P * frmin * frmin / L / L)
				{
					oHistLList[j]->Fill(L_det);
					oHistEList[j]->Fill(E_det);
					oHistLoEList[j]->Fill(L_det / E_det);
					oHistLEList[j]->Fill(L_det, E_det);

					genNumList[j]++;
					if (minGenNum > genNumList[j]) minGenNum = genNumList[j];
				}
				iterNumList[j]++;
			}
		}
		if (minGenNum < genNum) i--;
		else if (i % (int)(genNum / 10) == 0) std::cout << (int)((double)i / (double)genNum * 100) << "%" << std::endl;
	}

	double IntegralCurrentCrossSection = tfEnergy->Integral(fSpectrum.GetEmin(), fSpectrum.GetEmax());
	double N_p = fDetector->GetProtonNumber();
	std::vector<double> Coef(listSize);
	for (int i = 0; i < listSize; i++)
	{
		Coef[i] = IntegralCurrentCrossSection * N_p / 4 / TMath::Pi() / frmin / frmin / (double)(iterNumList[i]);
		oHistLList[i]->Scale(Coef[i], "nosw2");
		oHistEList[i]->Scale(Coef[i], "nosw2");
		oHistLoEList[i]->Scale(Coef[i], "nosw2");
		oHistLEList[i]->Scale(Coef[i], "nosw2");
	}
}


void vModelGeneratorSterileEE::PrintInfo() const
{
	std::cout << "<vModelGenerator>" << std::endl;
	std::cout << "    Minimum Distance : " << frmin << std::endl;
	std::cout << "    Delta X          : " << fDeltaX << std::endl;
	std::cout << "    Delta Z          : " << fDeltaZ << std::endl;
	fDetector->PrintInfo();
	fSource->PrintInfo();
	fSpectrum.PrintInfo();
}


double vModelGeneratorSterileEE::CalMinDistance()
{
	vDetector* detector = this->GetDetector();
	vSource* source = this->GetSource();
	TString typeD = detector->GetShapeType();
	TString typeS = source->GetShapeType();
	if (typeD == "Cylinder" && typeS == "Point")
	{
		vDetectorCylinder* detectorC = (vDetectorCylinder*)detector;
		double R_det = detectorC->GetRadius();
		double H_det = detectorC->GetHeight();

		if (TMath::Abs(fDeltaZ) < H_det / 2.)
		{
			return fDeltaX - R_det;
		}
		else
		{
			return CalculateL(fDeltaX - R_det, 0, fDeltaZ - H_det / 2.);
		}
	}
	else if (typeD == "Cylinder" && typeS == "Cylinder")
	{
		vDetectorCylinder* detectorC = (vDetectorCylinder*)detector;
		vSourceCylinder* sourceC = (vSourceCylinder*)source;
		double R_source = sourceC->GetRadius();
		double H_source = sourceC->GetHeight();
		double R_det = detectorC->GetRadius();
		double H_det = detectorC->GetHeight();
		if (TMath::Abs(fDeltaZ) < (H_det + H_source) / 2.)
		{
			return fDeltaX - R_source - R_det;
		}
		else
		{
			return CalculateL(fDeltaX - R_det - R_source, 0, fDeltaZ - (H_det + H_source) / 2.);
		}
	}
	else if (typeD == "Cylinder" && typeS == "Sphere")
	{
		vDetectorCylinder* detectorC = (vDetectorCylinder*)detector;
		vSourceSphere* sourceS = (vSourceSphere*)source;
		double R_source = sourceS->GetRadius();
		double R_det = detectorC->GetRadius();
		double H_det = detectorC->GetHeight();

		if (TMath::Abs(fDeltaZ) < H_det / 2.)
		{
			return fDeltaX - R_source - R_det;
		}
		else
		{
			return CalculateL(fDeltaX - R_det, 0, fDeltaZ - H_det / 2.) - R_source;
		}
	}
	else if (typeD == "Sphere" && typeS == "Point")
	{
		vDetectorSphere* detectorS = (vDetectorSphere*)detector;
		double R_det = detectorS->GetRadius();
		return TMath::Sqrt(fDeltaX * fDeltaX + fDeltaZ * fDeltaZ) - R_det;
	}
	else if (typeD == "Sphere" && typeS == "Cylinder")
	{
		vDetectorSphere* detectorS = (vDetectorSphere*)detector;
		vSourceCylinder* sourceC = (vSourceCylinder*)source;
		double R_det = detectorS->GetRadius();
		double R_source = sourceC->GetRadius();
		double H_source = sourceC->GetHeight();

		if (TMath::Abs(fDeltaZ) < H_source / 2.)
		{
			return fDeltaX - R_source - R_det;
		}
		else
		{
			return CalculateL(fDeltaX - R_source, 0, fDeltaZ - H_source / 2.) - R_det;
		}
	}
	else if (typeD == "Sphere" && typeS == "Sphere")
	{
		vDetectorSphere* detectorS = (vDetectorSphere*)detector;
		vSourceSphere* sourceS = (vSourceSphere*)source;
		double R_det = detectorS->GetRadius();
		double R_source = sourceS->GetRadius();
		return TMath::Sqrt(fDeltaX * fDeltaX + fDeltaZ * fDeltaZ) - R_det - R_source;
	}
	else
	{
		return 0;
	}
}
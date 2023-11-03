#include "../vClass.hh"

TF1* func_detected_source_spectrum(TVector3 relpos_source, double Wth)
{
    // reactor
    vHM->SetThermalPower(Wth); 

    // IBD cross section
    vIBD *ibd = new vIBD();

    // neutrino oscillation
    vOscillation *vosc = new vOscillation();
    vosc->LoadStdData();

    double Emin = 1.5;
    double Emax = 10;
    double NE = 1000;
    double dE = (Emax - Emin)/(NE-1);
    double E, curr, xsct, Pee;
    vector<double> x1, y1;

    for (int i=0; i<NE; i++) {
        E = Emin + i*dE;
        curr = vHM->GetCurrent(E);
        xsct = ibd->GetCrossSection(E);
        Pee = vosc->GetProbability(L0, E, "e", "e"); 
        x1.push_back(E);
        y1.push_back(curr*xsct*Pee);
    }
    vInterpolator *interp = new vInterpolator(x1, y1);
    TF1 *f1 = interp->GetTF1();
    return f1;
}


vDetector* detector()
{
    // cylindrical detector (target)
    double R_det =  7.; // m
    double H_det = 15.; // m
    double res_E = 0.05; // MeV
    double res_L = 0.12; // m

    vDetectorCylinder* det = new vDetectorCylinder();

    det->SetRadius(R_det);
    det->SetHeight(H_det);

    det->SetResolutionE(res_E);
    det->SetResolutionL(res_L);

    det->Initialization();

    return det;
}


int main()
{
    double L0 = 10; // m
    double Wth = 20; // GW
    double Emin = 1.8; // MeV
    double Emax = 10; // MeV

    // Get the function of reactor detected spectrum 
    // given the distance and thermal power 
    // (thermal power is not important because only the shape of the spectrum is used).
    TF1 *f_reactor = func_detected_reactor_spectrum(L0, Wth);
    
    // Set detector to generate ibd vertices
    vDetectorCylinder* det = (vDetectorCylinder*) detector();

    // event generator
    vEventGenerator *eg = new vEventGenerator();

    int nevt = 10000; // number of events to generate
    double t0, t1; 
    double Ev; // neutrino energy
    double x_det, y_det, z_det; // vertex position

    TFile *file = new TFile("ibdevt_reactor.root", "recreate");
    TTree *tree = new TTree("ibd_events", "ibd_events"); 
    TTree *tree2 = new TTree("info", "info");

    TLorentzVector pv0;
    TLorentzVector pe;
    TLorentzVector pn;
    TVector3 vert;

    tree->Branch("vertex", "TVector3", &vert);
    tree->Branch("pv0", "TLorentzVector", &pv0);
    tree->Branch("pe",  "TLorentzVector", &pe);
    tree->Branch("pn",  "TLorentzVector", &pn);

    tree2->Branch("dist_reactor", &L0, "L/D");
    tree2->Branch("det", "vDetectorCylinder", &det);
    tree2->Fill();

    TTimeStamp ts0;
    t0 = ts0.GetSec() + 1e-9*ts0.GetNanoSec();

    for (int i=0; i<nevt; i++) {
        Ev = f_reactor->GetRandom(Emin, Emax);
        det->GetRandomPosition(x_det, y_det, z_det);
        
        vert = TVector3(x_det, y_det, z_det);
        eg->GenerateIBD(Ev);
        pv0 = eg->GetPv0();
        pe  = eg->GetPe();
        pn  = eg->GetPn();

        tree->Fill();
    }

    TTimeStamp ts1;
    t1 = ts1.GetSec() + 1e-9*ts1.GetNanoSec();
    cout << (t1 - t0)/nevt << endl;
    tree->Write();
    tree2->Write();
    file->Close();

    return 0;
}

void evtgen_reactor()
{
    main();
}


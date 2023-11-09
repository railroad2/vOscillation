#include "../vClass.hh"

// Displaying progress bar using https://github.com/gipert/progressbar.git
#if __has_include("progressbar.hpp")
#include "progressbar.hpp"
#endif

string get_str(int i, int nevt, double t0)
{
    double ttmp;
    TTimeStamp tstmp;
    ttmp = tstmp.GetSec() + 1e-9*tstmp.GetNanoSec();
    ttmp = ttmp - t0;
    string stmp = to_string(ttmp);
    string stot = to_string(ttmp/i*nevt);

    string str = "  ";
    str += to_string(i+1) + "/" + to_string(nevt);
    str += "  ";
    str += stmp.substr(0, stmp.find('.') + 3) + "/";
    str += stot.substr(0, stot.find('.') + 3) + " s";

    return str;
}

TF1* func_detected_reactor_spectrum(double L0, double Wth)
{
    // reactor
    vReactorSpectrum *vHM = new vReactorSpectrum("HM");
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
    double L0 = 65000; // m
    double Wth = 20; // GW
    double Emin = 1.8; // MeV
    double Emax = 10; // MeV

    TVector3 uv(1, 0, 0);

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

    TFile *file = new TFile("ibdevt_reactor_singleE.root", "recreate");
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


    int last_i=0;
    string last_str;
    TTimeStamp ts0;
    t0 = ts0.GetSec() + 1e-9*ts0.GetNanoSec();

#ifdef __PROGRESSBAR_HPP
    progressbar bar(nevt);
#endif
    cout << "\e[?25l";

    for (int i=0; i<nevt; i++) {
        Ev = f_reactor->GetRandom(Emin, Emax);
        det->GetRandomPosition(x_det, y_det, z_det);
        
        vert = TVector3(x_det, y_det, z_det);
        eg->GenerateIBD(Ev, pv0, pe, pn, uv);

        tree->Fill();

        string str = get_str(i, nevt, t0);

        if (i >= last_i) {
#ifdef __PROGRESSBAR_HPP
            cout << std::string(last_str.size(), '\b');
            bar.update();
            cout << str;
#else
            cout << std::string(last_str.size(), '\b');
            cout << str;
#endif
        }
        last_i = i;
        last_str = str;
    }
    cout << "\e[?25h" << endl;

    TTimeStamp ts1;
    t1 = ts1.GetSec() + 1e-9*ts1.GetNanoSec();
    cout << "Generated events         : " << nevt << endl;
    cout << "Elapsed time             : " << (t1 - t0) << " s" << endl;
    cout << "Elapsed time per event   : " << (t1 - t0)/nevt << " s" << endl;

    tree->Write();
    tree2->Write();
    file->Close();

    return 0;
}

void evtgen_reactor()
{
    main();
}


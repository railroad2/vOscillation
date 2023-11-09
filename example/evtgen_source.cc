#include "../vClass.hh"

// Displaying progress bar using https://github.com/gipert/progressbar.git
#if __has_include("progressbar.hpp")
#include "progressbar.hpp"
#endif

double mag(double x, double z) 
{
    return TMath::Sqrt(x*x + z*z);
}

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

double get_Lmin_cylinder(double Rd, double Hd, double Xs, double Zs)
//{{{
{
    double Lmin = 0;
    double Zsa  = TMath::Abs(Zs);

    if (Xs < Rd) {
        if (Zsa < Hd/2) 
            Lmin = 0;
        else 
            Lmin = Zsa - Hd/2; 
    }
    else {
        if (Zsa < Hd/2) 
            Lmin = Xs - Rd;
        else 
            Lmin = mag(Xs - Rd, Zsa - Hd/2);
    }

    return Lmin;
}
//}}}


double get_Lmax_cylinder(double Rd, double Hd, double Xs, double Zs)
//{{{
{
    double Lmax = 0;
    double Zsa  = TMath::Abs(Zs);

    Lmax = mag(Rd + Xs, Hd/2 + Zsa);
    
    return Lmax;
}
//}}}


TF1* func_detected_source_spectrum()
// {{{
{
    /**
    the beta spectrum and ibd cross section are accounted.
    **/

    // IBD cross section
    vIBD *ibd = new vIBD();

    double Emin = 1.8;
    double Emax = 3.0;
    double NE = 1000;
    double dE = (Emax - Emin)/(NE-1);
    double E, curr, xsct;

    // beta spectrum
    vCe144Spectrum* vbs = new vCe144Spectrum();
    vbs->SetActivity(1);
    vEnergySpectrum ves = vEnergySpectrum(vbs, Emin, Emax);
    TF1 *tfEnergy = new TF1("tfEnergy", ves, Emin, Emax, 0);

    vector<double> x1, y1;

    for (int i=0; i<NE; i++) {
        E = Emin + i*dE;
        curr = tfEnergy->Eval(E);
        xsct = 1;//ibd->GetCrossSection(E);
        x1.push_back(E);
        y1.push_back(curr*xsct);
    }

    vInterpolator *interp = new vInterpolator(x1, y1);
    TF1 *f1 = interp->GetTF1();

    return f1;
}
//}}}


TF1* func_distance_distribution(vDetectorCylinder* det, double Xs, double Zs, int ndiv=1000)
//{{{
{
    double cnt;
    double cntmax = 0;
    double Rd = det->GetRadius();
    double Hd = det->GetHeight();
    double Lmin = get_Lmin_cylinder(Rd, Hd, Xs, Zs);
    double Lmax = get_Lmax_cylinder(Rd, Hd, Xs, Zs);
    double dL = (Lmax - Lmin)/(ndiv-1);
    double L;
    vector<double> x1, y1;

    for (int i=0; i<ndiv; i++) {
        L = Lmin + i*dL;
        cnt = det->GetLDistribution(L, Xs, Zs, 1000, true);
        if (cnt > cntmax) cntmax = cnt;
        x1.push_back(L);
        y1.push_back(cnt);
    }

    cout << cntmax << endl;
    for (int i=0; i<ndiv; i++) {
        y1[i] = y1[i] / cntmax;
    }

    cout << "Lmin = " << Lmin << endl;
    cout << "Lmax = " << Lmax << endl;
    cout << "dL   = " << dL << endl;

    vInterpolator *interp = new vInterpolator(x1, y1);
    TF1 *f1 = interp->GetTF1();

    return f1;
}
//}}}


vDetector* detector()
//{{{
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
//}}}


int main()
{
    double Emin = 1.8; // MeV
    double Emax = 3; // MeV
    double L;

    int nevt = 10000; // number of events to generate
    double t0, t1; 
    double Ev; // neutrino energy
    double x_det, y_det, z_det; // vertex position
    double Pee;

    double Xs = 10;
    double Ys = 0;
    double Zs = 0;

    TVector3 pos_src(10, 0, 0);
    TVector3 uv(0, 0, 1);

    //vOscillation *vosc = new vOscillation();
    vSterile *vosc = new vSterile ();
    vosc->LoadStdData();
    vosc->Load4StdData();

    vDetectorCylinder* det = (vDetectorCylinder*) detector(); // Set detector to generate ibd vertices 

    TF1 *f_source = func_detected_source_spectrum();
    TF1 *f_dist = func_distance_distribution(det, mag(Xs, Ys), Zs, 1000);

    TCanvas *c1 = new TCanvas();
    f_source->SetNpx(100);
    f_source->Draw();

    TCanvas *c2 = new TCanvas();
    f_dist->SetNpx(100);
    f_dist->Draw();

    vEventGenerator *eg = new vEventGenerator(); // event generator

    TFile *file = new TFile("ibdevt_source_tmp.root", "recreate");
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
    tree->Branch("L", &L, "L/D");

    tree2->Branch("pos_src", "TVector3", &pos_src);
    tree2->Branch("det", "vDetectorCylinder", &det);
    tree2->Fill();


    double wasted1 = 0;
    double wasted2 = 0;

    double Rd = det->GetRadius();
    double Hd = det->GetHeight();
    double Lmin = get_Lmin_cylinder(Rd, Hd, Xs, Zs);


    int last_i=0;
    string last_str;
    TTimeStamp ts0;
    t0 = ts0.GetSec() + 1e-9*ts0.GetNanoSec();

#ifdef __PROGRESSBAR_HPP
    progressbar bar(nevt);
#endif
    cout << "\e[?25l";

    for (int i=0; i<nevt; i++) {
        det->GetRandomPosition(x_det, y_det, z_det);
        
        vert = TVector3(x_det, y_det, z_det);
        uv = vert - pos_src;
        L = uv.Mag();
        uv *= 1./L;

        // MC #1 distance-flux distribution 
        if (gRandom->Uniform(1) > Lmin/L/L) {
            wasted1++;
            i--;
            continue; 
        }

        Ev = f_source->GetRandom(Emin, Emax);

        // MC #2 (3+1) neutrino oscillation 
        Pee = vosc->GetProbability(L, Ev, "e", "e"); 

        if (gRandom->Uniform(1) > Pee) {
            wasted2++;
            i--;
            continue; 
        }

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
    cout << "Wasted 1 (distance-flux) : " << wasted1 << endl;
    cout << "Wasted 2 (oscillation)   : " << wasted2 << endl;

    tree->Write();
    tree2->Write();
    file->Close();

    return 0;
}

void evtgen_source()
{
    main();
}


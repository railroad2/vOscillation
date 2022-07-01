#include "../src/vOscillating.cc"

void print_Pee(){
    vOscillating * vosc = new vOscillating();
    // vosc -> setdelta_CP(0);
    // double rad_13 = TMath::ASin(TMath::Sqrt(0.1))/2;
    // double rad_23 = TMath::ASin(TMath::Sqrt(0.97))/2;
    // double rad_12 = TMath::ASin(TMath::Sqrt(0.861))/2;
    // double theta_13 = 180 * rad_13 / TMath::Pi();
    // double theta_23 = 180 * rad_23 / TMath::Pi();
    // double theta_12 = 180 * rad_12 / TMath::Pi();
    //vosc -> settheta(theta_12, theta_13, theta_23);

    vosc -> loadstddata(true, false);

    cout << "|U_11| : " << vosc -> getPMNSmatrix(1, 1).Rho() << endl;
    cout << "|U_12| : " << vosc -> getPMNSmatrix(1, 2).Rho() << endl;
    cout << "|U_13| : " << vosc -> getPMNSmatrix(1, 3).Rho() << endl;
    cout << "|U_21| : " << vosc -> getPMNSmatrix(2, 1).Rho() << endl;
    cout << "|U_22| : " << vosc -> getPMNSmatrix(2, 2).Rho() << endl;
    cout << "|U_23| : " << vosc -> getPMNSmatrix(2, 3).Rho() << endl;
    cout << "|U_31| : " << vosc -> getPMNSmatrix(3, 1).Rho() << endl;
    cout << "|U_32| : " << vosc -> getPMNSmatrix(3, 2).Rho() << endl;
    cout << "|U_33| : " << vosc -> getPMNSmatrix(3, 3).Rho() << endl;
    
    // cout << " sin^2(2 theta_13) : " << TMath::Sin(2 * rad_13) * TMath::Sin(2 * rad_13) << endl;
    // cout << " sin^2(2 theta_23) : " << TMath::Sin(2 * rad_23) * TMath::Sin(2 * rad_23) << endl;
    // cout << " sin^2(2 theta_12) : " << TMath::Sin(2 * rad_12) * TMath::Sin(2 * rad_12) << endl;
    
    cout << " delta_CP : " << vosc -> getdelta_CP() << endl;

    TGraph * gPee = new TGraph;
    gPee -> SetName("P_e->e");
    TGraph * gPem = new TGraph;
    gPem -> SetName("P_e->m");
    TGraph * gPet = new TGraph;
    gPet -> SetName("P_e->t");
    TGraph * gPme = new TGraph;
    gPme -> SetName("P_m->e");
    TGraph * gPmm = new TGraph;
    gPmm -> SetName("P_m->m");
    TGraph * gPmt = new TGraph;
    gPmt -> SetName("P_m->t");
    TGraph * gPte = new TGraph;
    gPte -> SetName("P_t->e");
    TGraph * gPtm = new TGraph;
    gPtm -> SetName("P_t->m");
    TGraph * gPtt = new TGraph;
    gPtt -> SetName("P_t->t");
    

    for(int i = 0; i<500; i++){
        gPee -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "e", "e"));
        gPem -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "e", "mu"));
        gPet -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "e", "tau"));
        gPme -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "mu", "e"));
        gPmm -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "mu", "mu"));
        gPmt -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "mu", "tau"));
        gPte -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "tau", "e"));
        gPtm -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "tau", "mu"));
        gPtt -> SetPoint(i, 50 * i, vosc -> getProbability(50 * i, 1, "tau", "tau"));
    }
    
    gPee -> SetLineColor(1);
    gPem -> SetLineColor(2);
    gPet -> SetLineColor(3);
    gPme -> SetLineColor(1);
    gPmm -> SetLineColor(2);
    gPmt -> SetLineColor(3);
    gPte -> SetLineColor(1);
    gPtm -> SetLineColor(2);
    gPtt -> SetLineColor(3);

    TCanvas * can = new TCanvas("test", "", 1200, 860);
    can -> Divide(2, 2);

    can -> cd(1);
    TH1D * hFrame1 = new TH1D("hFrame1", "", 100, 0, 25000);
    hFrame1 -> GetXaxis() -> SetTitle("L/E (m/MeV)");
    hFrame1 -> GetYaxis() -> SetTitle("Survival Probability");
    hFrame1 -> GetYaxis() -> SetRangeUser(0, 1);
    hFrame1 -> GetXaxis()->SetTitleSize(0.047);
    hFrame1 -> GetYaxis()->SetTitleSize(0.047);
    hFrame1 -> GetXaxis()->SetTitleOffset(1.1);
    hFrame1 -> GetYaxis()->SetTitleOffset(1.1);
    hFrame1 -> GetXaxis()->CenterTitle();
    hFrame1 -> GetYaxis()->CenterTitle();
    hFrame1 -> GetXaxis()->SetLabelSize(0.038);
    hFrame1 -> GetYaxis()->SetLabelSize(0.038);
    hFrame1 -> Draw();
    
    gPee -> Draw("l");
    gPem -> Draw("l");
    gPet -> Draw("l");

    TLegend * leg1 = new TLegend();
    leg1 -> AddEntry("P_e->e", "P_e->e", "l");
    leg1 -> AddEntry("P_e->m", "P_e->m", "l");
    leg1 -> AddEntry("P_e->t", "P_e->t", "l");
    leg1 -> Draw();

    can -> cd(2);
    TH1D * hFrame2 = new TH1D("hFrame2", "", 100, 0, 25000);
    hFrame2 -> GetXaxis() -> SetTitle("L/E (m/MeV)");
    hFrame2 -> GetYaxis() -> SetTitle("Survival Probability");
    hFrame2 -> GetYaxis() -> SetRangeUser(0, 1);
    hFrame2 -> GetXaxis()->SetTitleSize(0.047);
    hFrame2 -> GetYaxis()->SetTitleSize(0.047);
    hFrame2 -> GetXaxis()->SetTitleOffset(1.1);
    hFrame2 -> GetYaxis()->SetTitleOffset(1.1);
    hFrame2 -> GetXaxis()->CenterTitle();
    hFrame2 -> GetYaxis()->CenterTitle();
    hFrame2 -> GetXaxis()->SetLabelSize(0.038);
    hFrame2 -> GetYaxis()->SetLabelSize(0.038);
    hFrame2 -> Draw();
    
    gPme -> Draw("l");
    gPmm -> Draw("l");
    gPmt -> Draw("l");

    TLegend * leg2 = new TLegend();
    leg2 -> AddEntry("P_m->e", "P_m->e", "l");
    leg2 -> AddEntry("P_m->m", "P_m->m", "l");
    leg2 -> AddEntry("P_m->t", "P_m->t", "l");
    leg2 -> Draw();
    
    can -> cd(3);
    TH1D * hFrame3 = new TH1D("hFrame3", "", 100, 0, 25000);
    hFrame3 -> GetXaxis() -> SetTitle("L/E (m/MeV)");
    hFrame3 -> GetYaxis() -> SetTitle("Survival Probability");
    hFrame3 -> GetYaxis() -> SetRangeUser(0, 1);
    hFrame3 -> GetXaxis()->SetTitleSize(0.047);
    hFrame3 -> GetYaxis()->SetTitleSize(0.047);
    hFrame3 -> GetXaxis()->SetTitleOffset(1.1);
    hFrame3 -> GetYaxis()->SetTitleOffset(1.1);
    hFrame3 -> GetXaxis()->CenterTitle();
    hFrame3 -> GetYaxis()->CenterTitle();
    hFrame3 -> GetXaxis()->SetLabelSize(0.038);
    hFrame3 -> GetYaxis()->SetLabelSize(0.038);
    hFrame3 -> Draw();
    
    gPte -> Draw("l");
    gPtm -> Draw("l");
    gPtt -> Draw("l");

    TLegend * leg3 = new TLegend();
    leg3 -> AddEntry("P_t->e", "P_t->e", "l");
    leg3 -> AddEntry("P_t->m", "P_t->m", "l");
    leg3 -> AddEntry("P_t->t", "P_t->t", "l");
    leg3 -> Draw();
}

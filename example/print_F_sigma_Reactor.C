#include "FluxCalculator.cc"


void print_F_sigma_Reactor(){
    gStyle->SetOptStat(kFALSE);

    CGenerator * gen = new CGenerator();
    double ff[4] = {0.568, 0.078, 0.297, 0.057};
    gen -> SetReactor(2.815, ff, 18000000);
    gen -> Initialization();

    vOscillating * vosc = new vOscillating();

    FluxCalculator * fc = new FluxCalculator();
    double Flux_const = fc -> integral_Flux_const(gen);
    double Flux_sigma_const = fc -> integral_sigma_Flux_const(gen);

    TGraph * gFlux = new TGraph();
    TGraph * gsigma = new TGraph();
    TGraph * gFS = new TGraph();

    gFlux -> SetLineColor(1);
    gsigma -> SetLineColor(2);
    gFS -> SetLineColor(3);
    
    double leftmax = 0.6 * 1e-3;
    double rightmax = 10 * 1e-42;
    double E;

    for(int i=0; i<500; i++){
        E = 20 * i;
        gFlux -> SetPoint(i, E, gen -> CalReactorNeutrinoFlux(E) / Flux_const);
        gsigma -> SetPoint(i, E, fc -> sigma_IBD(E / 1000) / rightmax * leftmax);
        gFS -> SetPoint(i, E, gen -> CalReactorNeutrinoFlux(E) * fc -> sigma_IBD(E / 1000) / Flux_sigma_const);
    }
    
    TCanvas * can = new TCanvas("test", "", 800, 600);

    TH1D * hFrame = new TH1D("hFrame", "", 100, 0, 10000);
    hFrame->GetXaxis()->SetTitle("Neutrino Energy (keV)");
    hFrame->GetYaxis()->SetTitle("Normalized E Spectrum (/keV)");
    hFrame->GetXaxis()->SetTitleSize(0.04);
    hFrame->GetYaxis()->SetTitleSize(0.04);
    hFrame->GetXaxis()->SetTitleOffset(1.1);
    hFrame->GetYaxis()->SetTitleOffset(1.1);
    hFrame->GetXaxis()->CenterTitle();
    hFrame->GetYaxis()->CenterTitle();
    hFrame->GetXaxis()->SetLabelSize(0.038);
    hFrame->GetYaxis()->SetLabelSize(0.038);
    hFrame->GetYaxis()->SetNdivisions(505);
    hFrame->GetYaxis()->SetRangeUser(0, leftmax);
    hFrame->Draw();

    gFlux -> Draw("l");
    gsigma -> Draw("l");
    gFS -> Draw("l");
    
    // draw an axis on the right side
    TGaxis * axis = new TGaxis(10000, 0, 10000, 0.6*1e-3, 
                           0, rightmax * 1e42, 510, "+L");
    axis->SetTitle("Cross Section (10^{-42} cm^{2})");
    axis->Draw();

}


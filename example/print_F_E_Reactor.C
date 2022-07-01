#include "FluxCalculator.cc"

void print_F_E_Reactor(){
    gStyle->SetOptStat(kFALSE);

    CGenerator * gen = new CGenerator();
    gen -> Initialization();

    vOscillating * vosc = new vOscillating();
    FluxCalculator*FC = new FluxCalculator();
    FC -> setint_N(5000);

    TGraph * gFlux_e = new TGraph();
    TGraph * gFlux_m = new TGraph();
    TGraph * gFlux_t = new TGraph();
    
    gFlux_e -> SetName("P_e->e");
    gFlux_m -> SetName("P_e->m");
    gFlux_t -> SetName("P_e->t");

    gFlux_e -> SetLineColor(1);
    gFlux_m -> SetLineColor(2);
    gFlux_t -> SetLineColor(3);
    
    for(int i=1; i<500; i++){
        gFlux_e -> SetPoint(i, 20 * i, gen -> CalReactorNeutrinoFlux(20 * i) * vosc -> getProbability(6000, 20 * i,"e", "e", true));
        gFlux_m -> SetPoint(i, 20 * i, gen -> CalReactorNeutrinoFlux(20 * i) * vosc -> getProbability(6000, 20 * i, "e", "mu", true));
        gFlux_t -> SetPoint(i, 20 * i, gen -> CalReactorNeutrinoFlux(20 * i) * vosc -> getProbability(6000, 20 * i, "e", "tau", true));
        cout << gen->CalReactorNeutrinoFlux(20*i) * vosc->getProbability(6000, 20*i, "e", "tau", true) << endl;
    }

    TCanvas * can = new TCanvas("test", "", 1200, 800);
    gPad -> SetLeftMargin(0.12);
    gPad -> SetBottomMargin(0.12);
    gPad -> SetRightMargin(0.08);
    gPad -> SetTopMargin(0.05);

    TH1D * hFrame = new TH1D("hFrame", "", 100, 0, 10000);
    hFrame->GetXaxis()->SetTitle("Neutrino Energy (keV)");
    hFrame->GetYaxis()->SetTitle("Reactor-#nu Flux (/cm^{2}/day/keV)");
    hFrame->GetXaxis()->SetTitleSize(0.047);
    hFrame->GetYaxis()->SetTitleSize(0.047);
    hFrame->GetXaxis()->SetTitleOffset(1.1);
    hFrame->GetYaxis()->SetTitleOffset(1.1);
    hFrame->GetXaxis()->CenterTitle();
    hFrame->GetYaxis()->CenterTitle();
    hFrame->GetXaxis()->SetLabelSize(0.038);
    hFrame->GetYaxis()->SetLabelSize(0.038);
    hFrame->GetYaxis()->SetNdivisions(505);
    hFrame->GetYaxis()->SetRangeUser(5, 3e14);
    hFrame->Draw();

    gFlux_e -> Draw("l");
    gFlux_m -> Draw("l");
    gFlux_t -> Draw("l");

    TLegend * leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg -> AddEntry("P_e->e", "P_{#bar{#nu_{e}}->#bar{#nu_{e}}}", "l");
    leg -> AddEntry("P_e->m", "P_{#bar{#nu_{e}}->#bar{#nu_{#mu}}}", "l");
    leg -> AddEntry("P_e->t", "P_{#bar{#nu_{e}}->#bar{#nu_{#tau}}}", "l");
    leg -> Draw();
}

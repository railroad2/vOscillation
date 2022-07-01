#include "FluxCalculator.cc"

void print_F_L_Reactor(){
    gStyle->SetOptStat(kFALSE);

    CGenerator * gen = new CGenerator();
    gen -> Initialization();

    vOscillating * vosc = new vOscillating();
    FluxCalculator * FC = new FluxCalculator();
    FC -> setint_N(5000);

    double Flux_thr = FC -> integral_Flux_const(gen);
    double sigma_Flux_thr = FC -> integral_sigma_Flux_const(gen);
    cout << "init sigma_Flux_thr : " << sigma_Flux_thr << endl;

    TGraph * gFlux_e = new TGraph();
    TGraph * gFlux_m = new TGraph();
    TGraph * gFlux_t = new TGraph();
    TGraph * gFlux_e_det = new TGraph();
    TGraph * gFlux_e_Kam = new TGraph();
    // TGraph * gFlux_m_det = new TGraph();
    // TGraph * gFlux_t_det = new TGraph();
    
    gFlux_e -> SetName("P_e->e");
    gFlux_m -> SetName("P_e->m");
    gFlux_t -> SetName("P_e->t");
    gFlux_e_det -> SetName("P_e->e_det");
    gFlux_e_Kam -> SetName("P_e->e_Kam");
    // gFlux_m_det -> SetName("P_e->m_det");
    // gFlux_t_det -> SetName("P_e->t_det");
    
    gFlux_e -> SetLineColor(1);
    gFlux_m -> SetLineColor(2);
    gFlux_t -> SetLineColor(3);
    gFlux_e_det -> SetLineColor(1);
    gFlux_e_Kam -> SetLineColor(2);
    // gFlux_m_det -> SetLineColor(2);
    // gFlux_t_det -> SetLineColor(3);

    for(int i=0; i<900; i++){
        gFlux_e -> SetPoint(i, 200 * i, FC -> integral_P_Flux(200 * i, "e", gen, vosc) / Flux_thr);
        gFlux_m -> SetPoint(i, 200 * i, FC ->integral_P_Flux(200 * i, "mu", gen, vosc) / Flux_thr);
        gFlux_t -> SetPoint(i, 200 * i, FC -> integral_P_Flux(200 * i, "tau", gen, vosc) / Flux_thr);
        gFlux_e_det -> SetPoint(i, 200 * i, FC -> integral_sigma_P_Flux(200 * i, "e", gen, vosc) / sigma_Flux_thr);
        // gFlux_m_det -> SetPoint(i, 200 * i, FC -> integral_sigma_P_Flux(200 * i, "mu", gen, vosc) / sigma_Flux_thr);
        // gFlux_t_det -> SetPoint(i, 200 * i, FC -> integral_sigma_P_Flux(200 * i, "tau", gen, vosc) / sigma_Flux_thr);
    }

    FC -> setint_a(3400);
    sigma_Flux_thr = FC -> integral_sigma_Flux_const(gen);
    cout << "second sigma_Flux_thr : " << sigma_Flux_thr << endl;
    for(int i=0; i<900; i++){
        gFlux_e_Kam -> SetPoint(i, 200 * i, FC -> integral_sigma_P_Flux(200 * i, "e", gen, vosc) / sigma_Flux_thr);
    }

    TCanvas * can = new TCanvas("test", "Reactor Neutrino Survival Probability", 1200, 800);
    gPad -> SetLeftMargin  (0.12);
    gPad -> SetBottomMargin(0.12);
    gPad -> SetRightMargin (0.08);
    gPad -> SetTopMargin   (0.05);

    can -> Divide(2,1);
    can -> cd(1);

    TH1D * hFrame1 = new TH1D("hFrame", "Reactor Neutrino Survival Probability", 100, 0, 100000);
    hFrame1 -> GetXaxis() -> SetTitle("L (m)");
    hFrame1 -> GetYaxis() -> SetTitle("Survival Probability");
    hFrame1 -> GetXaxis() -> SetTitleSize(0.04);
    hFrame1 -> GetYaxis() -> SetTitleSize(0.04);
    hFrame1 -> GetXaxis() -> SetTitleOffset(1.1);
    hFrame1 -> GetYaxis() -> SetTitleOffset(1.1);
    hFrame1 -> GetXaxis() -> CenterTitle();
    hFrame1 -> GetYaxis() -> CenterTitle();
    hFrame1 -> GetXaxis() -> SetLabelSize(0.038);
    hFrame1 -> GetYaxis() -> SetLabelSize(0.038);
    hFrame1 -> GetYaxis() -> SetRangeUser(0, 1);
    hFrame1 -> SetOption("AXIS");
    hFrame1 -> Draw();
    
    gFlux_e -> Draw("l");
    gFlux_m -> Draw("l");
    gFlux_t -> Draw("l");

    TLegend * leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg -> AddEntry("P_e->e", "P_{#bar{e}->#bar{e}}^{arr}", "l");
    leg -> AddEntry("P_e->m", "P_{#bar{e}->#bar{#mu}}^{arr}", "l");
    leg -> AddEntry("P_e->t", "P_{#bar{e}->#bar{#tau}}^{arr}", "l");
    leg -> Draw();

    can -> cd(2);

    TH1D * hFrame2 = new TH1D("hFrame", "Reactor Neutrino Detected Probability", 100, 0, 180000);
    hFrame2 -> GetXaxis() -> SetTitle("L (m)");
    hFrame2 -> GetYaxis() -> SetTitle("Detected Probability");
    hFrame2 -> GetXaxis() -> SetTitleSize(0.04);
    hFrame2 -> GetYaxis() -> SetTitleSize(0.04);
    hFrame2 -> GetXaxis() -> SetTitleOffset(1.1);
    hFrame2 -> GetYaxis() -> SetTitleOffset(1.1);
    hFrame2 -> GetXaxis() -> CenterTitle();
    hFrame2 -> GetYaxis() -> CenterTitle();
    hFrame2 -> GetXaxis() -> SetLabelSize(0.038);
    hFrame2 -> GetYaxis() -> SetLabelSize(0.038);
    hFrame2 -> GetYaxis() -> SetRangeUser(0, 1);
    hFrame2 -> SetOption("AXIS");
    hFrame2 -> Draw();
    
    gFlux_e_det -> Draw("l");
    gFlux_e_Kam -> Draw("l");
    // gFlux_m_det -> Draw("l");
    // gFlux_t_det -> Draw("l");

    TLegend * leg2 = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg2 -> AddEntry("P_e->e_det", "P_{#bar{e}->#bar{e}}^{det}", "l");
    leg2 -> AddEntry("P_e->e_Kam", "P_{#bar{e}->#bar{e}}^{det} with 3.4 MeV Threshold", "l");
    // leg2 -> AddEntry("P_e->m_det", "P_{#bar{e}->#bar{#mu}}^{det}", "l");
    // leg2 -> AddEntry("P_e->t_det", "P_{#bar{e}->#bar{#tau}}^{det}", "l");
    gStyle -> SetLegendTextSize(0.032);
    leg2 -> Draw();
}

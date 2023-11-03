#include "../header/vEventGenerator.hh"
#include "../header/vIBD.hh"
#include "../header/vInterpolator.hh"

vIBD* ibd = new vIBD();

TF1* vEventGenerator::GetFunctionTheta(double Ev)
{
    int ntheta = 180;
    double dtheta = TMath::Pi() / (ntheta-1);
    double theta = 0;

    vector<double> vtheta;
    vector<double> vsigdiff;

    for (int i=0; i<ntheta; i++) {
        vtheta.push_back(theta);
        vsigdiff.push_back(ibd->GetDifCrossSection(Ev, theta));
        theta += dtheta;
    }

    vInterpolator* interp = new vInterpolator(vtheta, vsigdiff);
    TF1* f1 = interp->GetTF1();
    f1->SetNormalized(1);

    return f1;
}

int vEventGenerator::GenerateIBD(double Ev, TLorentzVector &pv0, TLorentzVector &pe, TLorentzVector &pn, 
                                 TVector3 uv, double theta) 
{
    pv0.SetPxPyPzE(0., 0., Ev, Ev);
    TLorentzVector pp(0., 0., 0., MASSPROTON);

    TF1* ftheta = GetFunctionTheta(Ev);
    double phi = gRandom->Uniform(2.*TMath::Pi());  
    
    if (theta == -1) {
        theta = ftheta->GetRandom();
    }

    double Ee1 = ibd->GetEe1(Ev, theta);
    double pe1 = TMath::Sqrt(Ee1*Ee1 - MASSELECTRON*MASSELECTRON);

    TVector3 vpe; 
    vpe.SetMagThetaPhi(pe1, theta, phi);

    pe.SetVect(vpe);
    pe.SetE(Ee1);

    pn = pv0 - pe + pp;

    // recalculation of neutron energy
    pn.SetE(TMath::Sqrt(pn.P()*pn.P() + MASSNEUTRON*MASSNEUTRON));
    
    pv0.RotateUz(uv);
    pe.RotateUz(uv);
    pn.RotateUz(uv);

    return 0;
}



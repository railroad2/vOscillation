#ifndef VEVENTGENERATOR_HH
#define VEVENTGENERATOR_HH
// 

class vEventGenerator
{
public:
    vEventGenerator() {}
    ~vEventGenerator() {}

    int GenerateIBD(double Ev, TLorentzVector &pv0, TLorentzVector &pe, TLorentzVector &pn,
                    TVector3 uv=TVector3(1, 0, 0), double theta=-1); // neutrino energy in Ev
    TF1* GetFunctionTheta(double Ev);

private: 
};

#endif

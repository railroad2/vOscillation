#ifndef VEVENTGENERATOR_HH
#define VEVENTGENERATOR_HH
// 

class vEventGenerator
{
public:
    vEventGenerator() {}
    ~vEventGenerator() {}

    int GenerateIBD(double Ev, TVector3 uv=TVector3(1, 0, 0)); // neutrino energy in Ev
    TLorentzVector GetPv0() { return pv0; }
    TLorentzVector GetPv()  { return pv;  }
    TLorentzVector GetPe()  { return pe;  }
    TLorentzVector GetPn()  { return pn;  }

private: 
    TLorentzVector pv0;
    TLorentzVector pv;
    TLorentzVector pe;
    TLorentzVector pn;
};

#endif

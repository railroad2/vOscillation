#ifndef VSTERILEEE_HH
#define VSTERILEEE_HH


class vSterileEE
{
public:
    vSterileEE();
    virtual ~vSterileEE();

    // Main Method
    double GetProbability_SBL(double LoE) const;

    // DataLoader (Setter)
    double Gets22t14() const { return fS22t14; }
    double GetDm2_41() const { return fDm2_41; }
    void Sets22t14(double s22t14) { fS22t14 = s22t14; }
    void SetDm2_41(double dm2_41) { fDm2_41 = dm2_41; }

	double operator()(double* x, double* p)
	{
		double LoE = x[0];
		return GetProbability_SBL(LoE);
	}
    // Setter and Getter
private:
    double fS22t14;
    double fDm2_41; // eV^2
};

#endif

#ifndef VINTERPOLATOR_HH
#define VINTERPOLATOR_HH
// convert TH1 or x-y array to ROOT::Math::Interpolator 

class vInterpolator : public ROOT::Math::Interpolator 
{
public:
    vInterpolator(TH1 *h_in) {
        int i;
        double bc, bv;
        vector<double> xi, yi;
        //xi.push_back(0);
        //yi.push_back(0);
        
        for (i=0; i<h_in->GetNbinsX(); i++) {
            bc = h_in->GetBinCenter(i+1);
            bv = h_in->GetBinContent(i+1);
            xi.push_back(bc);
            yi.push_back(bv);
        }
        bmin_ = xi.front();
        bmax_ = xi.back();
        xi_ = xi;
        yi_ = yi;

        SetData(xi_, yi_);
    }

    vInterpolator(const vector<double> &x, const vector<double> &y) {
        bmin_ = x.front();
        bmax_ = x.back();
        xi_ = x;
        yi_ = y;

        SetData(xi_, yi_);
    }

    double operator () (double x) {
        double res = 0;

        if (x < bmin_ || x > bmax_)
            return 0;

        res = Eval(x);

        return (isnan(res) || isinf(res) ? 0 : res);
    }

    double operator () (double* x, double* p) {
        return operator()(x[0]);
    }

    vInterpolator(const vInterpolator & obj) { 
        bmin_ = obj.bmin_; 
        bmax_ = obj.bmax_; 
        SetData(obj.xi_, obj.yi_);
    }

    TF1* GetTF1() { 
        double (vInterpolator::*funcp)(double*, double*) = &vInterpolator::operator();
        return new TF1("", this, funcp, bmin_, bmax_, 0); 
    }

    double GetXmin() { return bmin_; }
    double GetXmax() { return bmax_; }

private:
    double bmin_;
    double bmax_;
    vector<double> xi_, yi_;

    bool isnan(double a) { return (a != a); }
    bool isinf(double a) { return !((a+1 != a) && (a == a)); }
};

#endif

#pragma once

#ifndef VCROSSSECTION_HH
#define VCROSSSECTION_HH

#include "vConstant.hh"


class vCrossSection
{
    public:
        vCrossSection() { mvConstant = new vConstant; }
        ~vCrossSection() { delete mvConstant; }
        double GetCrossSection_IBD(double E, int order=1);

    private:
        double GetCrossSection_IBD_zeroth(double E);
        double GetCrossSection_IBD_first(double E);
        double GetMomentum_Positron(double E);

        vConstant* mvConstant;
};
#endif

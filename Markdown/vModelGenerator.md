## vModelGenerator

vModelGenerator class is the class for calculation of distribution of detected signal of neutrino detection experiment.

It is considered the detector effect(energy resolution, position resoltion), the source effect(size effect) in this class.


--------------------

### How to use? (example : vModelGeneratorSterileEE)

``` C++
// Set expDays and Source Activity Information Setting

double expDays   = 500.;                        // day
double Activity  = 150. * 1.e3 * 3.7e10;        // ex) 150kCi (constant)
double int_Activ = Activity * expDays * 8.64e4; // integration of Activity


// Source Spatial Information Setting

vSourceCylinder* source = new vSourceCylinder();
double R_source = 0.085;
double H_source = 0.17;
source->SetRadius(R_source);
source->SetHeight(H_source);


// Detector Information Setting

double R_det       = 7.5;
double H_det       = 15;
double delta_X     = 9.5;
double delta_Z     = 0;
double ResolutionE = 0.05;
double ResolutionL = 0.12;

vDetectorCylinder* detector = new vDetectorCylinder();
detector->SetRadius(R_det);
detector->SetHeight(H_det);
detector->SetResolutionE(ResolutionE);
detector->SetResolutionL(ResolutionL);
detector->Initialization();


// Calculation of L_max
double Lmax = (double)(int)(delta_X + delta_Z + H_det / 2 + R_det) + 1.;


// Energy Spectrum TF assign

double Emin = 1.8;
double Emax = 3.0;
vCe144Spectrum* vbs = new vCe144Spectrum();
vbs->SetActivity(int_Activ);
vEnergySpectrum fobj = vEnergySpectrum(vbs, Emin, Emax);


// Set Sterile Model Parameter

vSterileEE* vst = new vSterileEE();
vst->Sets22t14(1.);
vst->SetDm2_41(Dm2list[i]);
vmg->SetSterileEE(vst);
vmg->Initialization();


// Set Model Generator Parameter

vModelGeneratorSterileEE* vmg = new vModelGeneratorSterileEE(detector, source, fobj);
vmg->SetDeltaX(delta_X);
vmg->SetDeltaZ(delta_Z);
vmg->Initialization();


int     binNum  = 500;
int64_t N       = 10000000;
int64_t iterNum;

TH1D* histL   = new TH1D("histL",   "", binNum, 0,    Lmax);
TH1D* histE   = new TH1D("histE",   "", binNum, Emin, Emax);
TH1D* histLoE = new TH1D("histLoE", "", binNum, 0,    Lmax / 1.5);
TH2D* histLE  = new TH2D("histLE",  "", binNum, 0, Lmax, binNum, 0, 2.5);

vmg->FillHistogram(histL, histE, histLoE, histLE, iterNum, N);

```


--------------------

### What is the calculation result?

Let consider a neutrino source and a detector with LABs(liquid alkylbenzenes) as LS(liquid scintillator).
The neutrino producted at random point of source fly to detector.
At detector, neutrino occurs an IBD(Inverse Beta Decay) and the positron producted.
This position deposits energy in LS and finally make two photons of 0.511 MeV.
By resolution effect, we cannot know the exact value of this energy(deposit energy + annihilation).

This class can calculate four distribution.
1. the distribution of detected flight distance of neutrinos.
2. the distribution of detected energy.
3. the distribution of L/E (L : detected flight distance of neutrinos, E : detected energy).
4. the 2-D distribution of (L,E).

For example, the distribution of detected energy can be calculated as

$\frac{d^2N}{dE_{det}dt}(E_{det}) = \frac{n_p}{4 \pi V_{source}} \int_0^{\infty} dE_{det} D(E_{det}, E) \sigma(E) \frac{d \Phi^o}{d E} \int_{source} d^3 X^{(s)} \int_{detector} d^3 X^{(d)} \frac{ P\left(\dfrac{r}{E}\right)}{r^2}$

,where

$\frac{d^2N}{dE_{det}dt}(E_{det})$ is the distribution of detected energy,
$n_p$ is the density of protons in the LS of the detectos,
$D(E_{det}, E)$ is the detector matrix, which contains the resolution information,
$\sigma(E)$ is the cross section of IBD,
$\frac{d \Phi^o}{d E}$ is the energy diffrential current of neutrino from source,
$r$ is the flight distance of neutrino, and
$P\left(\dfrac{r}{E}\right)$ is the survival probability of neutrinos.

This 7-dimensions integration is difficult to do analytically.
This class calculate this integration with Cutoff Method(Monte Carlo).
Therefore the equation of the above is changed as

$\int_{E_i}^{E_{i+1}} \frac{d^2 N}{dE_{det}dt} dE_{det} = \frac{F_i(E_{det})}{\text{iterNum}} \frac{N_p}{4 \pi r_{min}^2} \frac{A}{2} \int dE \sigma(E) f(E)$
,where
$A$ is the activity of neutrino source,
$f(E)$ is the distribution of energy of neutrino,
$iterNum$ is the number of loop iteration in the code,
$F_i(E_{det}) is the binContent of the histogram of detected energy.


--------------------

### How the resolution effect is calculated?

It is assumed that the relative energy resolution is proportional to the 1/sqrt(E).
Therefore the energy resolution is proportional to the sqrt(E).

Is is also assumed that the position resolution is proportional to the 1/sqrt(E).


--------------------
## Reference
>[1] JHEP 09 (2020) 178 [arXiv:2007.14792]

# vOscillating
This class is a Calculator class for Neutrino Oscillation.

This class need to be used with ROOT(CERN).


-----------------------
## How to download
> git clone https://github.com/jangddol/vOscillating.git


-----------------------
## Structure and Hierarchy
There are four classes : vOscillating, vCrossSection, vReactorFlux, vConstant

The file "vClass.hh" is not a class file.


-----------------------
## How to start
``` C++
#include "vClass.hh"

vOscillating* vosc = new vOscillating();
vReactorFlux* vrf = new vReactorFlux("HuberMueller"); // modelName (or "Gutlein")
vCrossSection* vcs = new vCrossSection();

```


-----------------------
## vOscillating
### How to get PMNS matrix elements
If you want to get PMNS matrix element with ith row and jth column, $U_{ij}$, then
``` C++
vOscillating * vosc = new vOscillating();
double element = vosc->getPMNSmatrix(i, j);
```


----------------------
### How to get Survival Probability
$P_{\alpha \xrightarrow{} \beta}(L) = \delta_{\alpha \beta}- 4 \sum_{j>i} \textrm{Re} \left( U_{\alpha i} U_{\beta i}^* U_{\alpha j}^* U_{\beta j} \right) \sin^2 \left( \frac{\Delta m_{ji}^2 L}{4 E} \right) + 2 \sum_{j>i} \textrm{Im} \left( U_{\alpha i} U_{\beta i}^* U_{\alpha j}^* U_{\beta j} \right) \sin \left( \frac{\Delta m_{ji}^2 L}{2 E} \right)$

If you want to get Survival Probability $P(\nu_e -> \nu_\mu)$ of Neutrino with Energy $E$ and flight length $L$, then
``` C++
vOscillating * vosc = new vOscillating();
double  L        = 10000; // unit : m
double  E        = 2;     // unit : MeV
TString iflavour = "e";   // "e" or "mu" or "tau"
TString fflavour = "mu";
bool    anti     = false;
double probability = vosc->getProbability(L, E, iflavour, fflavour, anti);
```


---------------------
### How to change paramters : $\theta_{ij}, \Delta m_{ji}^2, \delta_{CP}$
In this class, $\Delta m_{32}^2$ is defined as:

$\Delta m_{32}^2 = \Delta m_{31}^2 - \Delta m_{21}^2$

You can change the parameters with setter and getter.

Please read the header file.


--------------------
### 4 Standard Parameter Data
In vOscillating class, there are 6 standard Parameter data[1][2] : 
1. PDG data
    1-1. Normal Ordering 
    1-2. Inverted Ordering
2. NuFit data
    2-1. Normal Ordering, SK atmospheric data not considered.
    2-2. NOrmal Ordering, SK atmospheric data considered.
    2-3. Inverted Ordering, SK atmospheric data not considered. 
    2-4. Inverted Ordering, SK atmospheric data considered.

You can select one of these data:
```C++
vOscillating * vosc = new vOscillating();
vosc->LoadStdData_PDG(false); // PDG data, Inverted Ordering = false.
vosc->LoadStdData_PDG(true); // PDG data, Inverted Ordering = true.
vosc->LoadStdData_NuFit(false, false); // NuFit data, Inverted Ordering = false, SK considering = false.
vosc->LoadStdData_NuFit(false, true); // NuFit data, Inverted Ordering = false, SK considering = true.
vosc->LoadStdData_NuFit(true, false); // NuFit data, Inverted Ordering = true, SK considering = false.
vosc->LoadStdData_NuFit(true, true); // NuFit data, Inverted Ordering = true, SK considering = true.
```


--------------------
## vReactorFlux
### How to set the reactor properties : ThermalPower, Distance to Detector, Fission Fraction, Released Energy

```C++
vReactorFlux* vrf = new vReactorFlux("HuberMueller"); // or "Gutlein" (not recommended) [3][4][5]
vrf->SetDistance(2000); // unit : m , default : 60000
vrf->SetThermalPower(14); // unit : GWth, default : 16.85(Hanul reactors, Korea)
std::vector<double> ff = {0.3, 0.4, 0.1, 0.2};
vrf->SetFissionFraction(ff); // default : {0.5, 0.1, 0.3, 0.1}
std::vector<double> re = {200, 200, 200, 200};
vrf->SetReleasedEnergy(re); // default : in source code
```


--------------------
### How to get Neutrino Flux from Reactor

```C++
vReactorFlux* vref = new vReactorFlux("HuberMuller");
double E = 3; // Neutrino Energy, unit : MeV
double flux = vref->GetReactorNeutrinoFlux(E);
```


--------------------
## vCrossSection
### How to get Cross Section of IBD 
Reference : [6]

```C++
vCrossSection* vcs = new vCrossSection();
double E_nu = 3; // Neutrino Energy, unit : MeV
double sigma = vcs->GetCrossSection_IBD(E_nu);
```


--------------------
### How to get Cross Section of neutrino-electron scattering
Reference : [7]

```C++
vCrossSection* vcs = new vCrossSection();
double E_nu = 3; // Neutrino energy, unit : MeV
double T_re = 2; // Recoiled electron kinetic energy, unit : MeV
TString flavour = "e"; // Neutrino flavour, "e", "mu", or "tau"
double sigma = vcs->GetCrossSection_IBD(E_nu, T_re, flavour);
```


## Reference
>[1] JHEP 09 (2020) 178 [arXiv:2007.14792]

>[2] NuFIT 5.1 (2021), www.nu-fit.org

>[3] A. Gutlein, Feasibility study for a first observation of coherent neutrino necleus scattering using low-temperature detectors

>[4] Mueller, T. A., et al. (2011). Improved predictions of reactor antineutrino spectra. Physical Review C, 83(5). https://doi.org/10.1103/physrevc.83.054615

>[5] Huber, P. (2011). Determination of antineutrino spectra from nuclear reactors. Physical Review C, 84(2). https://doi.org/10.1103/physrevc.84.024617

>[6] Vogel P., Beacom J. F. 1999 Phys. Rev. D 60 53003

>[7] 't Hooft, G., 1971,Phys. Lett. B 37, 195.

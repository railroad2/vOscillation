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
vReactorFlux* vref = new vReactorFlux("Gutlein"); // modelName (or "HuberMuller")
vCrossSection* vcrs = new vCrossSection();

```


-----------------------
## vOscillating : How to get PMNS matrix elements
If you want to get PMNS matrix element with ith row and jth column, $U_{ij}$, then
``` C++
vOscillating * vosc = new vOscillating();
double element = vosc->getPMNSmatrix(i, j);
```


----------------------
## vOscillating : How to get Survival Probability
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
## vOscillating : How to change paramters : $\theta_{ij}, \Delta m_{ji}^2, \delta_{CP}$
In this class, $\Delta m_{32}^2$ is defined as:

$\Delta m_{32}^2 = \Delta m_{31}^2 - \Delta m_{21}^2$

You can change the parameters with setter and getter.

Please read the header file.


--------------------
## vOscillating : 4 Standard Parameter Data
In vOscillating class, there are 4 standard Parameter data[1][2] : 
1. Normal Ordering, no considering SK atmosperic data 
2. Normal Ordering, considering SK atmosperic data 
3. Inverse Ordering, no considering SK atmosperic data 
4. Inverse Ordering, considering SK atmosperic data 

You can select one of these data:
```C++
vOscillating * vosc = new vOscillating();
vosc -> loadstddata(true, true); // Inverse Ordering = true, considering SK data = true
```


--------------------
## vReactorFlux : How to set the reactor properties : ThermalPower, Distance to Detector, Fission Fraction, Released Energy

```C++
vReactorFlux* vref = new vReactorFlux("HuberMuller"); // or "Gutlein" (not recommended) [3][4][5]
vref->SetDistance(2000); // unit : m , default : 60000
vref->SetThermalPower(14); // unit : GWth, default : 16.85(Hanul reactors, Korea)
std::vector<double> ff = {0.3, 0.4, 0.1, 0.2};
vref->SetFissionFraction(ff); // default : {0.5, 0.1, 0.3, 0.1}
std::vector<double> re = {200, 200, 200, 200};
vref->SetReleasedEnergy(re); // default : in source code
```


--------------------
## vReactorFlux : How to get Neutrino Flux from Reactor

```C++
vReactorFlux* vref = new vReactorFlux("HuberMuller");
double E = 3; // Neutrino Energy, unit : MeV
double flux = vref->GetReactorNeutrinoFlux(E);
```


--------------------
## vCrossSection : How to get Cross Section of IBD 
Reference : [6]

```C++
vCrossSection* vcs = new vCrossSection();
double E_nu = 3;
double sigma = vcs->GetCrossSection_IBD(E_nu);
```


## Reference
>[1] JHEP 09 (2020) 178 [arXiv:2007.14792]

>[2] NuFIT 5.1 (2021), www.nu-fit.org

>[3]A. Gutlei, Feasibility study for a first observation of coherent neutrino necleus scattering using low-temperature detectors

>[4]Mueller, T. A., et al. (2011). Improved predictions of reactor antineutrino spectra. Physical Review C, 83(5). https://doi.org/10.1103/physrevc.83.054615

>[5]Huber, P. (2011). Determination of antineutrino spectra from nuclear reactors. Physical Review C, 84(2). https://doi.org/10.1103/physrevc.84.024617

>[6]Vogel P., Beacom J. F. 1999 Phys. Rev. D 60 53003

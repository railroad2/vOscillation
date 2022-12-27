## vEnergySpectrum

This class is the class for the calculation of multiplication of cross section and neutrino energy spectrum.


--------------------

### Code Example

``` C++
vCe144Spectrum* vbs = new vCe144Spectrum(); // has inheritance from vNeutrinoSpectrum
vbs->SetActivity(int_Activ);

double Emin = 1.8;
double Emax = 3.0;

vEnergySpectrum fobj = vEnergySpectrum(vbs, Emin, Emax);
```


--------------------

### vIBD
This class is for the cross section of inverse beta decay(IBD)[1].
This class is not used by customers.


--------------------

### vNeutrinoSpectrum
This class is for the energy spectrum of neutrinos from the source.
There is two child classes : vBetaSpectrum and vReactorFlux.
You can also make new child class for your purposes.

--------------------

### vBetaSpectrum
This class is for the energy spectrum of neutrinos from the beta decay (also beta+ decay).

$ Spectrum ~ FpE_e(Q-T)^2 $

$ F = frac{2 \pi \eta}{1 - \text{exp}\left( -2 \pi \eta \right) $

$ eta = \pm\frac{Z_f \alpha E_e}{p} $ (plus : beta decay, minus : beta+ decay)



--------------------

### vReactorFlux
This class is for the energy spectrum of neutrinos from the beta decay (also beta+ decay).


--------------------

#### Code Example
```C++
vReactorFlux* vrf = new vReactorFlux("HuberMueller"); // or "Gutlein" (not recommended) [2][3][4]
vrf->SetDistance(2000); // unit : m , default : 60000
vrf->SetThermalPower(14); // unit : GWth, default : 16.85(Hanul reactors, Korea)
std::vector<double> ff = {0.3, 0.4, 0.1, 0.2};
vrf->SetFissionFraction(ff); // default : {0.5, 0.1, 0.3, 0.1}
std::vector<double> re = {200, 200, 200, 200};
vrf->SetReleasedEnergy(re); // default : in source code
```


--------------------

## Reference
>[1] Vogel P., Beacom J. F. 1999 Phys. Rev. D 60 53003

>[2] A. Gutlein, Feasibility study for a first observation of coherent neutrino necleus scattering using low-temperature detectors

>[3] Mueller, T. A., et al. (2011). Improved predictions of reactor antineutrino spectra. Physical Review C, 83(5). https://doi.org/10.1103/physrevc.83.054615

>[4] Huber, P. (2011). Determination of antineutrino spectra from nuclear reactors. Physical Review C, 84(2). https://doi.org/10.1103/physrevc.84.024617



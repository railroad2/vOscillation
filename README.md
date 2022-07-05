# vOscillating
Calculator class for Neutrino Oscillation.

-----------------------
## How to get PMNS matrix element
If you want to get PMNS matrix element with ith row and jth column, $U_{ij}$, then
``` C++
vOscillating * vosc = new vOscillating();
double element = vosc->getPMNSmatrix(i, j);
```

----------------------
## How to get Survival Probability
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
## How to change paramters $\theta_{ij}, \Delta m_{ji}^2, \delta_{CP}$
You can change the parameters with setter and getter.
Please read the header file.

--------------------
## 4 Standard Parameter Data
In vOscillating class, there are 4 standard Parameter data : 
1. Normal Ordering, no considering SK atmosperic data 
2. Normal Ordering, considering SK atmosperic data 
3. Inverse Ordering, no considering SK atmosperic data 
4. Inverse Ordering, considering SK atmosperic data 

You can select one of these data:
```C++
vOscillating * vosc = new vOscillating();
vosc -> loadstddata(true, true); // Inverse Ordering = true, considering SK data = true
```

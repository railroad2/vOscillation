## vOscillating

vOscillating class is the class that contains methods to get PMNS matrix and Neutrino Survival Probability.

PMNS matrix is a unitary matrix that representate the mismatch of flavor eigenstate and mass eigenstate of the neutrinos : 

$\nu_\alpha = U_{\alpha i} \nu_i$

$|\nu_\alpha \rangle = U^*_{\alpha i} |\nu_i \rangle$

where $\alpha = e, \mu, \tau$, and $i = 1, 2, 3$.

### How to get PMNS matrix elements
If you want to get PMNS matrix element with ith row and jth column, $U_{ij}$, then
``` C++
vOscillating* vosc = new vOscillating();
double element = vosc->GetPMNSmatrix(i, j);
```

-----------------------

### How to get Survival Probability
$P_{\alpha \xrightarrow{} \beta}(L) = \delta_{\alpha \beta}- 4 \sum_{j>i} \textrm{Re} \left( U_{\alpha i} U_{\beta i}^* U_{\alpha j}^* U_{\beta j} \right) \sin^2 \left( \frac{\Delta m_{ji}^2 L}{4 E} \right) + 2 \sum_{j>i} \textrm{Im} \left( U_{\alpha i} U_{\beta i}^* U_{\alpha j}^* U_{\beta j} \right) \sin \left( \frac{\Delta m_{ji}^2 L}{2 E} \right)$

If you want to get Survival Probability $P(\nu_e -> \nu_\mu)$ of Neutrino with Energy $E$ and flight length $L$, then
``` C++
vOscillating* vosc = new vOscillating();
vosc->LoadStdData(); // load PDG parameters of neutrino oscillation.
double  L        = 10000; // unit : m
double  E        = 2;     // unit : MeV
TString iflavour = "e";   // "e" or "mu" or "tau"
TString fflavour = "mu";
bool    anti     = false;
double probability = vosc->GetProbability(L, E, iflavour, fflavour, anti);
```

-----------------------

### How to change paramters : $\theta_{ij}, \Delta m_{ji}^2, \delta_{CP}$
In this class, $\Delta m_{32}^2$ is defined as:

$\Delta m_{32}^2 = \Delta m_{31}^2 - \Delta m_{21}^2$

You can change the parameters with setter and getter.

Please read the header file.

-----------------------

### 4 Standard Parameter Data
In vOscillating class, there are 6 standard Parameter data[1] : 
1. PDG data - Normal Ordering 
2. PDG data - Inverted Ordering

You can select one of these data:
```C++
vOscillating* vosc = new vOscillating();
vosc->LoadStdData(false); // PDG data, Inverted Ordering = false
vosc->LoadStdData(true); // PDG data, Inverted Ordering = true
```


--------------------
## Reference
>[1] JHEP 09 (2020) 178 [arXiv:2007.14792]

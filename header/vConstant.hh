#ifndef VCONSTANT_HH
#define VCONSTANT_HH


constexpr static double MASSELECTRON = 0.51099895000; // (15) MeV/c^2
constexpr static double MASSPROTON   = 938.27208816; // (29) MeV/c^2
constexpr static double MASSNEUTRON  = 939.56542052; // (54) MeV/c^2
constexpr static double MASSDALTON   = 931.49410242; // (28) MeV/c^2 
constexpr static double MASSDELTA = 1.29333236; // M_n - M_p, calculated from the above values
constexpr static double GUTLEINCONSTANT[3][5] = { { 1.72254, 10.5200, 896.017, 1054.50, 945.390 },
												  { 10.4669, 25.1948, 854.174, 856.805, 864.198 },
												  { 1.52535, 10.3982, 799.199, 938.927, 842.464 } };
constexpr static double HUBERMUELLERCONSTANT[4][6] = { { 4.367, -4.577,   2.100,  -0.5294,   0.06186,  -0.002777  }, // Huber Data
													   { 0.4833, 0.1927, -0.1283, -0.006762, 0.002233, -0.0001536 }, // Mueller Data
													   { 4.757, -5.392,   2.563,  -0.6596,   0.07820,  -0.003536  }, // Huber Data
													   { 2.990, -2.882,   1.278,  -0.3343,   0.03905,  -0.001754  } }; // Huber Data


#endif
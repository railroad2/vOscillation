#include "../header/vModelGenerator.hh"


double vModelGenerator::CalculateL(double x, double y, double z)
{
	return TMath::Sqrt(x * x + y * y + z * z);
}
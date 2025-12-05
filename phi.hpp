#pragma once
#include <cmath>

#ifndef M_E
    #include <corecrt_math_defines.h>
#endif

extern const int N;

extern const double pmax;
extern const double pmin;
extern const double p0;
extern const double pi;

extern double a;
extern double b;

double phi(double V, double k);
double Iphi(double p, double k);
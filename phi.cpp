#include "phi.hpp"

double a = (pmax-pmin)*(N-1)*p0/pi;
double b = std::log(1/p0 - 1);

double phi(double V){
    double f = V;
    f /= a;
    f -= b;

    double g = 1 + std::pow(M_E, -f);
    g = 1/g;

    g-= p0;

    return g;
}

double Iphi(double p){
    double g = 1/p;
    g -= 1;
    g+= p0;

    double f = -std::log(g);
    f += b;
    f *= a;

    return f;
}
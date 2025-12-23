#include "distributions.hpp"
using namespace std;

double normal_cdf(double x, double mu, double sigma) {
    return 0.5 * (1.0 + std::erf((x - mu) / (sigma * std::sqrt(2.0))));
}

double exp_cdf(double x, double lambda){
    return 1 - pow(M_E, -lambda*x);
}
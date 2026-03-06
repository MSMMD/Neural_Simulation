#include "histogram.hpp"

long double Standard_Deviantion(long double *TMN, int n){
    long double sd=0;
    for(int i=0; i<n; i++)
        sd += (TMN[i]-1)*(TMN[i]-1)/n;

    return sd;
}

long double Scotts_Rule(long double sd, int n){
    return 3.49*sd / pow(n, 1/3);
}

long double Freedman_Diaconis(long double *TMN, int n){
    int vq1 = std::round(n/4);
    int vq3 = std::round(3*n/4);
    long double q1 = TMN[vq1];
    long double q3 = TMN[vq3];

    long double iqr = q3 - q1;

    return 0.1*iqr / pow(n, 1/3);
}
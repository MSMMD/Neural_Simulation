#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

long double Standard_Deviantion(long double *TMN, int n);
long double Scotts_Rule(long double sd, int n);
long double Freedman_Diaconis(long double *TMN, int n);
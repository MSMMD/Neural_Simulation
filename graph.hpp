#pragma once

#include <stdlib.h>
#include <random>
#include <vector>

extern const double pmax;
extern const double pmin;

std::vector <std::pair<int, double>>* construct(int seed, int N);
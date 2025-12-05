#include "graph.hpp"


std::vector <std::pair<int, double>>* construct(int seed, int N){
    std::vector <std::pair<int, double>> *viz = (std::vector <std::pair<int, double>>*) calloc(N, sizeof(std::vector <std::pair<int, double>>));

    std::mt19937 mat(seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i==j) continue;
                
            double peso;// = 1;

            /*
                +1: 50%
                0: 20%
                -1: 30%
            */
            double U = dist(mat);
            if(U<pmin) peso = -1;
            else if(U<1-pmax) peso = 0;
            else peso = 1;
                    
            if(peso) viz[i].push_back({j, peso}); // w_(j→i) = peso;
        }
    }

    return viz;
}
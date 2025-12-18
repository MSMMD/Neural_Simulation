#include <bits/stdc++.h>
#include <cmath>

#include "phi.hpp"
#include "graph.hpp"

using namespace std;

const int n = 300;
const int N = 300;
const double rho = 0.79;
double V[N];

const double pmax = 1;
const double pmin = 0;
const double p0 = 0.05;
const double pi = 0.2;


int main(){
    int M=100;
    int seed = 0;

    std::vector <std::pair<int, double>>* viz = construct(1, N);
    
    cout.precision(5);
    double MVm = 0;
    long long Tot_MVm = 0;
    
    double Tot_TM=0;
    double Tempos_de_mortes_normalizado[M];
    
    ofstream data_TM("./output/plot_TM.dat");
    data_TM << "# Longevidade\tQuantidade\n";
    

    while(seed<M){
        
        double V_inicial = Iphi(pi);
        for(int i=0; i<N; i++) V[i] = V_inicial;
        
        ofstream data_Phi("./output/plot_Phi.dat");
        data_Phi << "# x\tPhi\n";
        for(double i=-100; i<1000; i+=0.2)
            data_Phi<<i<<"\t"<<phi(i)<<"\n";
        
        //ofstream data_pm("./output/plot_pm.dat");
        //data_pm << "# Tempo\tProbabilidade\n";
        
        //ofstream data_Vm("./output/plot_Vm.dat");
        //data_Vm << "# Tempo\tPotencial\n";
        
        
        int t=1;
        bool Esta_Morto = 0;
        
        mt19937 gen(seed);
        uniform_real_distribution<double> dist(0.0, 1.0);
        while(Esta_Morto==0){
            Esta_Morto = 1;
            
            double vmax=V_inicial;
            int X[N];
            int disparos=0;
            
            for(int i=0; i<N; i++){
                double Ui = dist(gen);
                double phiVi = phi(V[i]);
                    
                if(Ui < phiVi) X[i] = 1;
                else X[i] = 0;
            }
            
            for(int i=0; i<N; i++){
                V[i] *= rho;
                if(X[i] == 0){
                    for(auto p: viz[i]){
                        if(X[p.first]==1) V[i] += p.second;
                    }
                }
            }
            for(int i=0; i<N; i++){
                if(X[i] == 1){
                    V[i] = 0;
                    disparos++;
                }

                if(phi(V[i]) > 0.0001) Esta_Morto = 0;
            }

            double Vm = 0;
            for(int i=0; i<N; i++){
                Vm += V[i];
                vmax = max(V[i], vmax);
            }
            Vm /= N;
            MVm += Vm;
            Tot_MVm++;

            cout<<"Quant. de disparos: "<<disparos<<"\t| Vm="<<Vm<<" phi(Vm)="<<phi(Vm)<<"\t| Vmax="<<vmax<<" phi(Vmax)="<<phi(vmax)<<endl;

            t++;
        }
    
        cout<<"Tempo até morrer: "<< t <<"\tSeed: "<<seed<<endl;
        Tempos_de_mortes_normalizado[seed] = t;
        Tot_TM += Tempos_de_mortes_normalizado[seed];
        seed++;
    }
    
    for(int i=0; i<M; i++){
        Tempos_de_mortes_normalizado[i] *= M/Tot_TM;
        //cout<<Tempos_de_mortes_normalizado[i]<<endl;
    }
    
    map<double, double> quantidades;
    for(int i=0; i<M; i++){
        if(!quantidades[Tempos_de_mortes_normalizado[i]]) quantidades[Tempos_de_mortes_normalizado[i]] = 1;
        else quantidades[Tempos_de_mortes_normalizado[i]] += 1;
    }
    
    for(auto p:quantidades){
        data_TM<<p.first<<"\t"<<p.second<<"\n";
    }
    //data_pm.close();
    //data_Vm.close();
    

    free(viz);
    return 0;
}
#include <bits/stdc++.h>
#include <cmath>

#include "phi.hpp"
#include "graph.hpp"

using namespace std;

const int n = 1000;
const int N = 800;
const double rho = 0.95;
double V[N];

const double pmax = 0.2;
const double pmin = 0.05;
const double p0 = 0.05;
const double pi = 0.2;


int main(){
    int seed = 0;

    std::vector <std::pair<int, double>>* viz = construct(1, N);

    double MVm = 0;
    long long Tot_MVm = 0;

    mt19937 gen(seed);
    uniform_real_distribution<double> dist(0.0, 1.0);

    double V_inicial = Iphi(pi);
    for(int i=0; i<N; i++) V[i] = V_inicial;
    double vmax=V_inicial, vmin=V_inicial;

    cout.precision(5);

    ofstream data_disparos("./output/plot_disp.dat");
    data_disparos << "# Tempo\tDisparos\n";

    ofstream data_Vm("./output/plot_Vm.dat");
    data_Vm << "# Tempo\tPotencial\n";
    
    
    for(int t=1; t<=n; t++){
        
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
        }
        double Vm = 0;
        for(int i=0; i<N; i++){
            Vm += V[i];
            vmax = max(V[i], vmax);
            vmin = min(V[i], vmin);
        }
        Vm /= N;
        MVm += Vm;
        Tot_MVm++;
        cout<<"Quant. de disparos: "<<disparos<<", Vm: "<<Vm<<" | phi(Vm)="<<phi(Vm)<<endl;
        data_disparos << t << "\t" << disparos << "\n";
        data_Vm << t << "\t" << Vm << "\n";
    }

    cout<<"V minimo: "<<vmin<<endl;
    cout<<"V maximo: "<<vmax<<endl;
    cout<<"Media dos Vm ate agr: "<<MVm/Tot_MVm<<" | Phi:"<< phi(MVm/Tot_MVm)<<endl;
    
    data_disparos.close();
    data_Vm.close();


    free(viz);
    return 0;
}
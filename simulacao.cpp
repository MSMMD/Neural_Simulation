#include <bits/stdc++.h>
#include <cmath>

#include "phi.hpp"
#include "graph.hpp"
#include "distributions.hpp"
#include "histogram.hpp"

using namespace std;

const int n = 300;
const int N = 300;
double rho = 0.785;
long double V[N];

const double pmax = 1;
const double pmin = 0;
const double p0 = 0.05;
const double pi = 0.2;

int main(){
    int seed = 1;
    cout<<"Seed: ";
    cin>>seed;
    cout<<"Rho: ";
    cin>>rho;

    std::vector <std::pair<int, double>>* viz = construct(1, N);
    
    /*
    ofstream data_TM("./output/Tempos_de_Morte.dat");
    data_TM << "# Longevidade\n";
    ofstream data_TM_Hist("./output/plot_TM_Hist.dat");
    data_TM_Hist << "# Longevidade\tQuantidade\n";
    ofstream data_TM_Acumulado("./output/plot_TM_Acumulado.dat");
    data_TM_Acumulado << "# Longevidade\tQuantidade\n";
    
    ofstream data_Phi("./output/plot_Phi.dat");
    data_Phi << "# x\tPhi\n";
    for(double i=-100; i<1000; i+=0.2)
        data_Phi<<i<<"\t"<<phi(i)<<"\n";
    data_Phi.close();

    ofstream data_Exp("./output/plot_Exp.dat");
    data_Exp << "# x\tExp\n";
    for(double i=0; i<10; i+=0.01)
    data_Exp<<i<<"\t"<<exp_cdf(i, 1.0)<<"\n";
    data_Exp.close();
    
    ofstream data_Exp("./output/plot_Exp_Dist.dat");
    data_Exp << "# x\tExp\n";
    for(double i=0; i<10; i+=0.01)
        data_Exp<<i<<"\t"<<exp_dist(i, 1.0)<<"\n";
    data_Exp.close();
    
    ofstream data_Norm("./output/plot_Norm.dat");
    data_Norm << "# x\tNorm\n";
    for(double i=0; i<=2.5; i+=0.001)
    data_Norm<<i<<"\t"<<normal_cdf(i, 1, 0.17)<<"\n";
    data_Norm.close();
    */

    long double V_inicial = Iphi(pi);
    for(int i=0; i<N; i++) V[i] = V_inicial;
        
        
    //ofstream data_pm("./output/plot_pm.dat");
    //data_pm << "# Tempo\tProbabilidade\n";
        
    ofstream data_Vm("./output/plot_Vm.dat");
    data_Vm << "# Tempo\tPotencial\n";
    data_Vm<<0<<"\t"<<V_inicial<<"\n";
        
        
    int t=0;
    bool Esta_Morto = 0;
        
    mt19937 gen(seed);
    uniform_real_distribution<long double> dist(0.0, 1.0);
    while(Esta_Morto==0){
        t++;
        Esta_Morto = 1;
        
        int X[N];
        int disparos=0;
        
        for(int i=0; i<N; i++){
            long double Ui = dist(gen);
            long double phiVi = phi(V[i]);
            
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
        
        long double Vm = 0;
        for(int i=0; i<N; i++){
            Vm += V[i];
        }
        Vm /= N;
        data_Vm<<t<<"\t"<<Vm<<"\n";

        cout<<"Seed: "<<seed<<" Tempo: "<<t<<"\t| "<<"Quant. de disparos: "<<disparos<<"\t| Vm="<<Vm<<" phi(Vm)="<<phi(Vm)<<endl;
    }

    //data_TM.close();
    //data_TM_Hist.close();
    //data_TM_Acumulado.close();
    //data_pm.close();
    data_Vm.close();
    

    free(viz);
    return 0;
}
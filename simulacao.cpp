#include <bits/stdc++.h>
#include <cmath>

#include "phi.hpp"
#include "graph.hpp"

using namespace std;

const int n = 300;
const int N = 300;
double rho = 0.7;
long double V[N];

const double pmax = 1;
const double pmin = 0;
const double p0 = 0.05;
const double pi = 0.2;


int main(){
    int M=400;
    int seed = 1;
    cin>>rho;

    std::vector <std::pair<int, double>>* viz = construct(1, N);
    
    cout.precision(5);
    long double MVm = 0;
    long long Tot_MVm = 0;
    
    long double Tot_TM=0;
    long double Tempos_de_mortes_normalizado[M];
    
    ofstream data_TM("./output/Tempos_de_Morte.dat");
    data_TM << "# Longevidade\n";
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
        data_Exp<<i<<"\t"<<1 - pow(M_E, -i)<<"\n";
    data_Exp.close();

    for(int j=0; j<M; j++){
        
        long double V_inicial = Iphi(pi);
        for(int i=0; i<N; i++) V[i] = V_inicial;
        
        
        //ofstream data_pm("./output/plot_pm.dat");
        //data_pm << "# Tempo\tProbabilidade\n";
        
        //ofstream data_Vm("./output/plot_Vm.dat");
        //data_Vm << "# Tempo\tPotencial\n";
        
        
        int t=1;
        bool Esta_Morto = 0;
        
        mt19937 gen(seed);
        uniform_real_distribution<long double> dist(0.0, 1.0);
        while(Esta_Morto==0){
            Esta_Morto = 1;
            
            long double vmax=V_inicial;
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
                vmax = max(V[i], vmax);
            }
            Vm /= N;
            MVm += Vm;
            Tot_MVm++;

            //cout<<"Seed: "<<seed<<" Tempo: "<<t<<"\t| "<<"Quant. de disparos: "<<disparos<<"\t| Vm="<<Vm<<" phi(Vm)="<<phi(Vm)<<"\t| Vmax="<<vmax<<" phi(Vmax)="<<phi(vmax)<<endl;

            t++;
        }
    
        cout<<"Tempo até morrer: "<< t <<"\tSeed: "<<seed<<endl;
        Tempos_de_mortes_normalizado[seed] = t;
        Tot_TM += Tempos_de_mortes_normalizado[seed];
        seed++;

        //cout<<"contiuar?"<<endl;
        //cin.get();
    }
    
    for(int i=0; i<M; i++){
        Tempos_de_mortes_normalizado[i] *= M/Tot_TM;
        //cout<<Tempos_de_mortes_normalizado[i]<<endl;
    }
    sort(Tempos_de_mortes_normalizado, Tempos_de_mortes_normalizado + M);

    map<long double, long double> acumulado;

    double cont = 0;
    for(int i=1; i<M; i++){
        data_TM<<Tempos_de_mortes_normalizado[i-1]<<"\n";

        if(Tempos_de_mortes_normalizado[i] == Tempos_de_mortes_normalizado[i-1]) cont++;
        else{
            acumulado[Tempos_de_mortes_normalizado[i-1]] = (i + i-cont)/(2*M);
            cont=0;
        }
    }

    data_TM<<Tempos_de_mortes_normalizado[M-1]<<"\n";
    acumulado[Tempos_de_mortes_normalizado[M-1]] = (M + M-cont)/(2*M);


    for(auto p:acumulado)
        data_TM_Acumulado<<p.first<<"\t"<<p.second<<"\n";

    data_TM.close();
    data_TM_Acumulado.close();
    //data_pm.close();
    //data_Vm.close();
    

    free(viz);
    return 0;
}
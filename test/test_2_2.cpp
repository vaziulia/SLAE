#include"../src/MPI.h"
#include"../src/Gradient_descent.h"
#include<iostream>

double f(std::vector<double> x, CSR<double> matrix, std::vector<double> b,double c){
    int n = x.size();
    std::vector<double> Ax = matrix*x;
    double a = 0;
    for(int i=0;i<n;++i){
        a+=Ax[i]*x[i];
    }
    double btx = 0;
    for(int i=0;i<n;++i){
        btx+=b[i]*x[i];
    }

    return 0.5*a-btx+c;
}


int main(){
    std::vector<double> values{10,11,13,15};
    std::vector<int> cols{0,1,2,3};
    std::vector<int> rows{0,1,2,3,4};

    CSR<double> matrix = CSR<double>(values,cols,rows);

    std::vector<double> b{4,4,4,4};
    std::vector<double> x_mpi;
    std::vector<double> x_opt;
    std::vector<double> x_gd;
    double c = 2;
    double tolerance = 0.0000000000001;
    double tau = 0.9*2/15;
    double tau_opt = 2.0/(10.0+15.0);
    std::cout<<"MPI:";
    x_mpi = MPI(matrix,b,tau,tolerance);
    std::cout<<"MPI opt:";
    x_opt = MPI(matrix,b,tau_opt,tolerance);
    std::cout<<"GD fast:";
    x_gd = Gradient_descent_fast(matrix,b,tolerance);


    std::cout<<"X gradient descent (MPI):";
    for(int i=0;i<4;i++){
        std::cout<<x_mpi[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"X MPI opt:";
    for(int i=0;i<4;i++){
        std::cout<<x_opt[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"X gradient descent fast:";
    for(int i=0;i<4;i++){
        std::cout<<x_gd[i]<<" ";
    }
    std::cout<<std::endl;

    std::cout<<f(x_mpi,matrix,b,c)<<" "<<f(x_opt,matrix,b,c)<<" "<<f(x_gd,matrix,b,c)<<" "<<std::endl;

    return 0;
}
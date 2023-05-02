#pragma once

#include<vector>
#include"CSR.h"
#include"operators.h"
#include<iostream>

std::vector<double> Gradient_descent_fast(CSR<double> matrix, std::vector<double> b, double tolerance){
    int n = b.size();
    std::vector<double> res(n);
    std::vector<double> dif(n);
    for(int i =0;i<n;++i){
        res[i] = 0;
    }
    do{
        dif = (matrix*res-b);

        double tau = 0;
        for(int i =0;i<n;++i){
            tau+=dif[i]*dif[i];
        }
        std::vector<double> Ar = matrix*dif;
        double rtAr = 0;
        for(int i =0;i<n;++i){
            rtAr+=Ar[i]*dif[i];
        }

        tau = tau/rtAr;

        res = res-dif*tau;

    std::cout<<res[0]<<" "<<res[3]<<std::endl;
    }while(norm(dif) > tolerance);

    return res;
}
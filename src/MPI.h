#pragma once

#include<vector>
#include"CSR.h"
#include"operators.h"
#include<iostream>

std::vector<double> MPI(CSR<double> matrix, std::vector<double> b, double tau, double tolerance){
    int n = b.size();
    std::vector<double> res(n);
    std::vector<double> dif(n);
    for(int i =0;i<n;++i){
        res[i] = 0;
    }
    do{
        dif = (matrix*res-b);
        res = res-dif*tau;

    std::cout<<res[0]<<" "<<res[3]<<std::endl;
    }while(norm(dif) > tolerance);

    return res;
}
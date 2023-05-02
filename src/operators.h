#pragma once

#include<vector>
#include"CSR.h"

std::vector<double> operator*(std::vector<double> a, double b){
    std::vector<double> res(a.size());
    for(int i=0;i<a.size();++i){
        res[i] = a[i]*b;
    }
    return res;
}

std::vector<double> operator-(std::vector<double> a, std::vector<double> b){
    std::vector<double> res(a.size());
    for(int i=0;i<a.size();++i){
        res[i] = a[i]-b[i];
    }
    return res;
}

double norm(std::vector<double> a){
    double max = a[0];
    if(max<0){
            max = -max;
    }
    for(int i=0;i<a.size();++i){
        int x = a[i];
        if(x<0){
            x = -x;
        }
        if(x>max){max=x;}
    }

    return max;
}
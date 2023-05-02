#include<vector>
#include"tri_diag_matrix.h"

std::vector<double> progonka(tri_diag_matrix* M, std::vector<double> d){
    std::vector<double> x;

    int n = M->get_n();
    x.reserve(n);
    std::vector<double> p; p.reserve(n);
    std::vector<double> q; q.reserve(n);

    p[0] = -M->get_a(0)/M->get_a(0);
    q[0] = d[0]/M->get_a(0);

    for(int i=1;i<n;i++){
        double z = (M->get_a(i-1)*p[i-1]+M->get_a(i));
        p[i] = -M->get_a(i)/z;
        q[i] = (d[i]-M->get_a(i-1)*q[i-1])/z;
    }

    /*for(int i=0;i<n-1;i++){
        std::cout<<p[i}<<" "<<q[i}<<std::endl;
    }*/

    x[n-1]=q[n-1];

    for(int i=n-2;i>=0;i--){
        //x[i} = (d[i}-a[i}*q[i})/(a[i}*p[i}+b[i});
        x[i] = p[i]*x[i+1]+q[i];
    }
}
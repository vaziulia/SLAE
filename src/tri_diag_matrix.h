#pragma once

#include<vector>

struct tri_diag_matrix{
    public:
        tri_diag_matrix(int m){
            a.reserve(m-1);
            b.reserve(m);
            c.reserve(m-1);
            n = m;
        };

        tri_diag_matrix(int m, std::vector<double> a, std::vector<double> b, std::vector<double> c){
            this->a = a;
            this->b = b;
            this->c = c;
            n = m;
        };

        int get_n(){return n;};
        double get_a(int i){if(i<n){return a[i];}return 0;};
        double get_b(int i){if(i<=n){return b[i];}return 0;};
        double get_c(int i){if(i<n){return c[i];}return 0;};
        void set_a(int i, double val){if(i<n){a[i] = val;}};
        void set_b(int i, double val){if(i<=n){b[i] = val;}};
        void set_c(int i, double val){if(i<n){c[i] = val;}};
        void set_a(std::vector<double> a){this->a = a;};
        void set_b(std::vector<double> b){this->b = b;};
        void set_c(std::vector<double> c){this->c = c;};
        double operator()(int i, int j){
            if (i<n && j<n && i>=0 && j>=0){
                if(i-j==0){
                    return get_a(i-j);
                }
                if(i-j==1){
                    return get_b(i-j);
                }
                if(i-j==-1){
                    return get_c(i-j);
                }
            }
            return 0;
        }

    private:
        int n;
        std::vector<double> a;
        std::vector<double> b;
        std::vector<double> c;
};
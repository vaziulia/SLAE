#pragma once
#include<iostream>
#include <algorithm>
#include<vector>

template<typename T>
struct DOK {
    int i;
    int j;
    T value_;

    bool operator<(const DOK<T> dok_) const {
        if (i != dok_.i) return i < dok_.i;
        if (i == dok_.i) return j < dok_.j;
    }
};


template<typename T>
class CSR {
    public:
        int row_num;
        int col_num;
        std::vector<T> values;
        std::vector<int> cols;
        std::vector<int> rows;

        CSR(int n, double a, double b){
            std::vector<DOK<double>> dok;
            for(int i = 0; i < n*n; i ++){
                dok.push_back({i, i, 2 * b});
            }

            for(int i = 0; i < n*n-1; i ++){
                dok.push_back({i + 1, i, a});
                dok.push_back({i, i + 1, a});
            }

            for(int i = 0; i < n*n-n; i ++){
                dok.push_back({i + 17, i, a});
                dok.push_back({i, i + 17, a});
            }

            this->col_num = n*n;
            this->row_num = n*n;

            std::sort(dok.begin(), dok.end());
            rows.reserve(this->row_num + 1);
            values.reserve(dok.size());
            cols.reserve(dok.size());
            rows.push_back(0);

            int count_el = 0;
            int i = 0; // row index
            for (auto it: dok) {
                while (i < it.i) {
                    rows.push_back(count_el);
                    i += 1;
                }

                if (it.i == i) {
                    values.push_back(it.value_);
                    cols.push_back(it.j);
                    count_el++;
                }
            }
            rows.push_back(count_el);
        }

        CSR(std::vector<T> &values_i,std::vector<int> &cols_i,std::vector<int> &rows_i){
            values = values_i;
            cols = cols_i;
            rows = rows_i;
            row_num = rows.size()-1;
        }

        CSR(std::vector<DOK<T>> &elements_, int row_num, int col_num){
            this->col_num = col_num;
            this->row_num = row_num;

            std::sort(elements_.begin(), elements_.end());
            rows.reserve(row_num + 1);
            values.reserve(elements_.size());
            cols.reserve(elements_.size());
            rows.push_back(0);

            int count_el = 0;
            int i = 0; // row index
            for (auto it: elements_) {
                while (i < it.i) {
                    rows.push_back(count_el);
                    i += 1;
                }

                if (it.i == i) {
                    values.push_back(it.value_);
                    cols.push_back(it.j);
                    count_el++;
                }
            }
            rows.push_back(count_el);
        }

        CSR(int N, int L, double a, double b){
            row_num = N;
            int Nz = 5*N-2*L-2;
            values.resize(Nz);
            cols.resize(Nz);
            rows.resize(N+1);

            values[0] = 2*b;
            values[1] = a;
            values[2] = a;

            cols[0] = 0;
            cols[1] = 1;
            cols[2] = L;
        
            rows[0] = 0;
            rows[1] = 3;

            for(int i = 1;i<L;++i){
                values[i*4-1] = a;
                values[i*4+0] = 2*b;
                values[i*4+1] = a;
                values[i*4+2] = a;

                cols[i*4-1] = i-1;
                cols[i*4+0] = i+0;
                cols[i*4+1] = i+1;
                cols[i*4+2] = i+L;

                rows[i+1] = rows[i]+4;
            }
            for(int i = 0;i<N-2*L;++i){
                values[i*5+4*L-1] = a;
                values[i*5+4*L-0] = a;
                values[i*5+4*L+1] = 2*b;
                values[i*5+4*L+2] = a;
                values[i*5+4*L+3] = a;

                cols[i*5+4*L-1] = i+2-L;
                cols[i*5+4*L-0] = i+2-1;
                cols[i*5+4*L+1] = i+2+0;
                cols[i*5+4*L+2] = i+2+1;
                cols[i*5+4*L+3] = i+2+L;

                rows[i+L+1] = rows[i+L]+5;
            }
            for(int i = 0;i<L-1;++i){
                int index = 5*N-6*L;
                values[i*4+index-1] = a;
                values[i*4+index-0] = a;
                values[i*4+index+1] = 2*b;
                values[i*4+index+2] = a;

                cols[i*4+index-1] = i-L+4;
                cols[i*4+index-0] = i-1+4;
                cols[i*4+index+1] = i+0+4;
                cols[i*4+index+2] = i+1+4;

                rows[N-L+i+1] = rows[N-L+i]+4;
            }
            
            rows[N] = rows[N-1] + 3;

            values[Nz-3] = a;
            values[Nz-2] = a;
            values[Nz-1] = 2*b;
            cols[Nz-3] = N-L-1;
            cols[Nz-2] = N-2;
            cols[Nz-1] = N-1;
        }

        T operator()(int i, int j) const {
            for (int k = rows[i]; k < rows[i+1]; ++k) {
                if (cols[k] == j) {
                    return values[k];
                }
            }
            return 0;
        }

        std::vector<T> operator*(std::vector<T> vec) const {
            std::vector<T> res(row_num);
            for (int i = 0; i < row_num; ++i) {
                for (int j = rows[i]; j < rows[i+1]; ++j) {
                    res[i] += values[j] * vec[cols[j]];
                }
            }
            return res;
        }
};
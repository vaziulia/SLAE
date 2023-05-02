#pragma once

#include<vector>

template<typename T>
class CSR {
    public:
        int row_num;
        int col_num;
        std::vector<T> values;
        std::vector<int> cols;
        std::vector<int> rows;

        CSR(std::vector<T> &values_i,std::vector<int> &cols_i,std::vector<int> &rows_i){
            values = values_i;
            cols = cols_i;
            rows = rows_i;
            row_num = rows.size()-1;
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
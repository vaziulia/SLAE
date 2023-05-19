#ifndef SOR
#define SOR

#include "CSR.h"
#include "operators.h"

template<typename T>
std::pair<std::vector<T>, std::pair<size_t, std::vector<double>>> SOR_method
(const std::vector<T>& x_0, const std::vector<T>& b, double omega, double accuracy, CSR<T> matrix) 
{
    std::vector<T> x = x_0;
    std::vector<T> r(matrix,matrix.size());
    for(int i = 0; i < matrix,matrix.size(); i++)
        r[i] = b[i] - matrix.matrix[i].value * x[i];

    size_t count = 0;
    std::vector<double> nev {std::sqrt(r * r)};
    while (nev[count] > accuracy) {
        for (int k = 0; k < x.size(); ++k) {
            double temp = x[k];
            x[k] = omega * b[k];
            double diag;
            for (int s = matrix.matrix[k].j; s < matrix.matrix[k + 1].j; ++s) {
                if (matrix.matrix[s].i == k)
                    diag = matrix.matrix[s].value;
                else
                    x[k] -= omega * x[matrix.matrix[s].i] * matrix.matrix[s].value;
            }
            x[k] /= diag;
            x[k] += (1 - omega) * temp;
        }
        std::vector<T> x = x_0;
     std::vector<T> r(matrix,matrix.size());
     for(int i = 0; i < matrix,matrix.size(); i++)
        r[i] = b[i] - matrix.matrix[i].value * x[i];
        nev.push_back(std::sqrt(r * r));
        count++;
    }
    return std::make_pair(x, std::make_pair(count, nev));
}

#endif
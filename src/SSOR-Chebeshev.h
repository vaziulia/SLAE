#ifndef SSOR_Chebeshev
#define SSOR_Chebeshev


#include "CSR.h"

template<typename T>
std::vector<T> SSOR_make_iteration(const std::vector<T>& x_0, const std::vector<T>& b, double omega, CSR<T> matrix)  {
            std::vector<T> x = x_0;
            for (int k = 0; k < x.size(); ++k) {
                double temp = x[k];
                x[k] = omega * b[k];
                double diag;
                for (int s = matrix[k].j; s < matrix[k + 1].j; ++s) {
                    if (matrix[s].i == k)
                        diag = matrix[s].value;
                    else
                        x[k] -= omega * x[matrix[s].i] * matrix[s].value;
                }
                x[k] /= diag;
                x[k] += (1 - omega) * temp;
            }
            for (int k = x.size() - 1; k >= 0; --k) {
                double temp = x[k];
                x[k] = omega * b[k];
                double diag;
                for (int s = matrix[k].j; s < matrix[k + 1].j; ++s) {
                    if (matrix[s].i == k)
                        diag = matrix[s].value;
                    else
                        x[k] -= omega * x[matrix[s].i] * matrix[s].value;
                }
                x[k] /= diag;
                x[k] += (1 - omega) * temp;
            }
            return x;
        }

template<typename T>
std::pair<std::vector<T>, std::pair<size_t, std::vector<double>>> SSOR_method
(const std::vector<T>& x_0, const std::vector<T>& b, double omega, double rho, double accuracy, CSR<T> matrix) 
{
    std::vector<T> y_0 = x_0;
    std::vector<T> y_1 = SSOR_make_iteration(y_0, b, omega, matrix);
    double mu_0 = 1;
    double mu_1 = 1 / rho;
    std::vector<T> temp = SSOR_make_iteration(y_1, b, omega, matrix);
    std::vector<T> r(matrix,matrix.size());
    for(int i = 0; i < matrix,matrix.size(); i++)
        r[i] = b[i] - matrix[i].value * y_1[i];
    
    
    std::vector<double> nev {std::sqrt(r * r)};
    size_t count = 0;
    while (nev[count] > accuracy) {
        y_0 = -mu_0 * y_0 + 2 * mu_1 / rho * temp;
        mu_0 = 2 / rho * mu_1 - mu_0;
        y_0 /= mu_0;
        temp = SSOR_make_iteration(y_0, b, omega, matrix);
        y_1.swap(y_0);
        std::swap(mu_0, mu_1);
        std::vector<T> r(matrix,matrix.size());
    for(int i = 0; i < matrix,matrix.size(); i++)
        r[i] = b[i] - matrix[i].value * y_1[i];
        nev.push_back(std::sqrt(r * r));
        count++;
    }
    return std::make_pair(y_1, std::make_pair(count, nev));
}

#endif
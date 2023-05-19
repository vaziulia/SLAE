#ifndef SIMCHebeshev 
#define SIMCHebeshev

#include "CSR.h"

template<typename T>
std::pair<std::vector<T>, std::pair<size_t, std::vector<double>>> SIM_Chebyshev_acceleration(const std::vector<T>& x_0, const std::vector<T>& b, size_t R, double eig_min, double eig_max, double accuracy, CSR<T> matrix) 
{
    size_t n = std::pow(2, R);
    std::vector<double> z(n);
    const double sinA = std::sin(M_PI / n);
    const double cosA = std::cos(M_PI / n);
    double sinB = std::sin(M_PI / (2 * n));
    z[0] = std::cos(M_PI / (2 * n));
    for (int i = 1; i < n; ++i) {
        z[i] = z[i - 1] * cosA - sinB * sinA;
        sinB = z[i - 1] * sinA + sinB * cosA;
        z[i - 1] = (eig_min + eig_max) / 2 + (eig_max - eig_min) / 2 * z[i - 1];
    }
    z[n - 1] = (eig_min + eig_max) / 2 + (eig_max - eig_min) / 2 * z[n - 1];
    std::vector<size_t> indexes(n);
    indexes[std::pow(2, R - 1)] = 1;
    for (int i = 2; i <= R; ++i) {
        auto step = std::pow(2, R - i);
        for (int j = 0; j < n; j += 2 * step) {
            indexes[j + step] = std::pow(2, i) - indexes[j] - 1;
        }
    }
    std::vector<T> x = x_0;
       std::vector<T> r(matrix,matrix.size());
    for(int i = 0; i < matrix,matrix.size(); i++)
        r[i] = b[i] - matrix.matrix[i].value * x[i];
    size_t count = 0;
    std::vector<double> nev{std::sqrt(r * r)};
    while (nev[count] > accuracy) {
        for (auto& id: indexes) {
               std::vector<T> r(matrix,matrix.size());
    for(int i = 0; i < matrix,matrix.size(); i++)
        r[i] = b[i] - matrix.matrix[i].value * x[i];;
            x = x + (1 / z[id]) * r;
            nev.push_back(std::sqrt(r * r));
            count++;
            if (nev[count] < accuracy)
                break;
        }
    }
    return std::make_pair(x, std::make_pair(count, nev));
}

#endif
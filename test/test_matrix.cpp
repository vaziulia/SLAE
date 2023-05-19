#include<iostream>
#include"../src/tri_diag_matrix.h"
#include"../src/CSR.h"
#include <gtest/gtest.h>

TEST(matrix, values){
    std::vector<double> values{1, 2, 4, 2, 6};
    std::vector<int> cols{0, 1, 1, 1, 2};
    std::vector<int> rows{0, 2, 3, 5};
    CSR<double> matrix = CSR<double>(values,cols, rows);

    ASSERT_EQ(matrix(0,0),1);
    ASSERT_EQ(matrix(1,0),0);
}

TEST(matrix, out_of_range){
    std::vector<double> values{1, 2, 4, 2, 6};
    std::vector<int> cols{0, 1, 1, 1, 2};
    std::vector<int> rows{0, 2, 3, 5};
    CSR<double> matrix = CSR<double>(values,cols, rows);

    ASSERT_EQ(matrix(3,0),0);
}

TEST(matrix, negative_indexes){
    std::vector<double> values{1, 2, 4, 2, 6};
    std::vector<int> cols{0, 1, 1, 1, 2};
    std::vector<int> rows{0, 2, 3, 5};
    CSR<double> matrix = CSR<double>(values,cols, rows);

    ASSERT_EQ(matrix(-1,0),0);
}

TEST(matrix, mult_by_vect){
    std::vector<double> values{1, 2, 4, 2, 6};
    std::vector<int> cols{0, 1, 1, 1, 2};
    std::vector<int> rows{0, 2, 3, 5};

    std::vector<double> b{1, 2, 3};

    CSR<double> matrix = CSR<double>(values,cols, rows);

    std::vector<double> x = matrix*b;

    ASSERT_EQ(x[0],5);
    ASSERT_EQ(x[1],8);
    ASSERT_EQ(x[2],22);
}

TEST(matrix, DOKtoSCR){
    double b = 18;
    double a = 6;

    int n = 5;

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

    CSR<double> matrix = CSR<double>{dok, n*n, n*n};

}



TEST(matrix, five_diag){
    double b = 18;
    double a = 41;

    int n = 5;

    CSR<double> matrix = CSR<double>{n, a, b};

}
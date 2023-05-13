#include"../src/tri_diag_matrix.h"
#include<iostream>
#include <gtest/gtest.h>


TEST(triag_matrix,test_fill_after_constructor){
    int n = 3;

    std::vector<double> a{2, 3};
    std::vector<double> b{11, 12, 13};
    std::vector<double> c{5, 6};

    tri_diag_matrix matrix = tri_diag_matrix(n);

    matrix.set_a(a);
    matrix.set_b(b);
    matrix.set_c(c);

    ASSERT_EQ(matrix(0,0),b[0]);
}

TEST(triag_matrix,test_fill_in_constructor){
    int n = 3;

    std::vector<double> a{2, 3};
    std::vector<double> b{11, 12, 13};
    std::vector<double> c{5, 6};

    tri_diag_matrix matrix = tri_diag_matrix(n,a,b,c);
}

TEST(triag_matrix,set_some_el){
    int n = 3;

    std::vector<double> a{2, 3};
    std::vector<double> b{11, 12, 13};
    std::vector<double> c{5, 6};

    tri_diag_matrix matrix = tri_diag_matrix(n,a,b,c);
}
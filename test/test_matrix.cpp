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

    std::vector<DOK<double>> dok;
    for(int i = 0; i < 289; i ++){
        dok.push_back({i, i, 2 * b});
    }

    for(int i = 0; i < 288; i ++){
        dok.push_back({i + 1, i, a});
        dok.push_back({i, i + 1, a});
    }

    for(int i = 0; i < 272; i ++){
        dok.push_back({i + 17, i, a});
        dok.push_back({i, i + 17, a});
    }

    CSR<double> matrix = CSR<double>{dok, 289, 289};


    for(int i=0;i<10;++i){
        for(int j=0;j<289;j++){
            std::cout<<matrix(i,j)<<" ";
        }
        std::cout<<std::endl;
    }
}

TEST(matrix, five_diag){
    CSR<double> matrix = CSR<double>(7,3,4,5);
    
    /*
    for(int i=0;i<7;++i){
        for(int j=0;j<7;j++){
            std::cout<<matrix(i,j)<<" ";
        }
        std::cout<<std::endl;
    }
    */
   /*
    for(int i=0;i<30;i++){
            std::cout<<matrix.cols[i]<<" ";
    }
    */
    
}
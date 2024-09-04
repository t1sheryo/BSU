#include <iostream>
#include "Matrix.h"
#include "SquareMatrix.h"

//Чеберук Тимофей, группа 10

int main() {

    try {
        Matrix<2, 3, int> m1(std::vector<std::vector<int>>{{1,   2,  3},
                                                           {2,   -1, 10}});
        Matrix<2, 2, int> m2(std::vector<std::vector<int>>{{2,  3},
                                                           {2, 10}});
        Matrix<2, 2, int> m3(m2);
        Matrix<4, 4, int> m4(std::vector<std::vector<int>>{{2, 3, 4, 2},
                                                           {2, 1, 1, -1},
                                                           {2, -10, 1, 3},
                                                           {2, 24, 2, 6}});
        SquareMatrix<5, int> m5(std::vector<std::vector<int>>{{2, 3, 17, 2, 3},
                                                              {-2, 111, 1, -1, 1},
                                                              {-2, 111, 1, -1, 1},
                                                              {1, 24, 41, 6, 7},
                                                              {1, 24, 41, 6, 7}});
        Matrix<4, 4, int> m6(std::vector<std::vector<int>>{{2, 5, 7, 13},
                                                           {6, 3, 4, 21},
                                                           {2, 5, 7, 35},
                                                           {209, -2, -3, 144}});

        Rational r1, r2, r3, r4;
        std::cin >> r1 >> r2 >> r3 >> r4;
        //std::cout << "r1: " << r1 << "; r2: " << r2 << "; r3: " << r3 << "; r4: " << r4 << '\n';
        Matrix<2, 2> m7(std::vector<std::vector<Rational>>{{r1, r2},
                                                           {r3, r4}});
        Matrix<3, 2> m8(std::vector<std::vector<Rational>>{{r3, r2},
                                                           {r3, r3},
                                                           {r3, r3}});
//        std::cout << std::boolalpha << "m3 == m2:" << (m3 == m2) << "\nm3 == m4: " << (m3 == m4) << '\n';
//
//        std::cout << std::boolalpha << "m3 == m2:" << (m3 == m2) << "\nm3 == m4: " << (m3 == m4) << '\n';
//        std::cout << "m4 + m6:\n" << (m4 + m6) << '\n';
//        std::cout << "m4 += m6:\n" << (m4 += m6) << '\n';
//        std::cout << "m4 - m6:\n" << (m4 - m6) << '\n';
//        std::cout << "m4 -= m6:\n" << (m4 -= m6) << '\n';
//        std::cout << "m4 + m6:\n" << (m4 + m6) << '\n';
//        std::cout << "m2 * m1:\n" << (m2 * m1) << '\n';
//        std::cout << "m2 *= m1:\n" << (m2 *= m3) << '\n';
//        std::cout << "m2(transposed):\n" << m2.transposed() << '\n';
//        std::cout << "m2(trace): " << m2.trace() << '\n';
//        std::cout << "m2(Rows): " << m2.getRows() << '\n';
//        std::cout << "m2(Columns): " << m2.getColumns() << '\n';
//        std::cout << "m5(determinant): " <<  m5.det() << '\n';
//        std::cout << "m6(inverted):\n" << m6.inverted() << '\n';
//        m6.invert();
//        std::cout << "m6(invert): \n" << m6 << '\n';
//        std::cout << "m5(rank): " << m5.rank() << '\n';
//
//        std::cout << m7 << '\n' << m8 << '\n';
//        std::cout << "m7 + m8:\n" << (m7 + m8) << '\n';
//        std::cout << "m7 += m8:\n" << (m7 += m8) << '\n';
//        std::cout << "m7(trace): " << m7.trace() << '\n';
//        std::cout << "m7(det): " << m7.det() << '\n';
        std::cout << "m8(rank): " << m8.rank() << '\n';

    }catch (const char* ex){
        std::cout << ex;
    }
    return 0;
}

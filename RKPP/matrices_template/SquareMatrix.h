#ifndef MATRICES_TEMPLATE_SQUAREMATRIX_H
#define MATRICES_TEMPLATE_SQUAREMATRIX_H

#include "Matrix.h"

template <size_t K, typename G>
class SquareMatrix : public Matrix<K, K, G>{
public:
    SquareMatrix() = default;
    SquareMatrix(std::vector<std::vector<G>> vec): Matrix<K, K, G>(vec){};
};

#endif //MATRICES_TEMPLATE_SQUAREMATRIX_H

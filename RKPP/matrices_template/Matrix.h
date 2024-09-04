#ifndef MATRICES_TEMPLATE_MATRIX_H
#define MATRICES_TEMPLATE_MATRIX_H

#include "Rational.h"

template<size_t M, size_t N, typename T = Rational>
class Matrix{
private:
    void deleteRow(size_t ind){
        matr.erase(matr.begin() + ind);
    }
    void deleteColumn(size_t ind){
        size_t size = matr.size();
        for(size_t i = 0; i < size; ++i){
            matr[i].erase(matr[i].begin() + ind);
        }
    }
    void swap(int row1, int row2, int col){
        for (int i = 0; i < col; i++){
            T temp = matr[row1][i];
            matr[row1][i] = matr[row2][i];
            matr[row2][i] = temp;
        }
    }
    long long rankOfMatrix(){
        int rank = matr[0].size();
        int rows = matr.size();
        for (int row = 0; row < rank; row++){
            if (matr[row][row] != 0){
                for (int col = 0; col < rows; col++){
                    if (col != row){
                        T mult = (T)matr[col][row] / matr[row][row];
                        for (int i = 0; i < rank; i++)
                            matr[col][i] -= mult * matr[row][i];
                    }
                }
            }
            else {
                bool reduce = true;
                for (int i = row + 1; i < rows;  i++){
                    if (matr[i][row] != 0){
                        swap(row, i, rank);
                        reduce = false;
                        break ;
                    }
                }
                if (reduce) {
                    rank--;
                    for (int i = 0; i < rows; i ++)
                        matr[i][row] = matr[i][rank];
                }
                row--;
            }
        }
        return rank;
    }
protected:
    std::vector<std::vector<T>> matr;
public:
    std::vector<std::vector<T>> getMatr() const{
        return matr;
    }
    Matrix(){
        std::vector<std::vector<T>> m;
        for(size_t i = 0; i < M; i++){
            std::vector<T> vec;
            for(size_t j = 0; j < N; ++j){
                if(i == j) vec.push_back(T(1));
                else vec.push_back(T(0));
            }
            m.push_back(vec);
        }
        matr = m;
    }
    Matrix(std::vector<std::vector<T>> other){
        matr = other;
    }
    Matrix(const Matrix<M, N, T>& other){
        matr = other.matr;
    }
    template<size_t _M, size_t _N, typename _T>
    bool operator==(const Matrix<_M, _N, _T>& other){
        if(M != _M || N != _N || typeid(T) != typeid(_T)) return false;
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; ++j){
                if(matr[i][j] != other[i][j]) return false;
            }
        }
        return true;
    }
    template<size_t _M, size_t _N, typename _T>
    bool operator!=(const Matrix<_M, _N, _T>& other){
        return !(*this == other);
    }
    Matrix<M, N, T> operator+(const Matrix<M, N, T>& other){
        //if(matr.size() != other.matr.size() || matr[0].size() != other.matr[0].size()) throw "Invalid sizes for addition!\n";
        Matrix <M, N, T> ret;
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; ++j){
                ret.matr[i][j] = matr[i][j] + other.matr[i][j];
            }
        }
        return ret;
    }
    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& other){
        *this = *this + other;
        return *this;
    }
    Matrix<M, N, T> operator-(const Matrix<M, N, T>& other){
        Matrix <M, N, T> ret;
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; ++j){
                ret.matr[i][j] = matr[i][j] - other.matr[i][j];
            }
        }
        return ret;
    }
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& other){
        *this = *this - other;
        return *this;
    }
    Matrix<M, N, T>& operator*(const T var){
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; ++j){
                matr[i][j] *= var;
            }
        }
        return *this;
    }
    template<size_t K>
    Matrix<M, K, T> operator*(Matrix<N, K, T>& other){
        Matrix<M, K, T> ret;
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < K; ++j){
                int sum = 0;
                for(size_t k = 0; k < N; ++k){
                    sum += matr[i][k] * other[k][j];
                }
                ret[i][j] = sum;
            }
        }
        return ret;
    }
    Matrix<M, N, T>& operator*=(Matrix<M, N, T>& other){
        Matrix<M, N, T> ret;
        ret = (*this) * other;
        matr = ret.getMatr();
        return *this;
    }
    long long det() const{
        long long res = 0;
        if(M != N) throw "Invalid size for det!\n";
        if (matr.size() == 1) {
            return matr[0][0];
        } else if (matr.size() == 2) {
            return ((matr[0][0] * matr[1][1]) - (matr[1][0] * matr[0][1]));
        } else {
            for(size_t j = 0; j < matr[0].size(); ++j){
                Matrix<M, N, T> submatr(*this);
                submatr.deleteRow(0);
                submatr.deleteColumn(j);
                int deg = j + 1 + 1;
                res += pow(-1, deg) * submatr.det() * matr[0][j];
            }
        }
        return res;
    }
    Matrix<M, N, T> transposed() const{
        Matrix<N, M, T> trans;
        for(size_t i = 0; i < M; ++i){
            for(size_t j = 0; j < N; ++j){
                trans[j][i] = matr[i][j];
            }
        }
        return trans;
    }
    long long rank() const{
        Matrix<M, N, T> copy(*this);
        return copy.rankOfMatrix();
    }
    T trace() const{
        if(M != N) throw "Invalid size!\n";
        Matrix<M, N, T> cur(*this);
        T sum(0);
        for(size_t i = 0; i < M; ++i){
            sum += matr[i][i];
        }
        return sum;
    }
    Matrix<M, M, T> inverted() const{
        long long det = this->det();
        if(det == 0) throw "Cannot find inverted matrix because det = 0!\n";
        Matrix<M, N, T> ret;
        for(size_t i = 0; i < matr.size(); ++i){
            for(size_t j = 0; j < matr[0].size(); ++j){
                Matrix<M, N, T> submatr(*this);
                submatr.deleteRow(i);
                submatr.deleteColumn(j);
                int deg = j + i;
                ret[i][j] = pow(-1, deg) * submatr.det();
                ret[i][j] /= det;
            }
        }
        ret = ret.transposed();
        return ret;
    }
    Matrix<M, N, T>& invert(){
        *this = this->inverted();
        return *this;
    }
    [[nodiscard]] size_t getRows() const{ return M; }
    [[nodiscard]] size_t getColumns() const{ return N; }
    const std::vector<T>& operator[](size_t i) const{ return matr[i]; }
    std::vector<T>& operator[](size_t i){ return matr[i]; }
    friend std::ostream& operator<<(std::ostream& out, const Matrix& other){
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; ++j){
                out << other.matr[i][j] << '\t';
            }
            out << '\n';
        }
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Matrix& other){
        for(size_t i = 0; i < M; i++){
            for(size_t j = 0; j < N; ++j){
                in >> other.matr[i][j];
            }
        }
        return in;
    }
};

#endif //MATRICES_TEMPLATE_MATRIX_H

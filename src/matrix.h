
#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
namespace aline
{
    template <class T,class M,class N>
    class Matrix
    {
    public:
        T **mat
        Matrix();
        Matrix(std::initializer_list<T>);
        Matrix(const Matrix<T,M,N> &m);

        Vector<T,N> at(size_t row)
        {
            if(row>M || row<0) throw runtime_error("Index non conforme");
            return mat[row];
        }

        T at(size_t row,size_t col)
        {
            if(row>M || row<0) throw runtime_error("Index non conforme");
            if(col>N || col<0) throw runtime_error("Index non conforme");
            return mat[row][col];
        }
        Vector<T,N> Matrix<T,M,N>::operator[]( size_t i ) const
        {
            return row[i];
        }
        Vector<T,N> Matrix<T,M,N>::operator[]( size_t i ) const
        {
            return row[i];
        }
        Matrix<T,M,N> & Matrix<T,M,N>::operator+=( const Matrix<T,M,N> & m)
        {
            for(int row=0;row<M;row++)
            {
                for(int col=0;col<N;col++)
                {
                    mat[row][col] += m.mat[row][col];
                }
            }
        }
        return *this;
    };
    template <class T,class M,class N>
    Matrix<T,M,N> inverse( const Matrix<T,M,N> & )
    {
        if(N != M)return NAN;

    }
    template <class T,class M,class N>
    bool isnan( const Matrix<T,M,N> &m )
    {
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                if(m.mat[row][col] == NAN) return true;
            }
        }
        return false;
    }
    template <class T,class M,class N>
    bool operator==( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
         for(int row=0;row<M;row++)
            {
                for(int col=0;col<N;col++)
                {
                    if(m1.mat[row][col] != m2.mat[row][col])return false;
                }
            }
        return true;
    }
    template <class T,class M,class N>
    bool operator!=( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        return !(m1==m2)
        /*for(int row=0;row<M;row++)
            {
                for(int col=0;col<N;col++)
                {
                    if(m1.mat[row][col] == m2.mat[row][col])return false;
                }
            }
        return true;*/
    }
    template <class T,class M,class N>
    std::ostream & operator<<( std::ostream out, const Matrix<T,M,N> &m ){
        for(int row=0;row<M;row++)
            {
                for(int col=0;col<N;col++)
                {
                    out << m.mat[row][col] ;
                }
                out << endl;
            }
        return out;
    }
    template <class T,class M,class N>
    Matrix<T,M,N> operator+( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        Matrix<T,M,N> mat = Matrix();
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] = m1.mat[row][col] + m2.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,class M,class N>
    Matrix<T,M,N> operator-( const Matrix<T,M,N> &m ){
        Matrix<T,M,N> mat = Matrix();
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] = - m.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,class M,class N>
    Matrix<T,M,N> operator-( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        Matrix<T,M,N> mat = Matrix();
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] = m1.mat[row][col] - m2.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,class M,class N>
    Matrix<T,M,N> operator*( const T &scalar, const Matrix<T,M,N> &m ){
     Matrix<T,M,N> mat = Matrix(m);
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] *= scalar;
            }
        }
        return mat;
    }
    template <class T,class M,class N>
    Matrix<T,M,N> operator*( const Matrix<T,M,N> &m, const T &scalar ){
        return m * scalar;
    }
    template <class T,class M,class N>
    Vector<T,M> operator*( const Matrix<T,M,N> &m, const Vector<T,N> &v){
        Vector<T,M> mult = Vector();
        if(M == N)
        {
            for(int )
        }
    }
    template <class T,class M,class N,class O>
    Matrix<T,M,O> operator*( const Matrix<T,M,N> &m1, const Matrix<T,N,O> &m2 ){
        Matrix<T,M,O> mat = Matrix();
        T sum = 0;
        for(int i = 0;i<M;i++)
        {
            for(int j=0;j<O;j++)
            {
                sum = 0;
                for(int k=0;k<N;k++)
                {
                    sum+= m1[i][k]*m2[k][j];
                }
                mat[i][j] = sum;
            }
        }
        return mat;
    }
    template <class T,class M,class N>
    Matrix<T,M,N> operator/( const Matrix<T,M,N> & m, const T & s ){
        return m* (1/s);
    }
    template <class T,class M,class N>
    Matrix<T,M,N> to_string( const Matrix<T,M,N> &m ){

    }
    template <class T,class M,class N>
    Matrix<T,M,N> transpose( const Matrix<T,M,N> &m ){
        Matrix<T,N,M> mat = Matrix();
        for(int row=0;row<N;row++)
        {
            for(int col=0;col<M;col++)
            {
                mat[row][col] = m.mat[col][row];
            }
        }
        return mat;
    }
}
#endif
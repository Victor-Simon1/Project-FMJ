
#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
namespace aline
{

    //const int NAN = 0;
    template <class T,size_t M,size_t N>
    class Matrix
    {
    public:
        //T **mat
        //vector<vector<T>> mat;
        Vector<Vector<T,N>,M> mat;
        Matrix(){
        }
        Matrix(std::initializer_list<std::initializer_list<T>> list)
        {
           Vector<T,N> v;
           int i= 0;
           for(auto vect:list)
           {
                v= Vector<T,N>(vect);
                mat.vec[i] = v;
                i++;
           }
        }

        Matrix(const Matrix<T,M,N> &m)
        {
            mat =Vector<Vector<T,N>,M>();
            for( size_t i=0;i<M;i++)
            {
                for(size_t j=0;j<N;j++)
                {
                  mat.vec[i][j] = m.mat.vec[i][j];  
                }
            }
        }

        Vector<T,N> at(size_t row)
        {
            if((row>=M) || (row<0)) throw runtime_error("Index non conforme");
            return mat.vec[row];
        }

        T at(size_t row,size_t col)
        {
            if(row>=M || row<0) throw runtime_error("Index non conforme");
            if(col>=N || col<0) throw runtime_error("Index non conforme");

            return mat.vec[row][col];
        }
        Vector<T,N> operator[]( size_t index ) const
        {

            return mat.vec[index];
        }
        Vector<T,N> &operator[]( size_t index ) 
        {
            return mat.vec[index];
        }
        Matrix<T,M,N> &operator+=( const Matrix<T,M,N> & m)
        {
            for(size_t row=0;row<M;row++)
            {
                for(size_t col=0;col<N;col++)
                {
                    mat[row][col] += m.mat[row][col];
                }
            }
            return *this;
        }
       
    };
    template <class T,size_t M,size_t N>
    bool nearly_equal(Matrix<T,M,N> m1,Matrix<T,M,N> m2)
    {
        for (size_t i = 0; i < M; i++)
		{
            for (size_t j = 0; j < N; j++)
			{
				const float epsilon = std::numeric_limits<float>::epsilon();
				T value =std::fabs(m1.mat[i][j]-m2.mat[i][j]);
				T max = std::max(std::abs(m1.mat[i][j]),std::abs(m2.mat[i][j]));

				if(value  > max*epsilon)
				{
					return false;
				}
			}
        }
        return true;
    }

    template <typename T, size_t M,size_t N>
    Matrix<double,M,N> inverse(const Matrix<T,M,N> &m1){
   Matrix<double,M,N> inverseMatrix;
   Matrix<double,M,N> mat;
   double max = 0, found = -1;

   for(size_t u=0; u<N; u++){
      for(size_t v=0; v<N; v++){
        mat[u][v] = (double)m1[u][v];
         if(u==v){
            inverseMatrix[u][v] = 1;
         }
      }
   }

   for(size_t j=0; j<N; j++){
        max = 0;
        found = -1;
        for(size_t i=j; i<M; i++){
            if(fabs(mat[i][j]) >= max)
            {
                max = fabs(mat[i][j]);
                found = i;
            }
        }
        if(found == -1){
            return inverseMatrix;
        }
        size_t i= found;
        if(found!=j)
        {
            Vector<double,N> temp = Vector<double,N>(mat[i]);
            Vector<double,N> temp2 = Vector<double,N>(inverseMatrix[i]);
            for(size_t c=0;c<N;c++)
            {
                mat[i][c] = mat[j][c];
                mat[j][c] = temp[c];

                inverseMatrix[i][c] = inverseMatrix[j][c];
                inverseMatrix[j][c] = temp2[c];
            }
            i = j;
        }
        std::cout << "mat1"<<mat << std::endl;
        std::cout << "inverse1"<<inverseMatrix<< std::endl;
        double pivot = 1/mat[i][j];
        std::cout << "pivot :"<<pivot<<std::endl;
        std::cout << i << " : " << j<<std::endl;
        for(size_t c=0;c<N;c++)
        {
            mat[j][c] *= pivot;
            inverseMatrix[j][c] *= pivot;
             
        }
        std::cout << "mat2"<<mat << std::endl;
        std::cout << "inverse2"<<inverseMatrix<< std::endl;
        double pivot2 ;
        for(size_t r=0; r<N; r++){
            if(r!=j)
            {
                pivot2= - mat[r][j];
                mat[r] +=  mat[j] * pivot2;
                inverseMatrix[r] += inverseMatrix[j] * pivot2;

            }
        }
        std::cout << "mat"<<mat << std::endl;
        std::cout << "inverse"<<inverseMatrix<< std::endl;
      
   }
   return inverseMatrix;
}
    template <class T,size_t M,size_t N>
    bool isnan( const Matrix<T,M,N> &m )
    {
        for(size_t row=0;row<M;row++)
        {
            for(size_t col=0;col<N;col++)
            {
                if(std::isnan(m.mat[row][col])) return true;
            }
        }
        return false;
    }
    template <class T,size_t M,size_t N>
    bool operator==( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
         for(size_t row=0;row<M;row++)
            {
                for(size_t col=0;col<N;col++)
                {
                    if(m1.mat[row][col] != m2.mat[row][col])return false;
                }
            }
        return true;
    }
    template <class T,size_t M,size_t N>
    bool operator!=( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        return !(m1==m2);
    }
    template <class T,size_t M, size_t N>
    std::ostream& operator<<(std::ostream &out, const Matrix<T,M,N> &m ){
        std::cout << "Matrice de taille (" << M <<","<<N<<")"<<std::endl;
        for(size_t row=0;row<M;row++)
            {
                out <<"{";
                for(size_t col=0;col<N;col++)
                {
                    out << m.mat[row][col] <<"," ;
                }
                out<< "}" << endl;
            }
        return out;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator+( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        Matrix<T,M,N> mat = Matrix<T,M,N>();
        for(size_t row=0;row<M;row++)
        {
            for(size_t col=0;col<N;col++)
            {
                mat.mat[row][col] = m1.mat[row][col] + m2.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator-( const Matrix<T,M,N> &m ){
        Matrix<T,M,N> mat = Matrix<T,M,N>();
        for(size_t row=0;row<M;row++)
        {
            for(size_t col=0;col<N;col++)
            {
                mat.mat[row][col] = - m.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator-( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        Matrix<T,M,N> mat = Matrix<T,M,N>();
        for(size_t row=0;row<M;row++)
        {
            for(size_t col=0;col<N;col++)
            {
                mat.mat[row][col] = m1.mat[row][col] - m2.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator*( const T &scalar, const Matrix<T,M,N> &m ){
     Matrix<T,M,N> mat = Matrix<T,M,N>(m);
        for(size_t row=0;row<M;row++)
        {
            for(size_t col=0;col<N;col++)
            {
                mat.mat[row][col] *= scalar;
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator*( const Matrix<T,M,N> &m, const T &scalar ){
        return  scalar * m;
    }
    template <class T,size_t M,size_t N>
    Vector<T,M> operator*( const Matrix<T,M,N> &m, const Vector<T,N> &v){
        Vector<T,M> mult = Vector<T,M>();
        for(size_t i=0;i<M;i++)
        {
            mult[i] = 0;
            for(size_t j =0; j<N;j++)
            {
                mult[i] += m.mat[i][j] * v.vec[j];
            }
        }
        return mult;
    }
    template <class T,size_t M,size_t N,size_t O>
    Matrix<T,M,O> operator*( const Matrix<T,M,N> &m1, const Matrix<T,N,O> &m2 ){
        Matrix<T,M,O> mat = Matrix<T,M,O>();
        T sum = T();
        for(size_t i = 0;i<M;i++)
        {
            for(size_t j=0;j<O;j++)
            {
                sum = 0;
                for(size_t k=0;k<N;k++)
                {
                    sum+= m1[i][k]*m2[k][j];
                }
                mat[i][j] = sum;
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator/( const Matrix<T,M,N> & m, const T & s ){
        return (1/s) * m;
    }
    template <class T,size_t M,size_t N>
    std::string to_string( const Matrix<T,M,N> &m ){
        std::string s;
        s.append("(");
        std::ostringstream strs;

        for(size_t i=0;i<M;i++)
        {
            s.append("(");
            for(size_t j=0;j<N;j++)
            {
                s.append( std::to_string(m.mat.vec[i][j]));
                if(!(j==N-1))
                {
                    s.append(", ");
                }
            }
            s.append(")");
            if(!(i==N-1))
            {
                s.append(", ");
            }
        }
        s.append(")");
        return s;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> transpose( const Matrix<T,M,N> &m ){
        Matrix<T,N,M> mat = Matrix<T,M,N>();
        for(size_t row=0;row<N;row++)
        {
            for(size_t col=0;col<M;col++)
            {
                mat[row][col] = m.mat[col][row];
            }
        }
        return mat;
    }
}
#endif
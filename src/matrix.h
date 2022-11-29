
#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
namespace aline
{

    //const int NAN = 0;
    template <class T,size_t M,size_t N>
    class Matrix
    {
    public:
        //T **mat
        vector<vector<T>> mat;
        Matrix(){
            //mat =vector<vector<T>>();
            for(int i=0;i<M;i++)
            {
                vector<T> v1;
                for(int i=0;i<N;i++)
                {
                    v1.push_back(0);
                }
                mat.push_back(v1);
            }  
        }
        Matrix(std::initializer_list<std::initializer_list<T>> list)
        {
            //mat =vector<vector<T>>();
            int l=0,c=0;
          /*
            for(auto x: list)
            {
                vector<T> v = vector<T>(x);
                int  size = v.size();
                while(size< N)
                {
                    v.push_back(0);
                    size = v.size();
                }   
                
                //std::cout <<"auto"<<std::endl;
                mat.push_back(v);
                size =  mat.size();
                 v = vector<T>();
                while(size< M)
                {
                    for(int i =0;i<N;i++)
                        v.push_back(0);
                    mat.push_back(v);
                    size = mat.size();
                } 
               /* for(T value: x)
                {
                    std::cout <<"T"<<std::endl;
                    mat.p
                    mat[l][c] = value;
                    c++;
                }
                l++;
            }   */
            for(int i=0;i<M;i++)
            {
                vector<T> v1;
                for(int i=0;i<N;i++)
                {
                    v1.push_back(0);
                }
                mat.push_back(v1);
            }  
        }
        Matrix(const Matrix<T,M,N> &m)
        {
            
            mat =vector<vector<T>>();
            for(vector<T> v : m.mat)
            {
                
                vector<T> temp;
                for(T value: v)
                {
                    
                    temp.push_back(value);
                }
                mat.push_back(temp);
            }
            std::cout << "Fin" << std::endl;
        }

        Vector<T,N> at(size_t row)
        {
            if((row>=M) || (row<0)) throw runtime_error("Index non conforme");
            Vector<T,N> vect;
            for(int i =0;i<N;i++)
            {
                vect.vec[i] = mat[row][i];
            }
            return vect;
        }

        T at(size_t row,size_t col)
        {
            if(row>=M || row<0) throw runtime_error("Index non conforme");
            if(col>=N || col<0) throw runtime_error("Index non conforme");
            return mat[row][col];
        }
        Vector<T,N> operator[]( size_t index ) const
        {
            std::cout <<"la";
            Vector<T,N> vect;
            for(int i =0;i<N;i++)
            {
                vect.vec[i] = mat[index][i];
            }
            return vect;
        }
        Vector<T,N> &operator[]( size_t index ) 
        {
            std::cout <<"ici";
            Vector<T,N> vect;
           for(int i =0;i <=N;i++)
            {
                vect.vec[i] = mat[index][i];
            }
            return vect;
        }
        Matrix<T,M,N> &operator+=( const Matrix<T,M,N> & m)
        {
            for(int row=0;row<M;row++)
            {
                for(int col=0;col<N;col++)
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
        return true;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> inverse( const Matrix<T,M,N> & )
    {
        if(N != M)return NAN;
        Matrix<T,M,N> m;

        return m;

    }
    template <class T,size_t M,size_t N>
    bool isnan( const Matrix<T,M,N> &m )
    {
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                if(std::isnan(m.mat[row][col])) return true;
            }
        }
        return false;
    }
    template <class T,size_t M,size_t N>
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
    template <class T,size_t M,size_t N>
    bool operator!=( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        return !(m1==m2);
        /*for(int row=0;row<M;row++)
            {
                for(int col=0;col<N;col++)
                {
                    if(m1.mat[row][col] == m2.mat[row][col])return false;
                }
            }
        return true;*/
    }
    template <class T,size_t M, size_t N>
    std::ostream& operator<<(std::ostream &out, const Matrix<T,M,N> &m ){
        for(int row=0;row<M;row++)
            {
                out <<"{";
                for(int col=0;col<N;col++)
                {
                    out << m.mat[row][col] <<" " ;
                }
                out<< "}" << endl;
            }
        return out;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator+( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        Matrix<T,M,N> mat = Matrix<T,M,N>();
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] = m1.mat[row][col] + m2.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator-( const Matrix<T,M,N> &m ){
        Matrix<T,M,N> mat = Matrix<T,M,N>();
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] = - m.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator-( const Matrix<T,M,N> &m1, const Matrix<T,M,N> &m2 ){
        Matrix<T,M,N> mat = Matrix<T,M,N>();
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] = m1.mat[row][col] - m2.mat[row][col];
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator*( const T &scalar, const Matrix<T,M,N> &m ){
     Matrix<T,M,N> mat = Matrix<T,M,N>(m);
        for(int row=0;row<M;row++)
        {
            for(int col=0;col<N;col++)
            {
                mat.mat[row][col] *= scalar;
            }
        }
        return mat;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator*( const Matrix<T,M,N> &m, const T &scalar ){
        return m * scalar;
    }
    template <class T,size_t M,size_t N>
    Vector<T,M> operator*( const Matrix<T,M,N> &m, const Vector<T,N> &v){
        Vector<T,M> mult = Vector<T,M>();
        for(int i=0;i<M;i++)
        {
            mult[i] = 0;
            for(int j =0; j<N;j++)
            {
                mult[i] += m.mat[i][j] * v.vec[j];
            }
        }
        return mult;
    }
    template <class T,size_t M,size_t N,size_t O>
    Matrix<T,M,O> operator*( const Matrix<T,M,N> &m1, const Matrix<T,N,O> &m2 ){
        Matrix<T,M,O> mat = Matrix<T,M,O>();
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
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> operator/( const Matrix<T,M,N> & m, const T & s ){
        return m* (1/s);
    }
    template <class T,size_t M,size_t N>
    std::string to_string( const Matrix<T,M,N> &m ){
        return "";
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> transpose( const Matrix<T,M,N> &m ){
        Matrix<T,N,M> mat = Matrix<T,M,N>();
        for(int row=0;row<N;row++)
        {
            for(int col=0;col<M;col++)
            {
                mat[row][col] = m.mat[col][row];
            }
        }
        return mat;
    }
    /*
    template <class T,size_t M,size_t N>
	std::ostream &operator <<(std::ostream &s, const Matrix<T,M,N> &v)
	{
		s <<  "La chaine de taille  <<: " ;
		s << endl;
		return s;
	}*/
}
#endif
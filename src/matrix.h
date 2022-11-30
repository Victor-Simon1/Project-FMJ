
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
            //mat =vector<vector<T>>();
            /*
            for(int i=0;i<M;i++)
            {
                vector<T> v1;
                for(int i=0;i<N;i++)
                {
                    v1.push_back(0);
                }
                mat.push_back(v1);
            }  */
            
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
            }  */ 
           /*/*/
           Vector<T,N> v;
           int i= 0;
           for(auto vect:list)
           {
                
              //  for(T value:vect)
                //{
                    
                    v= Vector<T,N>(vect);
                    //std::cout << "init" << v<< std::endl;
                    mat.vec[i] = v;
                    i++;
                    //std::cout << "mat" << mat << std::endl;
               // }
           }
        }
        Matrix(const Matrix<T,M,N> &m)
        {

            
            mat =Vector<Vector<T,N>,M>();
            int i=0,j=0;
            for( i=0;i<M;i++)
            {
                for(j=0;j<N;j++)
                {
                  mat.vec[i][j] = m.mat.vec[i][j];  
                }
            }
            /*
            for(Vector<T,N> v : m.mat.vec)
            {
                for(T value:v)
                    mat.vec[i][++j] = value;
                i++;
                /*
                for(T value: v)
                {
                    
                    temp.push_back(value);
                }
                mat.push_back(temp);
            }*/
           // std::cout << "Fin" << std::endl;
        }

        Vector<T,N> at(size_t row)
        {
            if((row>=M) || (row<0)) throw runtime_error("Index non conforme");
           /* Vector<T,N> vect;
            for(int i =0;i<N;i++)
            {
                vect.vec[i] = mat.vec[row].vec[i];
            }*/
            return mat.vec[row];
        }

        T at(size_t row,size_t col)
        {
            if(row>=M || row<0) throw runtime_error("Index non conforme");
            if(col>=N || col<0) throw runtime_error("Index non conforme");
            //std::cout <<row << " "<< col << " " <<mat.vec[row][col] <<std::endl;
            return mat.vec[row][col];
        }
        Vector<T,N> operator[]( size_t index ) const
        {
            //std::cout <<"la";
           /* Vector<T,N> vect;
            for(int i =0;i<N;i++)
            {
                std::cout <<"la";
                vect.vec[i] = mat[index][i];
            }*/
            return mat.vec[index];
        }
        Vector<T,N> &operator[]( size_t index ) 
        {
          //  std::cout <<"ici";
           /* Vector<T,N> vect;
           for(int i =0;i <=N;i++)
            {
                vect.vec[i] = mat[index][i];
            }*/
            return mat.vec[index];
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
    float findDeterminant(Matrix<T,M,N> m){
        float det=0; // here det is the determinant of the matrix.
        for(int r = 0; r < N; r++){
            det = det + (m.mat[0][r] * (m.mat[1][(r+1)%3] * m.mat[2][(r+2)%3] - m.mat[1][(r+2)%3] * m.mat[2][(r+1)%3]));
        }
        return det;
    }
    template <class T,size_t M,size_t N>
    Matrix<T,M,N> inverse( const Matrix<T,M,N> & m)
    {
        if(N != M)return NAN;
          for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                cout<<((m.mat[(c+1)%3][(r+1)%3] * m.mat[(c+2)%3][(r+2)%3]) - (m.mat[(c+1)%3][(r+2)%3] * m.mat[(c+2)%3][(r+1)%3]))<<"\t";
            }
            cout<<endl;
        }
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
        std::cout << "Matrice de taille (" << M <<","<<N<<")"<<std::endl;
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
        return  scalar * m;
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
        return (1/s) * m;
    }
    template <class T,size_t M,size_t N>
    std::string to_string( const Matrix<T,M,N> &m ){
        std::string s;
        s.append("(");
        std::ostringstream strs;

        for(int i=0;i<M;i++)
        {
            s.append("(");
            for(int j=0;j<N;j++)
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
        //std::cout << s << std::endl;
        return s;
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
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <vector>
#include <cmath>
#include <float.h>
#include <limits>  
namespace aline
{
	template <class T,size_t N>
	class Vector
	{

	public:
		std::vector<T> vec;
		//Constructors
		Vector()
		{
			vec =   std::vector<T>();
			T base = T();
			for(int i=0;i<N;i++)
				vec.push_back(base);
		}
		Vector(std::initializer_list<T> l)
		{
			vec =   std::vector<T>();
			for(T value:l)
				vec.push_back(value);
		}
		Vector(const Vector<T, N>& v)
		{
			vec = std::vector<T>();
			for (int i = 0; i < N; i++)
			{
				vec.push_back( v.vec[i]);
			}
		}
		~Vector()
		{
		}
		//Method
		T norm() const
		{
			return sqrt(dot(*this, *this));
		}
		T at(size_t index) const
		{
			if (index >= N || index < 0)
			{
				throw std::runtime_error("Aled");
			}
			return vec[index];
		}
		T operator[](size_t index) const
		{
			return vec[index];
		}
		T& operator[](size_t index)
		{
			return vec[index];
		}
		Vector<T, N>& operator+=(const Vector<T, N>& v)
		{
			for (int i = 0; i < N; i++)
			{
				vec[i] = vec[i] + v.vec[i];
			}
			return *this;
		}
		
		T sq_norm() const
		{
			return sqrt(norm());
		}
	};

		template <class T,size_t N> Vector<T, N> cross(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			if (N < 3) throw std::runtime_error("Less than 3");
			Vector<T, N> crossproduct = Vector<T,N>();
			
			/*for (int i = 0; i < N; i++)
			{
				if (i < 3) crossproduct.vec[i] = v1.vec[N-i-1] * v2.vec[N-i] - v1.vec[N-i] * v2.vec[N-i-1];
				else crossproduct.vec[i] = 0;
			}*/

			crossproduct.vec[0] = v1.vec[2] * v2.vec[2] - v2.vec[2] * v1.vec[1];
			crossproduct.vec[1] = v1.vec[2] * v2.vec[0] - v2.vec[0] * v1.vec[2];
			crossproduct.vec[2] = v1.vec[0] * v2.vec[1] - v2.vec[1] * v1.vec[0];
			//std::cout << crossproduct.vec[0] << std::endl
			return crossproduct;
		}
		template <class T,size_t N> T dot(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			T sum = T();
			for (int i = 0; i < N; i++)
			{
				sum += v1.vec[i] * v2.vec[i];
			}
			return sum;
		}
		template <class T,size_t N> bool isnan(const Vector<T,N>& v)
		{
			for (int i = 0; i < N; i++)
			{
				if (std::isnan(v.vec[i])) return true;
			}
			return false;
		}
		template <class T,size_t N> bool is_unit(const Vector<T, N>& v)
		{
			if (v.norm() -1 < 0.0001) return true;
			return false;
		}
		template <class T,size_t N> bool nearly_equal(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{	
			for (int i = 0; i < N; i++)
			{
				const float epsilon = std::numeric_limits<float>::epsilon();
				T value =std::fabs(v1.vec[i]-v2.vec[i]);
				T max = std::max(std::abs(v1.vec[i]),std::abs(v2.vec[i]));

				if(value  > max*epsilon)
				{
					return false;
				}
			}
			return true;
		}
		
		template <class T,size_t N> bool operator==(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			for (int i = 0; i < N; i++)
			{
				if(v1.vec[i] != v2.vec[i]) return false;
			}
			return true;
		}
		template <class T,size_t N> bool operator!=(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			for (int i = 0; i < N; i++)
			{
				if(v1.vec[i] != v2.vec[i]) return false;
			}
			return true;
		}
		template <class T,size_t N> std::ostream& operator<<(std::ostream& out, const Vector<T,N> &v)
		{
			out << "vecteur de taille " <<  v.vec.size()<<std::endl;
			out << "{ ";
			for(int i = 0;i< v.vec.size();i++)
				out << v.vec[i]<< " ";
			out <<"}" <<std::endl;
			return out;
		}
		template <class T,size_t N> Vector<T, N> operator+(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			Vector<T,N> add = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				add[i] = v1.vec[i] + v2.vec[i];
			}
			return add;
		}
		template <class T,size_t N> Vector<T, N> operator-(const Vector<T, N>& v) 
		{
			Vector<T,N> negation = Vector<T,N>();
			for(int i=0;i<N;i++)
			{
				negation.vec[i] = -v.vec[i];
			}
			return negation;
		}
		template <class T,size_t N> Vector<T, N> operator-(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			Vector<T,N> sub = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				sub[i] = v1.vec[i] - v2.vec[i];
			}
			return sub;
		}
		template <class T,size_t N> Vector<T, N> operator*(const T& scalarValue, const Vector<T, N>& v)
		{
			Vector<T,N> scalar = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				scalar[i] = scalarValue * v.vec[i];
			}
			return scalar;
		}
		template <class T,size_t N> Vector<T, N> operator*(const Vector<T, N>& v, const T& scalarValue)
		{
			return scalarValue * v;
			/*
			Vector<T,N> scalar = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				scalar[i] = scalarValue * v.vec[i];
			}
			return scalar;*/
		}
		template <class T,size_t N> Vector<T, N> operator*(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			Vector<T,N> scalar = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				scalar[i] = v1.vec[i] * v2.vec[i];
			}
			return scalar;
		}
		template <class T,size_t N> Vector<T, N> operator/(const Vector<T, N>& v, const T& scalarValue)
		{
			return (1/scalarValue) * v;
			/*
			Vector<T,N> scalar = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				scalar[i] = v.vec[i] / scalarValue;
			}
			return scalar;*/
		}
		template <class T,size_t N> std::string to_string(const Vector<T, N>& v)
		{
			return "Vector of size " ;
		}
		template <class T,size_t N> Vector<T, N> unit_vector(const Vector<T, N>& v)
		{
			Vector<T,N> unit = Vector<T,N>(v);
			for(int i= 0;i<N;i++)
			{
				unit[i] /= v.sq_norm();
			}
			return v * (1/v.norm());
		}
		template <class T,size_t N> T norm(const Vector<T, N>& v)
		{
			return v.norm();
		}

};

#endif

#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <vector>
#include <cmath>

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
			vec =  std::vector<T>();
			for(int i=0;i<N;i++)
				vec.push_back(0);
		}
		Vector(std::initializer_list<T> l){
			vec = l;
		}
		Vector(const Vector<T, N>& v)
		{
			vec =  std::vector<T>();
			for (int i = 0; i < N; i++)
			{
				vec.push_back( v.vec[i]);
			}
		}

		//Method
		T norm() const
		{
			return dot(*this, *this);
		}
		T at(size_t index) const
		{
			if (index > N || index < 0)
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
			for (int i = 0; i < N; i++)
			{
				if (i < 3) crossproduct.vec[i] = v1.vec[N-i-1] * v2.vec[N-i] - v1.vec[N-i] * v2.vec[N-i-1];
				else crossproduct.vec[i] = 0;
			}
			return crossproduct;
		}
		template <class T,size_t N> T dot(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			int sum = 0;
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
				if (v.vec[i] == NAN) return true;
			}
			return false;
		}
		template <class T,size_t N> bool is_unit(const Vector<T, N>& v)
		{
			std::cout << v.norm();
			if (v.norm() == 1) return true;
			return false;
		}
		template <class T,size_t N> bool nearly_equal(const Vector<T, N>& v1, const Vector<T, N>& v2)
		{
			if (v1.norm() - v2.norm() < 0.1)
				return true;
			return false;
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
			out << "vecteur de taille " <<  v.vec.size() << "/" <<N <<std::endl;
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
				negation.vec[i] = v.vec[i];
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
			Vector<T,N> scalar = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				scalar[i] = scalarValue * v.vec[i];
			}
			return scalar;
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
			Vector<T,N> scalar = Vector<T,N>();
			for(int i =0;i<N;i++)
			{
				scalar[i] = v.vec[i] / scalarValue;
			}
			return scalar;
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
			
			return unit;
		}
		template <class T,size_t N> T norm(const Vector<T, N>& v)
		{
			return sqrt(v.norm());
		}
		//template <class T,size_t N>
	//ostream &operator <<(ostream &s, const Vector<T,N> &v);
};

#endif

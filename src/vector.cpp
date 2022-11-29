#include "vector.h"
#include <cmath>
#include <initializer_list>
#include <vector>

namespace aline {
/*
	template <class T,size_t N>
	Vector<T, N>::Vector()
	{
		vec = std::vector<T>();
	}
	template <class T,size_t N>
	Vector<T, N>::Vector(std::initializer_list<T> l ) 
	{
		vec = l;
	}
	template <class T,size_t N>
	Vector<T, N>::Vector(const Vector<T, N>& v)
	{
		vec = vector();
		for (int i = 0; i < N; i++)
		{
			vec.push_back( v[i]);
		}
	}
	template <class T,size_t N>
	T Vector<T,N>::at(size_t index) const
	{
		if (index > N || index < 0)
		{
			throw runtime_error("index non conforme");
		}
		return vec[index];
	}
	template <class T,size_t N>
	T Vector<T,N>::operator[](size_t index) const
	{
		return vec[index];
	}
	template <class T,size_t N>
	T& Vector<T,N>::operator[](size_t index)
	{
		return &vec[index];
	}
	template <class T,size_t N>
	Vector<T, N>& Vector<T,N>::operator+=(const Vector<T, N>& v) 
	{
		for (int i = 0; i < N; i++)
		{
			vec[i] = vec[i] + v[i];
		}
		return *this;
	}
	template <class T,size_t N>
	Vector<T, N> cross(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		if (N < 3) throw runtime_error("Less than 3");
		Vector<T, N> crossproduct = Vector();
		for (int i = 0; i < N; i++)
		{
			if (i < 3) crossproduct.vec[i] = v1[2-i-1] * v2[2-i] - v1[2-i] * v2[2-i-1];
			else crossproduct.vec[i] = 0;
		}
	}
	template <class T,size_t N>
	T dot(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += v1[i] * v2[i];
		}
		return sum;
	}
	template <class T,size_t N>
	bool isnan(const Vector<T,N>& v)
	{
		for (int i = 0; i < N; i++)
		{
			if (vec[i] == "Nan") return true;
		}
		return false;
	}
	template <class T,size_t N>
	bool is_unit(const Vector<T, N>& v)
	{
		if (v.norm() == 1) return true;
		return false;
	}
	template <class T,size_t N>
	bool nearly_equal(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		if (v1.norm() - v2.norm() < 0.1)
			return true;
		return false;
	}
	template <class T,size_t N>
	T norm()
	{
		return dot(*this, *this);
	}
	template <class T,size_t N>
	bool operator==(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		for (int i = 0; i < N; i++)
		{
			if(v1.vec[i] != v2.vec[i]) return false
		}
		return true;
	}
	template <class T,size_t N>
	bool operator!=(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		for (int i = 0; i < N; i++)
		{
			if (v1.vec[i] == v2.vec[i]) return false
		}
		return true;
	}
	template <class T,size_t N>
	Vector<T, N> operator+(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		Vector<T,N> add = Vector();
		for(int i =0;i<N;i++)
		{
			add[i] = v1.vec[i] + v2.vec[i];
		}
		return add;
	}
	template <class T,size_t N>
	Vector<T, N> operator-(const Vector<T, N>& v1)
	{
		Vector<T,N> negation = Vector();
		for(int i=0;i<N;i++)
		{
			negation.vec[i] = vec[i];
		}
		return negation;
	}
	template <class T,size_t N>
	Vector<T, N> operator-(const Vector<T, N>& v1,const Vector<T, N>& v2)
	{
		Vector<T,N> sub = Vector();
		for(int i =0;i<N;i++)
		{
			sub[i] = v1.vec[i] - v2.vec[i];
		}
		return sub;
	}
	template <class T,size_t N>
	Vector<T, N> operator*(const T& scalarValue, const Vector<T, N>& v)
	{
		Vector<T,N> scalar = Vector();
		for(int i =0;i<N;i++)
		{
			scalar[i] = scalarValue * v.vec[i];
		}
		return scalar;
	}
	template <class T,size_t N>
	Vector<T, N> operator*(const Vector<T, N>& v,const T& scalarValue)
	{
		return scalarValue*v;
		Vector<T,N> scalar = Vector();
		for(int i =0;i<N;i++)
		{
			scalar[i] = scalarValue * v.vec[i];
		}
		return scalar;
	}
	template <class T,size_t N>
	Vector<T, N> operator*(const Vector<T, N>& v1,const Vector<T, N>& v2)
	{
		Vector<T,N> scalar = Vector();
		for(int i =0;i<N;i++)
		{
			scalar[i] = v1.vec[i] * v2.vec[i];
		}
		return scalar;
	}
	template <class T,size_t N>
	Vector<T, N> operator/(const Vector<T, N>& v,const T& scalarValue)
	{
		Vector<T,N> scalar = Vector();
		for(int i =0;i<N;i++)
		{
			scalar[i] = v.vec[i] / scalarValue;
		}
		return scalar;
	}
	template <class T,size_t N>
	T Vector<T,N>::sq_norm()
	{
		return sqrt(norm());
	}

	template <class T,size_t N>
	std::string to_string( const Vector<T,N> & v)
	{
		std::cout << "Vector of size "<< N << ":(" << v <<")" << endl;
	}
	template <class T,size_t N>
	Vector<T, N> unit_vector(const Vector<T, N>& v)
	{
		Vector<T,N> unit = Vector(v);
		for(int i= 0;i<N;i++)
		{
			unit[i] /= v.sq_norm();
		}
	}
	template <class T,size_t N>
	std::ostream &operator <<(std::ostream &s, const Vector<T,N> &v)
	{
		s <<  "La chaine de taille est : " ;
		s << endl;
		return s;
	}

*/
}

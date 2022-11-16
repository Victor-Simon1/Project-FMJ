#include "vector.h"
#include <initializer_list>

namespace aline {

	template <class T,class N>
	Vector<T, N>::Vector()
	{
		vec = new T[N];
	}
	template <class T,class N>
	Vector<T, N>::Vector(std::initializer_list<Vector<T, N>>)
	{

	}
	template <class T,class N>
	Vector<T, N>::Vector(const Vector<T, N>& v)
	{
		vec = new T[N];
		for (int i = 0; i < N; i++)
		{
			vec[i] = v[i];
		}
	}
	template <class T,class N>
	T Vector<T,N>::at(size_t index) const
	{
		if (index > N || index < 0)
		{
			throw runtime_error("index non conforme");
		}
		return vec[index];
	}
	template <class T,class N>
	T Vector<T,N>::operator[](size_t index) const
	{
		return vec[index];
	}
	template <class T,class N>
	T& Vector<T,N>::operator[](size_t index)
	{
		return &vec[index];
	}
	template <class T,class N>
	Vector<T, N>& Vector<T,N>::operator+=(const Vector<T, N>& v) 
	{
		for (int i = 0; i < N; i++)
		{
			vec[i] = vec[i] + v[i];
		}
		return *this;
	}
	template <class T,class N>
	Vector<T, N> Vector<T,N>::cross(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		if (N < 3) throw runtime_error("Less than 3");
		Vector<T, N> crossproduct = Vector();
		for (int i = 0; i < N; i++)
		{
			if (i < 3) crossproduct.vec[i] = v1[2-i-1] * v2[2-i] - v1[2-i] * v2[2-i-1];
			else crossproduct.vec[i] = 0;
		}
	}
	template <class T,class N>
	T Vector<T,N>::dot(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += v1[i] * v2[i];
		}
		return sum;
	}
	template <class T,class N>
	bool Vector<T,N>::isnan(const Vector<T,N>& v)
	{
		for (int i = 0; i < N; i++)
		{
			if (vec[i] == "Nan") return true;
		}
		return false;
	}
	template <class T,class N>
	bool Vector<T,N>::is_unit(const Vector<T, N>& v)
	{
		if (v.norm() == 1) return true;
		return false;
	}
	template <class T,class N>
	bool Vector<T,N>::nearly_equal(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		if (v1.norm() - v2.norm() < 0.1)
			return true;
		return false;
	}
	template <class T,class N>
	T Vector<T,N>::norm()
	{
		return sqrt(dot(*this, *this));
	}
	template <class T,class N>
	bool Vector<T,N>::operator==(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		for (int i = 0; i < N; i++)
		{
			if(v1.vec[i] != v2.vec[i]) return false
		}
		return true;
	}
	template <class T,class N>
	bool Vector<T,N>::operator!=(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		for (int i = 0; i < N; i++)
		{
			if (v1.vec[i] == v2.vec[i]) return false
		}
		return true;
	}
	template <class T,class N>
	Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>&, const Vector<T, N>&)
	{
		Vector<T,N> add = Vector();
		for(int i =0;i<N;i++)
		{
			add[i] = v1.vec[i] + v2.vec[i];
		}
		return add;
	}
	Vector<T, N> operator-(const Vector<T, N>&)
	{
		for(int i=0<)
	}
	Vector<T, N> operator-(const Vector<T, N>& v1,const Vector<T, N>& v2)
	{
		Vector<T,N> sub = Vector();
		for(int i =0;i<N;i++)
		{
			sub[i] = v1.vec[i] - v2.vec[i];
		}
		return sub;
	}
}

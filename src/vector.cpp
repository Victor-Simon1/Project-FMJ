#include "vector.h"
#include <initializer_list>

namespace aline {
	Vector<T, N>::Vector()
	{
		vec = new T[N];
	}
	Vector<T, N>::Vector(std::initializer_list<Vector<T, N>>)
	{

	}
	Vector<T, N>::Vector(const Vector<T, N>& v)
	{
		vec = new T[N];
		for (int i = 0; i < N; i++)
		{
			vec[i] = v[i];
		}
	}

	T Vector::at(size_t index) const
	{
		if (index > N || index < 0)
		{
			throw runtime_error("index non conforme");
		}
		return vec[index];
	}

	T Vector::operator[](size_t index)
	{
		return vec[index];
	}

	T& Vector::operator[](size_t index)
	{
		return &vec[index];
	}

	Vector<T, N>& Vector::operator+=(const Vector<T, N>& v) 
	{
		for (int i = 0; i < N; i++)
		{
			vec[i] = vec[i] + v[i];
		}
		return *this;
	}

	Vector<T, N> Vector::cross(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		if (N < 3) throw runtime_error("Less than 3");
		Vector<T, N> crossproduct = Vector();
		for (int i = 0; i < N; i++)
		{
			if (i < 3) crossproduct.vec[i] = v1[2-i-1] * v2[2-i] - v1[2-i] * v2[2-i-1];
			else crossproduct.vec[i] = 0;
		}
	}
	T Vector::dot(const Vector<T, N>& v1, const Vector<T, N>& v2)
	{
		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += v1[i] * v2[i];
		}
		return sum;
	}
	bool Vector::isnan(const Vector& v)
	{
		for (int i = 0; i < N; i++)
		{
			if (vec[i] == "Nan") return true;
		}
		return false;
	}

	bool Vector::is_unit(const Vector<T, N>& v)
	{
		if (v.norm() == 1) return true;
		return false;
	}
	bool nearly_equal(const Vector<T, N>&, const Vector<T, N>&)
	{

	}
	T Vector::norm()
	{
		return sqrt(dot(*this, *this));
	}
}

#ifndef ALINE_H
#define ALINE_H
#include <iostream>
namespace aline
{
	template <class T,class N>
	class Vector
	{

	public:
		T* vec;
		//Constructors

		Vector();
		Vector(std::initializer_list<T>);
		Vector(const Vector<T, N>&);

		//Method
		T at(size_t) const;
		T operator[](size_t) const;
		T& operator[](size_t);
		Vector<T, N>& operator+=(const Vector<T, N>&);
		
		T sq_norm();
	};
		//Function
		
		template <class T,class N> Vector<T, N> cross(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> T dot(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> bool isnan(const Vector<T,N>&);
		template <class T,class N> bool is_unit(const Vector<T, N>&);
		template <class T,class N> bool nearly_equal(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> bool operator==(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> bool operator!=(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> std::ostream operator<<(std::ostream&, const Vector<T, N> v);
		template <class T,class N> Vector<T, N> operator+(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> Vector<T, N> operator-(const Vector<T, N>&);
		template <class T,class N> Vector<T, N> operator-(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> Vector<T, N> operator*(const T&, const Vector<T, N>&);
		template <class T,class N> Vector<T, N> operator*(const Vector<T, N>&, const T&);
		template <class T,class N> Vector<T, N> operator*(const Vector<T, N>&, const Vector<T, N>&);
		template <class T,class N> Vector<T, N> operator/(const Vector<T, N>& v, const T& s);
		template <class T,class N> std::string to_string(const Vector<T, N>&);
		template <class T,class N> Vector<T, N> unit_vector(const Vector<T, N>& v);
		template <class T,class N> T norm(const Vector<T, N>& v);
};

#endif

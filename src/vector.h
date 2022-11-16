
template <class T>
template <class N>
class Vector<T, N>
{

public:
	T* vec;
	//Constructors

	Vector();
	Vector(std::initializer_list<Vector<T, N>>);
	Vector(const Vector<T, N>&);

	//Method
	T at(size_t) const;
	T operator[](size_t) const;
	T& operator[](size_t);
	Vector<T, N>& operator+=(const Vector<T, N>&);

	//Function
	Vector<T, N> cross(const Vector<T, N>&, const Vector<T, N>&);
	T dot(const Vector<T, N>&, const Vector<T, N>&);
	bool isnan(const Vector&);
	bool is_unit(const Vector<T, N>&);
	bool nearly_equal(const Vector<T, N>&, const Vector<T, N>&);
	T Vector<T, N>::norm();
	bool operator==(const Vector<T, N>&, const Vector<T, N>&);
	bool operator==(const Vector<T, N>&, const Vector<T, N>&);
	std::ostream operator<<(std::ostream&, const Vector<T, N> v);
	Vector<T, N> operator+(const Vector<T, N>&, const Vector<T, N>&);
	Vector<T, N> operator-(const Vector<T, N>&);
	Vector<T, N> operator-(const Vector<T, N>&, const Vector<T, N>&);
	Vector<T, n> operator*(const T&, const vector<T, N>&);
	Vector<T, n> operator*(const vector<T, N>&, const T&);
	Vector<T, n> operator*(const vector<T, N>&, const Vector<T, N>&);
	Vector<T, n> operator/(const Vector<T, N>& v, const T& s);
	T Vector<T, N>::sq_norm();
	std::string to_string(const Vector<T, N>&);
	Vector<T, N> unit_vector(const Vector<T, N>& v);

};
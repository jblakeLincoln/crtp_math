#ifndef VEC_H
#define VEC_H

/**
 * CRTP definitions of a standard vector classes, providing common vector
 * functionality without duplication.
 *
 * Vector types are derived from t_vec, passing in a type, a length, the
 * derived vector type, and optionally a variable member layout.
 */

#include <math.h>

/**
 * Default member for vector types simply leads back to an array.
 */
template<typename T, size_t len>
struct t_vec_members {
protected:
	T data[len] = { 0 };

public:
	T& operator[](size_t i) {
		return data[i];
	}

	const T& operator[](size_t i) const {
		return data[i];
	}

};

template<typename T, size_t len, typename t_vecx,
	typename members = t_vec_members<T, len>>
struct t_vec : members {
private:

	/**
	 * Copy construct 'this' to a t_vecx type.
	 */
	t_vecx this_to_vecx() const {
		t_vecx out;
		for(size_t i = 0; i < len; ++i)
			out[i] = data(i);
		return out;
	}

public:
	static constexpr size_t length = len;

	size_t m_length() const {
		return len;
	}

	T& data(size_t i) {
		return (*this)[i];
	}

	const T& data(size_t i) const {
		return (*this)[i];
	}

	/**********************************
	 * Construction and assignment
	 **********************************/

	t_vec() {
		for(size_t i = 0; i < len; ++i)
			data(i) = 0;
	}

	t_vec(const t_vecx &other) {
		for(size_t i = 0; i < len; ++i)
			data(i) = other[i];
	}

	t_vec(T in) {
		for(size_t i = 0; i < len; ++i)
			data(i) = in;
	}

	t_vecx& operator=(const t_vecx &other) {
		for(size_t i = 0; i < len; ++i)
			data(i) = other[i];
		return static_cast<t_vecx&>(*this);
	}

	/**********************************
	 * Operators with vector
	 **********************************/

	t_vecx operator+(const t_vecx &other) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] += other[i];
		return out;
	}

	t_vecx operator-(const t_vecx &other) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] -= other[i];
		return out;
	}

	t_vecx operator*(const t_vecx &other) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] *= other[i];
		return out;
	}

	t_vecx operator/(const t_vecx &other) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] /= other[i];
		return out;
	}

	/**********************************
	 * Shorthands with vector
	 **********************************/

	t_vecx& operator+=(const t_vecx &other) {
		for(size_t i = 0; i < len; ++i)
			data(i) += other[i];
		return static_cast<t_vecx&>(*this);
	}

	t_vecx& operator-=(const t_vecx &other) {
		for(size_t i = 0; i < len; ++i)
			data(i) -= other[i];
		return static_cast<t_vecx&>(*this);
	}

	t_vecx& operator*=(const t_vecx &other) {
		for(size_t i = 0; i < len; ++i)
			data(i) *= other[i];
		return static_cast<t_vecx&>(*this);
	}

	t_vecx& operator/=(const t_vecx &other) {
		for(size_t i = 0; i < len; ++i)
			data(i) /= other[i];
		return static_cast<t_vecx&>(*this);
	}

	/**********************************
	 * Operators with type
	 **********************************/

	t_vecx operator+(T in) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] += in;
		return out;
	}

	t_vecx operator-(T in) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] -= in;
		return out;
	}

	t_vecx operator*(T in) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] *= in;
		return out;
	}

	t_vecx operator/(T in) const {
		t_vecx out = this_to_vecx();
		for(size_t i = 0; i < len; ++i)
			out[i] /= in;
		return out;
	}

	/**********************************
	 * Shorthands with type
	 **********************************/

	t_vecx& operator+=(T in) {
		for(size_t i = 0; i < len; ++i)
			data(i) += in;
		return static_cast<t_vecx&>(*this);
	}

	t_vecx& operator-=(T in) {
		for(size_t i = 0; i < len; ++i)
			data(i) -= in;
		return static_cast<t_vecx&>(*this);
	}

	t_vecx& operator*=(T in) {
		for(size_t i = 0; i < len; ++i)
			data(i) *= in;
		return static_cast<t_vecx&>(*this);
	}

	t_vecx& operator/=(T in) {
		for(size_t i = 0; i < len; ++i)
			data(i) /= in;
		return static_cast<t_vecx&>(*this);
	}

	/**********************************
	 * Negation
	 **********************************/

	t_vecx operator-() const {
		t_vecx out;
		for(size_t i = 0; i < len; ++i)
			out[i] = -data(i);
		return out;
	}

	/**********************************
	 * Comparison
	 **********************************/

	bool operator==(const t_vecx &other) const {
		for(size_t i = 0; i < len; ++i) {
			if(data(i) != other[i])
				return false;
		}
		return true;
	}

	bool operator!=(const t_vecx &other) const {
		return !(*this == other);
	}

	/**********************************
	 * Additional functions
	 **********************************/

	static T magnitude(const t_vecx &in) {
		T out = 0;
		for(size_t i = 0; i < len; ++i)
			out += in[i] * in[i];
		return sqrt(out);
	}

	static t_vecx normalise(const t_vecx &in) {
		T v = magnitude(in);
		t_vecx out(in);

		for(size_t i = 0; i < len; ++i)
			out[i] /= v;
		return out;
	}

	static T dot(const t_vecx &a, const t_vecx &b) {
		T top = 0;
		T bottom = 0;
		T s_a = 0;
		T s_b = 0;

		for(size_t i = 0; i < len; ++i) {
			top += a[i] * b[i];
			s_a += a[i] * a[i];
			s_b += b[i] * b[i];
		}

		bottom = sqrt(s_a) * sqrt(s_b);
		T theta = top / bottom;
		return magnitude(a) * magnitude(b) * theta;
	}
};

/**
 * operator[] declaration for named member access, starting at
 * from starting pointer 'x'.
 */
#define T_VEC_NAMED_MEMBER_ACCESS(x)           \
	T& operator[](size_t i) {                  \
		return (&x)[i];                        \
	}                                          \
	const T& operator[](size_t i) const {      \
		return (&x)[i];                        \
	}                                          \


/* Default constructor and copy constructor. */
#define T_VEC_DEFAULTS(tv, tvb)                \
	tv() {}                                    \
	tv(T in) : tvb(in) {}                      \
	tv(const tv &v) : tvb(v) {}


template<typename T>
struct t_vec2_members {
	T_VEC_NAMED_MEMBER_ACCESS(x)
	union { T x, r; };
	union { T y, g; };
};

template<typename T>
struct t_vec3_members {
	T_VEC_NAMED_MEMBER_ACCESS(x)
	union { T x, r; };
	union { T y, g; };
	union { T z, b; };
};

template<typename T>
struct t_vec4_members {
	T_VEC_NAMED_MEMBER_ACCESS(x)
	union { T x, r; };
	union { T y, g; };
	union { T z, b; };
	union { T w, a; };
};

#define T_VEC2 t_vec<T, 2, t_vec2<T>, t_vec2_members<T>>
#define T_VEC3 t_vec<T, 3, t_vec3<T>, t_vec3_members<T>>
#define T_VEC4 t_vec<T, 4, t_vec4<T>, t_vec4_members<T>>
template<typename T>
struct t_vec2 : T_VEC2 {
	T_VEC_DEFAULTS(t_vec2, T_VEC2);

	t_vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}
};

template<typename T>
struct t_vec3 : T_VEC3 {
	T_VEC_DEFAULTS(t_vec3, T_VEC3);

	t_vec3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/**
	 * vec3-only cross product.
	 */
	static t_vec3 Cross(const t_vec3 &a, const t_vec3 &b) {
		return t_vec3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}
};

template<typename T>
struct t_vec4 : T_VEC4 {
	T_VEC_DEFAULTS(t_vec4, T_VEC4);

	t_vec4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};

#undef T_VEC2
#undef T_VEC3
#undef T_VEC4
#undef T_VEC_DEFAULTS
#undef T_VEC_NAMED_MEMBER_ACCESS

typedef t_vec2<float> vec2;
typedef t_vec3<float> vec3;
typedef t_vec4<float> vec4;

typedef t_vec2<double> vec2d;
typedef t_vec3<double> vec3d;
typedef t_vec4<double> vec4d;

typedef t_vec2<int> vec2i;
typedef t_vec3<int> vec3i;
typedef t_vec4<int> vec4i;

#endif

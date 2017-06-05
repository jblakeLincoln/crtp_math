#ifndef MAT_H
#define MAT_H

/**
 * CRTP definitions of matrix classes, everything in between 2x2 to 4x4.
 *
 * Matrix types are composed of two vectors (rows and columns).
 * Default constructor and type T constructor provide an identity matrix.
 *
 * Credit to glm for some of the mat4 functions.
 */

#include "vec.h"

#define PI 3.14159265358979323846

template <typename T>
static T to_radians(T in) {
	return in * (PI / 180);
}

template<typename T, typename Row, typename Col, typename t_matxx>
struct t_mat {
private:
	Col data[Row::length];

	t_matxx this_to_matxx() const {
		t_matxx out;
		for(size_t i = 0; i < rows; ++i)
				out[i] = data[i];
		return out;
	}

public:
	static constexpr size_t rows = Row::length;
	static constexpr size_t cols = Col::length;

	t_mat() {
		for(size_t i = 0; i < rows && i < cols; ++i)
			data[i][i] = 1;
	}

	t_mat(const t_matxx &other) {
		for(size_t i = 0; i < rows; ++i)
			data[i] = other[i];
	}

	t_mat(T in) {
		for(size_t i = 0; i < rows && i < cols; ++i)
			data[i][i] = in;
	}


	t_matxx& operator=(const t_matxx &other) {
		for(size_t i = 0; i < rows; ++i)
			data[i] = other[i];
		return static_cast<t_matxx&>(*this);
	}

	/**********************************
	 * Access
	 **********************************/

	Col& operator[](size_t i) {
		return data[i];
	}

	const Col& operator[](size_t i) const {
		return data[i];
	}

	/**********************************
	 * Operator with mat
	 **********************************/

	t_matxx operator+(const t_matxx &other) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] += other[i];
		return out;
	}

	t_matxx operator-(const t_matxx &other) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] -= other[i];
		return out;
	}

	t_matxx operator*(const t_matxx &other) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] *= other[i];
		return out;
	}

	t_matxx operator/(const t_matxx &other) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] /= other[i];
		return out;
	}

	/**********************************
	 * Shorthands with mat
	 ***********************************/

	t_matxx& operator+=(const t_matxx &other) {
		for(size_t i = 0; i < rows; ++i)
			data[i] += other[i];
		return static_cast<t_matxx&>(*this);
	}

	t_matxx& operator-=(const t_matxx &other) {
		for(size_t i = 0; i < rows; ++i)
			data[i] -= other[i];
		return static_cast<t_matxx&>(*this);
	}

	t_matxx& operator*=(const t_matxx &other) {
		for(size_t i = 0; i < rows; ++i)
			data[i] *= other[i];
		return static_cast<t_matxx&>(*this);
	}

	t_matxx& operator/=(const t_matxx &other) {
		for(size_t i = 0; i < rows; ++i)
			data[i] /= other[i];
		return static_cast<t_matxx&>(*this);
	}

	/**********************************
	 * Operators with type
	 **********************************/

	t_matxx operator+(T in) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] += in;
		return out;
	}

	t_matxx operator-(T in) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] -= in;
		return out;
	}


	t_matxx operator*(T in) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] *= in;
		return out;
	}

	t_matxx operator/(T in) const {
		t_matxx out = this_to_matxx();
		for(size_t i = 0; i < rows; ++i)
			out[i] /= in;
		return out;
	}

	/**********************************
	 * Shorthands with type
	 **********************************/

	t_matxx& operator+=(T in) {
		for(size_t i = 0; i < rows; ++i)
			data[i] += in;
		return static_cast<t_matxx&>(*this);
	}

	t_matxx& operator-=(T in) {
		for(size_t i = 0; i < rows; ++i)
			data[i] -= in;
		return static_cast<t_matxx&>(*this);
	}

	t_matxx& operator*=(T in) {
		for(size_t i = 0; i < rows; ++i)
			data[i] *= in;
		return static_cast<t_matxx&>(*this);
	}

	t_matxx& operator/=(T in) {
		for(size_t i = 0; i < rows; ++i)
			data[i] /= in;
		return static_cast<t_matxx&>(*this);
	}

	/**********************************
	 * Negation
	 **********************************/

	t_matxx operator-() const {
		t_matxx out;
		for(size_t i = 0; i < rows; ++i)
			out[i] = -data[i];
		return out;
	}

	/**********************************
	 * Comparison
	 **********************************/

	bool operator==(const t_matxx &other) const {
		for(size_t i = 0; i < rows; ++i) {
			if(data[i] != other[i])
				return false;
		}

		return true;
	}

	bool operator!=(const t_matxx &other) const {
		return !(*this == other);
	}
};

#define MATXX_DEFAULTS(tm, tmb)                                                \
	tm() {}                                                                 \
	tm(T in) : tmb(in) {} \
	tm(const tm &other) : tmb(other) {}

#define T_MAT2X2 t_mat<T, t_vec2<T>, t_vec2<T>, t_mat2x2<T>>
#define T_MAT2X3 t_mat<T, t_vec2<T>, t_vec3<T>, t_mat2x3<T>>
#define T_MAT2X4 t_mat<T, t_vec2<T>, t_vec4<T>, t_mat2x4<T>>
#define T_MAT3X2 t_mat<T, t_vec3<T>, t_vec2<T>, t_mat3x2<T>>
#define T_MAT3X3 t_mat<T, t_vec3<T>, t_vec3<T>, t_mat3x3<T>>
#define T_MAT3X4 t_mat<T, t_vec3<T>, t_vec4<T>, t_mat3x4<T>>
#define T_MAT4X2 t_mat<T, t_vec4<T>, t_vec2<T>, t_mat4x2<T>>
#define T_MAT4X3 t_mat<T, t_vec4<T>, t_vec3<T>, t_mat4x3<T>>
#define T_MAT4X4 t_mat<T, t_vec4<T>, t_vec4<T>, t_mat4x4<T>>

template<typename T>
struct t_mat2x2 : T_MAT2X2 {
	MATXX_DEFAULTS(t_mat2x2, T_MAT2X2);
};

template<typename T>
struct t_mat2x3 : T_MAT2X3 {
	MATXX_DEFAULTS(t_mat2x3, T_MAT2X3);
};

template<typename T>
struct t_mat2x4 : T_MAT2X4 {
	MATXX_DEFAULTS(t_mat2x4, T_MAT2X4);
};

template<typename T>
struct t_mat3x2 : T_MAT3X2 {
	MATXX_DEFAULTS(t_mat3x2, T_MAT3X2);
};

template<typename T>
struct t_mat3x3 : T_MAT3X3 {
	MATXX_DEFAULTS(t_mat3x3, T_MAT3X3);
};

template<typename T>
struct t_mat3x4 : T_MAT3X4 {
	MATXX_DEFAULTS(t_mat3x4, T_MAT3X4);
};

template<typename T>
struct t_mat4x2 : T_MAT4X2 {
	MATXX_DEFAULTS(t_mat4x2, T_MAT4X2);
};

template<typename T>
struct t_mat4x3 : T_MAT4X3 {
	MATXX_DEFAULTS(t_mat4x3, T_MAT4X3);
};

template<typename T>
struct t_mat4x4 : T_MAT4X4 {
	MATXX_DEFAULTS(t_mat4x4, T_MAT4X4);

	t_mat4x4(const vec4 &v1, const vec4 &v2, const vec4 &v3, const vec4 &v4) {
		this->data[0] = v1;
		this->data[1] = v2;
		this->data[2] = v3;
		this->data[3] = v4;
	}

	static t_mat4x4 perspective(T fov, T aspect, T znear, T zfar) {
		T rad = to_radians(fov);
		T tan_half_fov = tan(rad / static_cast<T>(2));
		t_mat4x4 out;

		out[0][0] = static_cast<T>(1) / (aspect * tan_half_fov);
		out[1][1] = static_cast<T>(1) / (tan_half_fov);
		out[2][2] = -(zfar + znear) / (zfar - znear);
		out[2][3] = -static_cast<T>(1);
		out[3][2] = -(static_cast<T>(2) * zfar * znear) / (zfar - znear);

		return out;
	}

	static t_mat4x4 ortho(T left, T right, T bottom, T top, T znear, T zfar)
	{
		t_mat4x4 out;
		out[0][0] = static_cast<T>(2) / (right - left);
		out[1][1] = static_cast<T>(2) / (top - bottom);
		out[2][2] = -static_cast<T>(2) / (zfar - znear);
		out[3][0] = -(right + left) / (right - left);
		out[3][1] = -(top + bottom) / (top - bottom);
		out[3][2] = -(zfar + znear) / (zfar - znear);

		return out;
	}

	static t_mat4x4 look_at(t_vec3<T> eye, t_vec3<T> centre, t_vec3<T> up) {
		t_vec3<T> f(t_vec3<T>::normalise(centre - eye));
		t_vec3<T> s(t_vec3<T>::normalise(t_vec3<T>::Cross(f, up)));
		t_vec3<T> u(t_vec3<T>::Cross(s, f));

		t_mat4x4 out;

		out[0][0] = s.x;
		out[1][0] = s.y;
		out[2][0] = s.z;
		out[0][1] = u.x;
		out[1][1] = u.y;
		out[2][1] = u.z;
		out[0][2] = -f.x;
		out[1][2] = -f.y;
		out[2][2] = -f.z;
		out[3][0] = -t_vec3<T>::dot(s, eye);
		out[3][1] = -t_vec3<T>::dot(u, eye);
		out[3][2] = t_vec3<T>::dot(f, eye);
		return out;
	}

	static t_mat4x4 translate(const t_mat4x4 &mat, const t_vec3<T> &v) {
		t_mat4x4 out(mat);
		out[3] = mat[0] * v[0] + mat[1] * v[1] + mat[2] * v[2] + mat[3];
		return out;
	}

	static t_mat4x4 rotate(const t_mat4x4 &mat, T angle, const t_vec3<T> &v) {
	    T c = cos(to_radians(angle));
	    T s = sin(to_radians(angle));

		t_mat4x4 rot(0.f);
		t_mat4x4 out;
		t_vec3<T> axis = t_vec3<T>::normalise(v);
		t_vec3<T> temp(axis * (1 - c));

		rot[0][0] = c + temp[0] * axis[0];
		rot[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
		rot[0][2] = 0 + temp[0] * axis[2] - s * axis[1];
		rot[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
		rot[1][1] = c + temp[1] * axis[1];
		rot[1][2] = 0 + temp[1] * axis[2] + s * axis[0];
		rot[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
		rot[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
		rot[2][2] = c + temp[2] * axis[2];

		out[0] = mat[0] * rot[0][0] + mat[1] * rot[0][1] + mat[2] * rot[0][2];
		out[1] = mat[0] * rot[1][0] + mat[1] * rot[1][1] + mat[2] * rot[1][2];
		out[2] = mat[0] * rot[2][0] + mat[1] * rot[2][1] + mat[2] * rot[2][2];
		out[3] = mat[3];

		return out;
	}

	static t_mat4x4 scale(const t_mat4x4 &mat, const t_vec3<T> &v) {
		t_mat4x4 out(mat);
		out[0] = mat[0] * v[0];
		out[1] = mat[1] * v[1];
		out[2] = mat[2] * v[2];
		out[3] = mat[3];
		return out;
	}
};

typedef t_mat2x2<float> mat2;
typedef t_mat2x3<float> mat2x3;
typedef t_mat2x4<float> mat2x4;
typedef t_mat3x2<float> mat3x2;
typedef t_mat3x3<float> mat3;
typedef t_mat3x4<float> mat3x4;
typedef t_mat4x2<float> mat4x2;
typedef t_mat4x3<float> mat4x3;
typedef t_mat4x4<float> mat4;

#undef MATXX_DEFAULTS
#undef T_MAT2X2
#undef T_MAT2X3
#undef T_MAT2X4
#undef T_MAT3X2
#undef T_MAT3X3
#undef T_MAT3X4
#undef T_MAT4X2
#undef T_MAT4X3
#undef T_MAT4X4

#endif

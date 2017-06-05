#if 0
time clang++ -fno-exceptions -fno-rtti -Wall -std=c++11 main.cpp && ./a.out
exit
#endif

/**
 * CRTP vector example. Classes defined:
 *   - vec2
 *   - vec3
 *   - vec4
 *   - mat2x2
 *   - mat2x3
 *   - mat2x4
 *   - mat3x2
 *   - mat3
 *   - mat3x4
 *   - mat3x2
 *   - mat4x3
 *   - mat4
 *
 *   The above are all typedefs of t_type<float>.
 *
 *   All vectors can:
 *     - + - / * other vectors of the same type, or their data type
 *     - shorthand + - / * with the same type T, or their own type
 *     - negate (-type)
 *     - compare
 *     - access through square brackets
 *
 *   Vectors have direct member access through .xyzw/.rgba members
 */

#include <stdio.h>
#include "vec.h"
#include "mat.h"

/**
 * Run through all implemented operators for vec/mat types.
 * Modifies input values.
 */
template<typename T>
void operator_test(T &a, T &b, void(*print_fnc)(const T&))
{
	T c;

	/* Full operators */
	printf("\n");

	c = a + b;
	printf("a + b:\t"); print_fnc(c);

	c = a - b;
	printf("a - b:\t"); print_fnc(c);

	c = a * b;
	printf("a * b:\t"); print_fnc(c);

	c = a / b;
	printf("a / b:\t"); print_fnc(c);

	/* Full operators  with data */
	printf("\n");

	c = a + 4;
	printf("a + 4:\t"); print_fnc(c);

	c = a - 2;
	printf("a - 4:\t"); print_fnc(c);

	c = a * 2;
	printf("a * 4:\t"); print_fnc(c);

	c = a / 2;
	printf("a / 4:\t"); print_fnc(c);

	/* Shorthands with vectors */
	printf("\n");

	a += b;
	printf("a += b:\t"); print_fnc(a);

	a -= b;
	printf("a -= b:\t"); print_fnc(a);

	a *= b;
	printf("a *= b:\t"); print_fnc(a);

	a /= b;
	printf("a /= b:\t"); print_fnc(a);

	/* Shorthands with data */
	printf("\n");

	a += 4;
	printf("a += 4:\t"); print_fnc(a);

	a -= 4;
	printf("a -= 4:\t"); print_fnc(a);

	a *= 4;
	printf("a *= 4:\t"); print_fnc(a);

	a /= 4;
	printf("a /= 4:\t"); print_fnc(a);

	/* Comparison: */
	printf("\n");

	printf("a == b:\t%s\n", a == b ? "true" : "false");
	printf("a != b:\t%s\n", a != b ? "true" : "false");
	printf("a == a:\t%s\n", a == a ? "true" : "false");
	printf("a != a:\t%s\n", a != a ? "true" : "false");
}

/* Print vec types */
template<typename vecT>
void printv(const vecT &in) {
	printf("{ ");
	for(size_t i = 0; i < vecT::length; ++i) {
		printf("%s%.6f%s", in[i] < 0 ? "" : " ", in[i],
				i != vecT::length - 1 ? ", " : " }\n");
	}
}

/* Print mat types */
template<typename matTxT>
void printm(const matTxT &in) {
	printf("\n{\n");
	for(size_t i = 0; i < matTxT::rows; ++i) {
		printf("\t");
		printv(in[i]);
	}
	printf("}\n\n");
}

/**
 * Set up vector types in the format:
 *  vec2 a = { 1, 2 }
 *  vec2 b = { 3, 4 }
 *
 * where the first value of 'b' follows the last value of 'a'.
 */
template<typename vecT>
void initialise_vecs(vecT &v1, vecT &v2) {
	for(size_t i = 0; i < vecT::length; ++i)
		v1[i] = i + 1;
	for(size_t i = 0; i < vecT::length; ++i)
		v2[i] = i + 1 + vecT::length;
}

/**
 * Set up mat types in the same format as vector types.
 */
template<typename matTxT>
void initialise_mats(matTxT &m1, matTxT &m2) {
	for(size_t i = 0; i < matTxT::rows; ++i)
		for(size_t j = 0; j < matTxT::cols; ++j)
			m1[i][j] = i * matTxT::rows + j + 1;

	for(size_t i = 0; i < matTxT::rows; ++i)
		for(size_t j = 0; j < matTxT::cols; ++j)
			m2[i][j] = (matTxT::rows + matTxT::cols) + i * matTxT::rows + j + 1;
}

template<typename vecT>
void vec_test(const char *label) {
	printf("\n*****************\n");
	printf("**** %s", label);
	printf("\n*****************\n");
	vecT a, b;
	initialise_vecs(a, b);
	operator_test<vecT>(a, b, &printv);

	printf("a:\t\t"); printv(a);
	printf("b:\t\t"); printv(b);
	printf("a/b dot:\t"); printf("%f\n", vecT::dot(a, b));
	printf("a magnitude:\t"); printf("%f\n", vecT::magnitude(a));
	printf("a normalise:\t"); printv(vecT::normalise(a));
}

template<typename matTxT>
void mat_test(const char *label) {
	printf("\n*****************\n");
	printf("**** %s", label);
	printf("\n*****************\n");
	matTxT a, b;
	initialise_mats(a, b);
	operator_test<matTxT>(a, b, &printm);

}

int main()
{
	vec_test<vec2>("vec2");
	vec_test<vec3>("vec3");
	vec_test<vec4>("vec4");

	mat_test<mat2>("mat2");
	mat_test<mat2x3>("mat2x3");
	mat_test<mat2x4>("mat2x4");
	mat_test<mat3x2>("mat3x2");
	mat_test<mat3>("mat3");
	mat_test<mat3x4>("mat3x4");
	mat_test<mat4x2>("mat4x2");
	mat_test<mat4x3>("mat4x3");
	mat_test<mat4>("mat4");

	/**
	 * Additional mat4 functions.
	 */
	{
		vec3 eye = vec3(12, 8, 4);
		vec3 centre;
		vec3 up = vec3(0, 1, 0);

		mat4 m = mat4::look_at(eye, centre, up);
		m = mat4::translate(m, vec3(2.5, 3.3, 4.4));
		m = mat4::rotate(m, 3.f, vec3(0.2, 0.6, 0.8));
		m = mat4::scale(m, vec3(0.2, 0.6, 0.8));
	}

	return 0;
}

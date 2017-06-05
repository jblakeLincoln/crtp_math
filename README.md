# CRTP math

A small header only library experimenting with template expressiveness for
vector and matrix math types. With rudimentary testing, debug performance is
notably worse than handwritten implementations, which makes this **not**
suitable for many cases such as games programming. However, optimised builds
compile down to match handwritten implementations.

Full write-up on the implementation:
<https://jordanblake.co.uk/articles/crtp_math.html>

Wandbox playground: <https://wandbox.org/permlink/S3DqOoSiSAVzpL2Y>

Declared types internally using floats:
 - vec2
 - vec3
 - vec4
 - mat2
 - mat2x3
 - mat2x4
 - mat3x2
 - mat3
 - mat3x4
 - mat4x2
 - mat4x3
 - mat4

All instantiated from the same vector and matrix template types, with declared
types being type definitions using floats internally. For example, `mat4` is a
typedef of `t_mat4x4<float>`.

## Usage:

``` cpp
vec2 v1;
vec2 v2(2, 4);

v1[0] = 1;
v1.y = 3;
v1 += v2;

printf("{ %f, %f }\n", vec2::normalise(v1));
printf("%f\n", vec2::dot(v1, v2));

mat4 m1;
mat4 m2;

mat4[3] = vec4(1, 2, 3, 1);
m2 = mat4::scale(m1, vec3(10));
```

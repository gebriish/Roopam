//=================================================================
// A single header portable vector math library
//=================================================================

#pragma once
#include <cmath>
#include <cstring>

namespace vmath {

constexpr float PI         =  3.14159265358979323846f;  	  /* pi       */
constexpr float PI_2       =	1.57079632679489661923f;	    /* pi/2     */
constexpr float PI_4       =	0.78539816339744830962f;	    /* pi/4     */
constexpr float RAD_TO_DEG =  57.29577951308232f;           /* 180 / pi */
constexpr float DEG_TO_RAD =  0.017453292519943295f;        /* pi / 180 */

//############################################################//
//#                         vec2                             #//
//############################################################//

struct vec2 {
	vec2():
		x(0), y(0)
	{}

	vec2(float d)
	: x(d), y(d)
	{}

	vec2(float v1, float vec2)
	: x(v1), y(vec2)
	{}

	union {
		struct { float x, y; };
		float xy[2];
	};

	inline bool operator==(const vec2& other) {
		return x == other.x && y == other.y;
	}

	inline vec2 operator+(float s) const { return vec2(x + s, y + s); }
	inline vec2 operator-(float s) const { return vec2(x - s, y - s); }
	inline vec2 operator*(float s) const { return vec2(x * s, y * s); }
	inline vec2 operator/(float s) const { return vec2(x / s, y / s); }

	inline vec2 operator+(const vec2& v) const { return vec2(x + v.x, y + v.y); }
	inline vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }
	inline vec2 operator*(const vec2& v) const { return vec2(x * v.x, y * v.y); }
	inline vec2 operator/(const vec2& v) const { return vec2(x / v.x, y / v.y); }

	inline vec2& operator+=(float s) { x += s; y += s; return *this; }
	inline vec2& operator-=(float s) { x -= s; y -= s; return *this; }
	inline vec2& operator*=(float s) { x *= s; y *= s; return *this; }
	inline vec2& operator/=(float s) { x /= s; y /= s; return *this; }

	inline vec2& operator+=(const vec2& v) { x += v.x; y += v.y; return *this; }
	inline vec2& operator-=(const vec2& v) { x -= v.x; y -= v.y; return *this; }
	inline vec2& operator*=(const vec2& v) { x *= v.x; y *= v.y; return *this; }
	inline vec2& operator/=(const vec2& v) { x /= v.x; y /= v.y; return *this; }
};

//############################################################//
//#                         vec3                             #//
//############################################################//

struct vec3 {
	vec3()
	: x(0), y(0), z(0)
	{}

	vec3(float d)
	: x(d), y(d), z(d)
	{}

	vec3(float v1, float vec2, float vec3)
	: x(v1), y(vec2), z(vec3)
	{}

	union {
		struct { float x, y, z; };
		float xyz[3];
	};

	inline bool operator==(const vec3& other) { 
		return x == other.x && y == other.y && z == other.z; 
	}

	inline vec3 operator+(float s) const { return vec3(x + s, y + s, z + s); }
	inline vec3 operator-(float s) const { return vec3(x - s, y - s, z - s); }
	inline vec3 operator*(float s) const { return vec3(x * s, y * s, z * s); }
	inline vec3 operator/(float s) const { return vec3(x / s, y / s, z / s); }

	inline vec3 operator+(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); }
	inline vec3 operator-(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); }
	inline vec3 operator*(const vec3& v) const { return vec3(x * v.x, y * v.y, z * v.z); }
	inline vec3 operator/(const vec3& v) const { return vec3(x / v.x, y / v.y, z / v.z); }

	inline vec3& operator+=(float s) { x += s; y += s; z += s; return *this; }
	inline vec3& operator-=(float s) { x -= s; y -= s; z -= s; return *this; }
	inline vec3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	inline vec3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

	inline vec3& operator+=(const vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline vec3& operator-=(const vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	inline vec3& operator*=(const vec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	inline vec3& operator/=(const vec3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
};


//############################################################//
//#                         vec4                             #//
//############################################################//
struct vec4 {
	vec4()
	: x(0), y(0), z(0), w(0)
	{}

	vec4(float d)
	: x(d), y(d), z(d), w(d)
	{}

	vec4(float v1, float vec2, float vec3, float vec4)
	: x(v1), y(vec2), z(vec3), w(vec4)
	{}

	union {
		struct { float x, y, z, w; };
		float xyzw[4];
	};

	inline bool operator==(const vec4& other) { 
		return x == other.x && y == other.y && z == other.z && w == other.w; 
	}

	inline vec4 operator+(float s) const { return vec4(x + s, y + s, z + s, w + s); }
	inline vec4 operator-(float s) const { return vec4(x - s, y - s, z - s, w - s); }
	inline vec4 operator*(float s) const { return vec4(x * s, y * s, z * s, w * s); }
	inline vec4 operator/(float s) const { return vec4(x / s, y / s, z / s, w / s); }

	inline vec4 operator+(const vec4& v) const { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
	inline vec4 operator-(const vec4& v) const { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
	inline vec4 operator*(const vec4& v) const { return vec4(x * v.x, y * v.y, z * v.z, w * v.w); }
	inline vec4 operator/(const vec4& v) const { return vec4(x / v.x, y / v.y, z / v.z, w / v.w); }

	inline vec4& operator+=(float s) { x += s; y += s; z += s; w += s; return *this; }
	inline vec4& operator-=(float s) { x -= s; y -= s; z -= s; w -= s; return *this; }
	inline vec4& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
	inline vec4& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }

	inline vec4& operator+=(const vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	inline vec4& operator-=(const vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	inline vec4& operator*=(const vec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	inline vec4& operator/=(const vec4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
};

//############################################################//
//                       utility                              //
//############################################################//

inline float clamp(float min, float max, float val) {
	if(val < min)
		return min;
	else if(val > max)
		return max;
	else 
		return val;
}

inline vec2 clamp(const vec2& min, const vec2& max, const vec2& vec) {
	vec2 result;
	result.x = clamp(min.x, max.x, vec.x);
	result.y = clamp(min.y, max.y, vec.y);
	return result;
}

inline vec3 clamp(const vec3& min, const vec3& max, const vec3& vec) {
	vec3 result;
	result.x = clamp(min.x, max.x, vec.x);
	result.y = clamp(min.y, max.y, vec.y);
	result.z = clamp(min.z, max.z, vec.z);
	return result;
}

inline vec4 clamp(const vec4& min, const vec4& max, const vec4& vec) {
	vec4 result;
	result.x = clamp(min.x, max.x, vec.x);
	result.y = clamp(min.y, max.y, vec.y);
	result.z = clamp(min.z, max.z, vec.z);
	result.w = clamp(min.w, max.w, vec.w);
	return result;
}

inline float MIN(float a, float b) {
	return (a < b) ? a : b;
}

inline vec2 MIN(const vec2& a, const vec2& b) {
	return vec2(MIN(a.x, b.x), MIN(a.y, b.y));
}

inline vec3 MIN(const vec3& a, const vec3& b) {
	return vec3(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z));
}

inline vec4 MIN(const vec4& a, const vec4& b) {
	return vec4(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z), MIN(a.w, b.w));
}

inline float MAX(float a, float b) {
	return (a > b) ? a : b;
}

inline vec2 MAX(const vec2& a, const vec2& b) {
	return vec2(MAX(a.x, b.x), MAX(a.y, b.y));
}

inline vec3 MAX(const vec3& a, const vec3& b) {
	return vec3(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z));
}

inline vec4 MAX(const vec4& a, const vec4& b) {
	return vec4(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z), MAX(a.w, b.w));
}

inline float lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

inline vec2 lerp(const vec2& a, const vec2& b, float t) {
	return a + (b - a) * t;
}

inline vec3 lerp(const vec3& a, const vec3& b, float t) {
	return a + (b - a) * t;
}

inline vec4 lerp(const vec4& a, const vec4& b, float t) {
	return a + (b - a) * t;
}

inline vec2 vec2_rotate(const vec2& v, float radians) {
	const float sinValue = sin(radians);
	const float cosValue = cos(radians);

	return vec2(v.x * cosValue - v.y * sinValue, v.x * sinValue + v.y * cosValue);
}

inline float dot(const vec2& a, const vec2& b) {
	return a.x * b.x + a.y * b.y;
}

inline float dot(const vec3& a, const vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float dot(const vec4& a, const vec4& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline float length(const vec2& v) {
	return sqrt(dot(v, v));
}

inline float length(const vec3& v) {
	return sqrt(dot(v, v));
}

inline float length(const vec4& v) {
	return sqrt(dot(v, v));
}

inline vec2 normalize(const vec2& v) {
	const float l = length(v);
	if(l == 0.0f) {
		return vec2(0.0f);
	}

	return v / l;
}

inline vec3 normalize(const vec3& v) {
	const float l = length(v);
	if(l == 0.0f) {
		return vec3(0.0f);
	}

	return v / l;
}

inline vec4 normalize(const vec4& v) {
	const float l = length(v);
	if(l == 0.0f) {
		return vec4(0.0f);
	}

	return v / l;
}

inline float cross(const vec2& a, const vec2& b) {
	return a.x * b.y - a.y * b.x;
}

inline vec3 cross(const vec3& a, const vec3& b) {
	return vec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

inline vec2 reflect(const vec2& ray, const vec2& normal) {
	const float component = dot(ray, normal);
	return ray - normal * component * 2.0f;
}

inline vec3 reflect(const vec3& ray, const vec3& normal) {
	const float component = dot(ray, normal);
	return ray - normal * component * 2.0f;
}

inline vec4 reflect(const vec4& ray, const vec4& normal) {
	const float component = dot(ray, normal);
	return ray - normal * component * 2.0f;
}

inline vec2 floored(const vec2& vec) {
	return vec2 (floor(vec.x), floor(vec.y));
}

inline vec3 floored(const vec3& vec) {
	return vec3 (floor(vec.x), floor(vec.y), floor(vec.z));
}

inline vec4 floored(const vec4& vec) {
	return vec4 (floor(vec.x), floor(vec.y), floor(vec.z), floor(vec.w));
}

//############################################################//
//#                         mat4                             #//
//############################################################//
struct mat4 {
	float elements[16];

	mat4() { memset(elements, 0, sizeof(elements)); for (int i = 0; i < 4; i++) elements[i + i * 4] = 1.0f; }

	float& operator()(int row, int col) { return elements[col * 4 + row]; }
	const float& operator()(int row, int col) const { return elements[col * 4 + row]; }

	mat4 operator*(const mat4& other) const {
		mat4 result;
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				result(row, col) = 0.0f;
				for (int k = 0; k < 4; k++) {
					result(row, col) += (*this)(row, k) * other(k, col);
				}
			}
		}
		return result;
	}

	static mat4 translation(const vec3& t) {
		mat4 result;
		result(0, 3) = t.x;
		result(1, 3) = t.y;
		result(2, 3) = t.z;
		return result;
	}

	static mat4 scale(const vec3& s) {
		mat4 result;
		result(0, 0) = s.x;
		result(1, 1) = s.y;
		result(2, 2) = s.z;
		return result;
	}

	static mat4 rotateX(float angle) {
		mat4 result;
		float c = std::cos(angle);
		float s = std::sin(angle);
		result(1, 1) = c; result(1, 2) = -s;
		result(2, 1) = s; result(2, 2) = c;
		return result;
	}

	static mat4 rotateY(float angle) {
		mat4 result;
		float c = std::cos(angle);
		float s = std::sin(angle);
		result(0, 0) = c; result(0, 2) = s;
		result(2, 0) = -s; result(2, 2) = c;
		return result;
	}

	static mat4 rotateZ(float angle) {
		mat4 result;
		float c = std::cos(angle);
		float s = std::sin(angle);
		result(0, 0) = c; result(0, 1) = -s;
		result(1, 0) = s; result(1, 1) = c;
		return result;
	}

	static mat4 perspective(float fov, float aspect, float near, float far) {
		mat4 result;
		float tanHalfFOV = std::tan(fov / 2.0f);
		result(0, 0) = 1.0f / (aspect * tanHalfFOV);
		result(1, 1) = 1.0f / tanHalfFOV;
		result(2, 2) = -(far + near) / (far - near);
		result(2, 3) = -(2.0f * far * near) / (far - near);
		result(3, 2) = -1.0f;
		result(3, 3) = 0.0f;
		return result;
	}

	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far) {
		mat4 result;
		result(0, 0) = 2.0f / (right - left);
		result(1, 1) = 2.0f / (top - bottom);
		result(2, 2) = -2.0f / (far - near);
		result(0, 3) = -(right + left) / (right - left);
		result(1, 3) = -(top + bottom) / (top - bottom);
		result(2, 3) = -(far + near) / (far - near);
		return result;
	}

	static mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
		vec3 f = normalize(center - eye);
		vec3 r = normalize(cross(f, up));
		vec3 u = cross(r, f);

		mat4 result;
		result(0, 0) = r.x; result(0, 1) = r.y; result(0, 2) = r.z;
		result(1, 0) = u.x; result(1, 1) = u.y; result(1, 2) = u.z;
		result(2, 0) = -f.x; result(2, 1) = -f.y; result(2, 2) = -f.z;
		result(0, 3) = -dot(r, eye);
		result(1, 3) = -dot(u, eye);
		result(2, 3) = dot(f, eye);
		return result;
	}
};

inline vec3 operator*(const mat4& matrix, const vec3& vector) {
	float x = matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z + matrix(0, 3);
	float y = matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z + matrix(1, 3);
	float z = matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z + matrix(2, 3);
	float w = matrix(3, 0) * vector.x + matrix(3, 1) * vector.y + matrix(3, 2) * vector.z + matrix(3, 3);

	if (w != 0.0f && w != 1.0f) {
		return vec3(x / w, y / w, z / w);
	}

	return vec3(x, y, z);
}

//############################################################//
//#                         quaternion                       #//
//############################################################//
struct quat {
	float x, y, z, w;

	quat() : x(0), y(0), z(0), w(1) {}
	quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	quat operator*(const quat& other) const {
		return {
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w,
			w * other.w - x * other.x - y * other.y - z * other.z
		};
	}
	quat normalize() const { float len = std::sqrt(x * x + y * y + z * z + w * w);
		return len > 0 ? quat(x / len, y / len, z / len, w / len) : quat();
	}

	mat4 toMat4() const {
		mat4 result;
		float xx = x * x, yy = y * y, zz = z * z;
		float xy = x * y, xz = x * z, yz = y * z;
		float wx = w * x, wy = w * y, wz = w * z;

		result(0, 0) = 1.0f - 2.0f * (yy + zz);
		result(0, 1) = 2.0f * (xy - wz);
		result(0, 2) = 2.0f * (xz + wy);

		result(1, 0) = 2.0f * (xy + wz);
		result(1, 1) = 1.0f - 2.0f * (xx + zz);
		result(1, 2) = 2.0f * (yz - wx);

		result(2, 0) = 2.0f * (xz - wy);
		result(2, 1) = 2.0f * (yz + wx);
		result(2, 2) = 1.0f - 2.0f * (xx + yy);

		return result;
	}

	static quat fromAxisAngle(const vec3& axis, float angle) {
		float halfAngle = angle * 0.5f;
		float s = std::sin(halfAngle);
		return quat(axis.x * s, axis.y * s, axis.z * s, std::cos(halfAngle));
	}
};

inline vec3 operator*(const quat& q, const vec3& v) {
	vec3 qVec(q.x, q.y, q.z);
	vec3 uv = cross(qVec, v);
	vec3 uuv = cross(qVec, uv);
	uv *= (2.0f * q.w);
	uuv *= 2.0f;
	return v + uv + uuv;
}

}

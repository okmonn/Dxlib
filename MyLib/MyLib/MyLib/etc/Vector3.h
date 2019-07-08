#pragma once
#include "Vector2.h"

template <typename T>
class Vector3
{
public:
	// X要素
	T x;
	// Y要素
	T y;
	// Z要素
	T z;


	// コンストラクタ
	Vector3() {
		(*this) = T(0);
	}
	Vector3(const T& i) {
		(*this) = i;
	}
	Vector3(const Vector2<T>& vec) {
		(*this) = vec;
	}
	Vector3(const Vector2<T>& vec, const T& i) {
		x = vec.x;
		y = vec.y;
		z = i;
	}
	Vector3(const T& i, const Vector2<T>& vec) {
		x = i;
		y = vec.y;
		z = vec.z;
	}
	Vector3(const T& x, const T& y, const T& z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	// コピーコンストラクタ
	Vector3(const Vector3& vec) {
		(*this) = vec;
	}
	// デストラクタ
	~Vector3() {}

	void operator=(const T& i) {
		x = y = z = i;
	}
	void operator=(const Vector2<T>& vec) {
		x = vec.x;
		y = vec.y;
		z = T(0);
	}
	void operator=(const Vector3& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	void operator+=(const T& i) {
		x += i;
		y += i;
		z += i;
	}
	void operator-=(const T& i) {
		x -= i;
		y -= i;
		z -= i;
	}
	void operator*=(const T& i) {
		x *= i;
		y *= i;
		z *= i;
	}
	void operator/=(const T& i) {
		x /= i;
		y /= i;
		z /= i;
	}

	void operator+=(const Vector3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	void operator-=(const Vector3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}
	void operator*=(const Vector3& vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
	}
	void operator/=(const Vector3& vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
	}

	Vector3 operator-(void) {
		return Vector3(-x, -y, -z);
	}

	Vector3 operator+(const Vector3& vec) {
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}
	Vector3 operator-(const Vector3& vec) {
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}
	Vector3 operator*(const Vector3& vec) {
		return Vector3(x * vec.x, y * vec.y, z * vec.z);
	}
	Vector3 operator/(const Vector3& vec) {
		return Vector3(x / vec.x, y / vec.y, z / vec.z);
	}

	Vector3 operator+(const Vector2<T>& vec) {
		return Vector3(x + vec.x, y + vec.y, z);
	}

	Vector3 operator+(const T& i) {
		return Vector3(x + i, y + i, z + i);
	}
	Vector3 operator-(const T& i) {
		return Vector3(x - i, y - i, z - i);
	}
	Vector3 operator*(const T& i) {
		return Vector3(x * i, y * i,z * i);
	}
	Vector3 operator/(const T& i) {
		return Vector3(x / i, y / i, z / i);
	}
};

template <typename T>
Vector3<T> operator+(const T& i, const Vector3<T>& vec) {
	return Vector3<T>(i + vec.x, i + vec.y, i + vec.z);
}
template <typename T>
Vector3<T> operator-(const T& i, const Vector3<T>& vec) {
	return Vector3<T>(i - vec.x, i - vec.y, i - vec.z);
}
template <typename T>
Vector3<T> operator*(const T& i, const Vector3<T>& vec) {
	return Vector3<T>(i * vec.x, i * vec.y, i * vec.z);
}
template <typename T>
Vector3<T> operator/(const T& i, const Vector3<T>& vec) {
	return Vector3<T>(i / vec.x, i / vec.y, i / vec.z);
}

template <typename T>
Vector3<T> operator+(const Vector3<T>& vec1, const Vector3<T>& vec2) {
	return Vector3<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}
template <typename T>
Vector3<T> operator-(const Vector3<T>& vec1, const Vector3<T>& vec2) {
	return Vector3<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}
template <typename T>
Vector3<T> operator*(const Vector3<T>& vec1, const Vector3<T>& vec2) {
	return Vector3<T>(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}
template <typename T>
Vector3<T> operator/(const Vector3<T>& vec1, const Vector3<T>& vec2) {
	return Vector3<T>(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

typedef Vector3<int> Vec3;
typedef Vector3<float> Vec3f;

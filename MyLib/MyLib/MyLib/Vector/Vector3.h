#pragma once
#include "Vector2.h"
#include <DirectXMath.h>

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
	inline constexpr Vector3() {
		x = T(0);
		y = T(0);
		z = T(0);
	}
	inline constexpr Vector3(const T& i) {
		x = i;
		y = i;
		z = i;
	}
	inline constexpr Vector3(const T& x, const T& y, const T& z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	inline constexpr Vector3(const Vector2<T>& vec, const T& i) {
		x = vec.x;
		y = vec.y;
		z = i;
	}
	// デストラクタ
	~Vector3() {
	}

	// 長さ
	inline T Length(void) const {
		return std::sqrt(x * x + y * y + z * z);
	}

	// 内積
	inline constexpr T Dot(const Vector3<T>& vec) const {
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	// 距離
	inline T Distance(const Vector3<T>& vec) const {
		return std::sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
	}

	// 正規化
	inline constexpr Vector3<T> Normalized(const Vector3<T>& vec) const {
		return Vector3(x / Length(), y / Length(), z / Length());
	}

	// 演算子オーバーロード

	inline constexpr bool operator==(const T& i) const {
		return (x == i && y == i && z == i);
	}
	inline constexpr bool operator!=(const T& i) const {
		return !(x == i && y == i && z == i);
	}
	inline constexpr bool operator==(const Vector3<T>& vec) const {
		return (x == vec.x && y == vec.y && z == vec.z);
	}
	inline constexpr bool operator!=(const Vector3<T>& vec) const {
		return !(x == vec.x && y == vec.y && z == vec.z);
	}

	inline constexpr bool operator<(const T& i) const {
		return (x < i && y < i && z < i);
	}
	inline constexpr bool operator>(const T& i) const {
		return (x > i && y > i && z > i);
	}
	inline constexpr bool operator<(const Vector3<T>& vec) const {
		return (x < vec.x && y < vec.y && z < vec.z);
	}
	inline constexpr bool operator>(const Vector3<T>& vec) const {
		return (x > vec.x && y > vec.y && z > vec.z);
	}

	inline constexpr bool operator<=(const T& i) const {
		return (x <= i && y <= i && z <= i);
	}
	inline constexpr bool operator>=(const T& i) const {
		return (x >= i && y >= i && z >= i);
	}
	inline constexpr bool operator<=(const Vector3<T>& vec) const {
		return (x <= vec.x && y <= vec.y && z <= vec.z);
	}
	inline constexpr bool operator>=(const Vector3<T>& vec) const {
		return (x >= vec.x && y >= vec.y && z >= vec.z);
	}

	inline constexpr void operator=(const T& i) {
		x = i;
		y = i;
		z = i;
	}
	inline constexpr void operator+=(const T& i) {
		x += i;
		y += i;
		z += i;
	}
	inline constexpr void operator-=(const T& i) {
		x -= i;
		y -= i;
		z -= i;
	}
	inline constexpr void operator*=(const T& i) {
		x *= i;
		y *= i;
		z *= i;
	}
	inline constexpr void operator/=(const T& i) {
		x /= i;
		y /= i;
		z /= i;
	}
	inline constexpr void operator=(const Vector3<T>& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
	inline constexpr void operator+=(const Vector3<T>& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
	inline constexpr void operator-=(const Vector3<T>& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}
	inline constexpr void operator*=(const Vector3<T>& vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
	}
	inline constexpr void operator/=(const Vector3<T>& vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
	}

	inline constexpr Vector3<T> operator+(void) const {
		return *this;
	}
	inline constexpr Vector3<T> operator-(void) const {
		return Vector3<T>(-x, -y, -z);
	}

	inline constexpr Vector3<T> operator+(const T& i) const {
		return Vector3<T>(x + i, y + i, z + i);
	}
	inline constexpr Vector3<T> operator-(const T& i) const {
		return Vector3<T>(x - i, y - i, z - i);
	}
	inline constexpr Vector3<T> operator*(const T& i) const {
		return Vector3<T>(x * i, y * i, z * i);
	}
	inline constexpr Vector3<T> operator/(const T& i) const {
		return Vector3<T>(x / i, y / i, z / i);
	}
	inline constexpr Vector3<T> operator+(const Vector3<T>& vec) const {
		return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);
	}
	inline constexpr Vector3<T> operator-(const Vector3<T>& vec) const {
		return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);
	}
	inline constexpr Vector3<T> operator*(const Vector3<T>& vec) const {
		return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);
	}
	inline constexpr Vector3<T> operator/(const Vector3<T>& vec) const {
		return Vector3<T>(x / vec.x, y / vec.y, z / vec.z);
	}

	inline constexpr void operator=(const DirectX::XMFLOAT3& vec) {
		x = T(vec.x);
		y = T(vec.y);
		z = T(vec.z);
	}
	inline constexpr void operator+=(const DirectX::XMFLOAT3& vec) {
		x += T(vec.x);
		y += T(vec.y);
		z += T(vec.z);
	}
	inline constexpr void operator-=(const DirectX::XMFLOAT3& vec) {
		x -= T(vec.x);
		y -= T(vec.y);
		z -= T(vec.z);
	}
	inline constexpr void operator*=(const DirectX::XMFLOAT3& vec) {
		x *= T(vec.x);
		y *= T(vec.y);
		z *= T(vec.z);
	}
	inline constexpr void operator/=(const DirectX::XMFLOAT3& vec) {
		x /= T(vec.x);
		y /= T(vec.y);
		z /= T(vec.z);
	}
	inline constexpr Vector3<T> operator+(const DirectX::XMFLOAT3& vec) const {
		return Vector3<T>(x + T(vec.x), y + T(vec.y), z + T(vec.z));
	}
	inline constexpr Vector3<T> operator-(const DirectX::XMFLOAT3& vec) const {
		return Vector3<T>(x - T(vec.x), y - T(vec.y), z - T(vec.z));
	}
	inline constexpr Vector3<T> operator*(const DirectX::XMFLOAT3& vec) const {
		return Vector3<T>(x * T(vec.x), y * T(vec.y), z * T(vec.z));
	}
	inline constexpr Vector3<T> operator/(const DirectX::XMFLOAT3& vec) const {
		return Vector3<T>(x / T(vec.x), y / T(vec.y), z / T(vec.z));
	}
};

template<typename T>
inline constexpr Vector3<T> operator+(const T & i, const Vector3<T>& vec) {
	return Vector3<T>(i + vec.x, i + vec.y, i + vec.z);
}
template<typename T>
inline constexpr Vector3<T> operator-(const T & i, const Vector3<T>& vec) {
	return Vector3<T>(i - vec.x, i - vec.y, i - vec.z);
}
template<typename T>
inline constexpr Vector3<T> operator*(const T & i, const Vector3<T>& vec) {
	return Vector3<T>(i * vec.x, i * vec.y, i * vec.z);
}
template<typename T>
inline constexpr Vector3<T> operator/(const T & i, const Vector3<T>& vec) {
	return Vector3<T>(i / vec.x, i / vec.y, i / vec.z);
}

typedef Vector3<int> Vec3;
typedef Vector3<float> Vec3f;

inline constexpr DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& vec1, const Vec3f& vec2) {
	return DirectX::XMFLOAT3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}
inline constexpr DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3& vec1, const Vec3f& vec2) {
	return DirectX::XMFLOAT3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}
inline constexpr DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& vec1, const Vec3f& vec2) {
	return DirectX::XMFLOAT3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}
inline constexpr DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3& vec1, const Vec3f& vec2) {
	return DirectX::XMFLOAT3(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

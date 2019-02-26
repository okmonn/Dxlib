#pragma once
#include "Vector2.h"

template <typename T>
class Vector3
{
public:
	// X�v�f
	T x;

	// Y�v�f
	T y;

	// Z�v�f
	T z;


	// �R���X�g���N�^
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
	inline constexpr Vector3(const Vector2<T>& vec) {
		x = vec.x;
		y = vec.y;
		z = T(0);
	}
	inline constexpr Vector3(const Vector2<T>& vec, const T& i) {
		x = vec.x;
		y = vec.y;
		z = i;
	}
	// �f�X�g���N�^
	~Vector3() {
	}

	// ����
	inline T Length(void) const {
		return std::sqrt(x * x + y * y + z * z);
	}

	// ����
	inline constexpr T Dot(const Vector3<T>& vec) const {
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	// ����
	inline T Distance(const Vector3<T>& vec) const {
		return std::sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
	}

	// ���K��
	inline constexpr Vector3<T> Normalized(const Vector3<T>& vec) const {
		return Vector3(x / Length(), y / Length(), z / Length());
	}

	// ���Z�q�I�[�o�[���[�h

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

inline DirectX::XMFLOAT2 Convert2(const Vec3f& vec) {
	return DirectX::XMFLOAT2(vec.x, vec.y);
}
inline DirectX::XMFLOAT3 Convert3(const Vec3f& vec) {
	return DirectX::XMFLOAT3(vec.x, vec.y, vec.z);
}

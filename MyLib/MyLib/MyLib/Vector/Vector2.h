#pragma once
#include <complex>

template <typename T>
class Vector2
{
public:
	// X�v�f
	T x;
	// Y�v�f
	T y;


	// �R���X�g���N�^
	inline constexpr Vector2() {
		x = T(0);
		y = T(0);
	}
	inline constexpr Vector2(const T& x, const T& y) {
		this->x = x;
		this->y = y;
	}
	inline constexpr Vector2(const T& i) {
		x = i;
		y = i;
	}
	// �f�X�g���N�^
	~Vector2() {
	}

	// ����
	inline constexpr T Length(void) const {
		return (x * x + y * y);
	}

	// ����
	inline constexpr T Dot(const Vector2<T>& vec) const {
		return (x * vec.x + y * vec.y);
	}

	// ����
	inline T Distance(const Vector2<T>& vec) const {
		return std::hypot(vec.x - x, vec.y - y);
	}

	// ���K��
	inline constexpr Vector2<T> Normalized(void) const {
		return Vector2<T>(x / Length(), y / Length());
	}

	// ���Z�q�I�[�o�[���[�h

	inline constexpr bool operator==(const T& i) const {
		return (x == i && y == i);
	}
	inline constexpr bool operator!=(const T& i) const {
		return !(x == i && y == i);
	}
	inline constexpr bool operator==(const Vector2<T>& vec) const {
		return (x == vec.x && y == vec.y);
	}
	inline constexpr bool operator!=(const Vector2<T>& vec) const {
		return !(x == vec.x && y == vec.y);
	}

	inline constexpr bool operator<(const T& i) const {
		return (x < i && y < i);
	}
	inline constexpr bool operator>(const T& i) const {
		return (x > i && y > i);
	}
	inline constexpr bool operator<(const Vector2<T>& vec) const {
		return (x < vec.x && y < vec.y);
	}
	inline constexpr bool operator>(const Vector2<T>& vec) const {
		return (x > vec.x && y > vec.y);
	}

	inline constexpr bool operator<=(const T& i) const {
		return (x <= i && y <= i);
	}
	inline constexpr bool operator>=(const T& i) const {
		return (x >= i && y >= i);
	}
	inline constexpr bool operator<=(const Vector2<T>& vec) const {
		return (x <= vec.x && y <= vec.y);
	}
	inline constexpr bool operator>=(const Vector2<T>& vec) const {
		return (x >= vec.x && y >= vec.y);
	}

	inline constexpr void operator+(const T& i) {
		x += i;
		y += i;
	}
	inline constexpr void operator-(const T& i) {
		x -= i;
		y -= i;
	}
	inline constexpr void operator*(const T& i) {
		x *= i;
		y *= i;
	}
	inline constexpr void operator/(const T& i) {
		x /= i;
		y /= i;
	}
	inline constexpr void operator+(const Vector2<T>& vec) {
		x += vec.x;
		y += vec.y;
	}
	inline constexpr void operator-(const Vector2<T>& vec) {
		x -= vec.x;
		y -= vec.y;
	}
	inline constexpr void operator*(const Vector2<T>& vec) {
		x *= vec.x;
		y *= vec.y;
	}
	inline constexpr void operator/(const Vector2<T>& vec) {
		x /= vec.x;
		y /= vec.y;
	}
	
	inline constexpr Vector2<T> operator+(void) const {
		return *this;
	}
	inline constexpr Vector2<T> operator-(void) const {
		return Vector2<T>(-x, -y);
	}

	inline constexpr Vector2<T> operator+(const T& i) const {
		return Vector2<T>(x + i, y + i);
	}
	inline constexpr Vector2<T> operator-(const T& i) const {
		return Vector2<T>(x - i, y - i);
	}
	inline constexpr Vector2<T> operator*(const T& i) const {
		return Vector2<T>(x * i, y * i);
	}
	inline constexpr Vector2<T> operator/(const T& i) const {
		return Vector2<T>(x / i, y / i);
	}
	inline constexpr Vector2<T> operator+(const Vector2<T>& vec) const {
		return Vector2<T>(x + vec.x, y + vec.y);
	}
	inline constexpr Vector2<T> operator-(const Vector2<T>& vec) const {
		return Vector2<T>(x - vec.x, y - vec.y);
	}
	inline constexpr Vector2<T> operator*(const Vector2<T>& vec) const {
		return Vector2<T>(x * vec.x, y * vec.y);
	}
	inline constexpr Vector2<T> operator/(const Vector2<T>& vec) const {
		return Vector2<T>(x / vec.x, y / vec.y);
	}

private:
};

template<typename T>
inline const Vector2<T> operator+(const T & i, const Vector2<T>& vec) {
	return Vector2<T>(i + vec.x, i + vec.y);
}
template<typename T>
inline const Vector2<T> operator-(const T & i, const Vector2<T>& vec) {
	return Vector2<T>(i - vec.x, i - vec.y);
}
template<typename T>
inline const Vector2<T> operator*(const T & i, const Vector2<T>& vec) {
	return Vector2<T>(i * vec.x, i * vec.y);
}
template<typename T>
inline const Vector2<T> operator/(const T & i, const Vector2<T>& vec) {
	return Vector2<T>(i / vec.x, i / vec.y);
}

template <typename T>
inline const T Dot(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}
template<typename T>
inline T Distance(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return T(std::hypot(vec2.x - vec1.x, vec2.y - vec2.y));
}

typedef Vector2<int> Vec2;
typedef Vector2<float> Vec2f;

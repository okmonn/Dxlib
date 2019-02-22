#include "Vector2.h"
#include <cmath>

// コンストラクタ
template<typename T>
inline constexpr Vector2<T>::Vector2()
{
	x = T(0);
	y = T(0);
}

// コンストラクタ
template<typename T>
inline constexpr Vector2<T>::Vector2(const T & x, const T & y)
{
	this->x = x;
	this->y = y;
}

// コンストラクタ
template<typename T>
inline constexpr Vector2<T>::Vector2(const T & i)
{
	Vector2(i, i);
}

// デストラクタ
template<typename T>
Vector2<T>::~Vector2()
{
}

// 長さ
template<typename T>
inline T Vector2<T>::Length(void) const
{
	return T(std::sqrt(x * x + y * y));
}

// 内積
template<typename T>
inline constexpr T Vector2<T>::Dot(const Vector2<T> & vec) const
{
	return T(x * vec.x + y * vec.y);
}

// 距離
template<typename T>
inline T Vector2<T>::Distance(const Vector2<T>& vec) const
{
	return T(std::hypot(vec.x - x, vec.y - y));
}

// 正規化
template<typename T>
inline constexpr Vector2<T> Vector2<T>::Normalized(void) const
{
	return Vector2<T>(x / Length(), y / Length());
}

template<typename T>
inline constexpr bool Vector2<T>::operator==(const T & i) const
{
	return (x == i && y == i);
}

template<typename T>
inline constexpr bool Vector2<T>::operator!=(const T & i) const
{
	return !(x == i && y == i);
}

template<typename T>
inline constexpr bool Vector2<T>::operator==(const Vector2<T>& vec) const
{
	return (x == vec.x && y == vec.y);
}

template<typename T>
inline constexpr bool Vector2<T>::operator!=(const Vector2<T>& vec) const
{
	return !(x == vec.x && y == vec.y);
}

template<typename T>
inline constexpr bool Vector2<T>::operator<(const T & i) const
{
	return (x < i && y < i);
}

template<typename T>
inline constexpr bool Vector2<T>::operator>(const T & i) const
{
	return (x > i && y > i);
}

template<typename T>
inline constexpr bool Vector2<T>::operator<(const Vector2<T>& vec) const
{
	return (x < vec.x && y < vec.y);
}

template<typename T>
inline constexpr bool Vector2<T>::operator>(const Vector2<T>& vec) const
{
	return (x > vec.x && y > vec.y);
}

template<typename T>
inline constexpr bool Vector2<T>::operator<=(const T & i) const
{
	return (x <= i && y <= i);
}

template<typename T>
inline constexpr bool Vector2<T>::operator>=(const T & i) const
{
	return (x >= i && y >= i);
}

template<typename T>
inline constexpr bool Vector2<T>::operator<=(const Vector2<T>& vec) const
{
	return (x <= vec.x && y <= vec.y);
}

template<typename T>
inline constexpr bool Vector2<T>::operator>=(const Vector2<T>& vec) const
{
	return (x >= vec.x && y >= vec.y);
}

template<typename T>
inline constexpr void Vector2<T>::operator+(const T & i)
{
	x += i;
	y += i;
}

template<typename T>
inline constexpr void Vector2<T>::operator-(const T & i)
{
	x -= i;
	y -= i;
}

template<typename T>
inline constexpr void Vector2<T>::operator*(const T & i)
{
	x *= i;
	y *= i;
}

template<typename T>
inline constexpr void Vector2<T>::operator/(const T & i)
{
	if (i == T(0))
	{
		return;
	}

	x /= i;
	y /= i;
}

template<typename T>
inline constexpr void Vector2<T>::operator+(const Vector2<T>& vec)
{
	x += vec.x;
	y += vec.y;
}

template<typename T>
inline constexpr void Vector2<T>::operator-(const Vector2<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
}

template<typename T>
inline constexpr void Vector2<T>::operator*(const Vector2<T>& vec)
{
	x *= vec.x;
	y *= vec.y;
}

template<typename T>
inline constexpr void Vector2<T>::operator/(const Vector2<T>& vec)
{
	if (vec == T(0))
	{
		return;
	}

	x /= vec.x;
	y /= vec.y;
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator+(void) const
{
	return *this;
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator-(void) const
{
	return Vector2<T>(-x, -y);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator+(const T & i) const
{
	return Vector2<T>(x + i, y + i);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator-(const T & i) const
{
	return Vector2<T>(x - i, y - i);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator*(const T & i) const
{
	return Vector2<T>(x * i, y * i);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator/(const T & i) const
{
	if (i == T(0))
	{
		return Vector2<T>(T(0));
	}

	return Vector2<T>(x / i, y / i);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec) const
{
	return Vector2<T>(x + vec.x, y + vec.y);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator-(const Vector2<T>& vec) const
{
	return Vector2<T>(x - vec.x, y - vec.y);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator*(const Vector2<T>& vec) const
{
	return Vector2<T>(x * vec.x, y * vec.y);
}

template<typename T>
inline constexpr Vector2<T> Vector2<T>::operator/(const Vector2<T>& vec) const
{
	if (vec == T(0))
	{
		return Vector2<T>(T(0));
	}

	return Vector2<T>(x / vec.x, y / vec.y);
}

template<typename T>
inline constexpr Vector2<T> operator+(const T & i, const Vector2<T>& vec)
{
	return Vector2<T>(i + vec.x, i + vec.y);
}

template<typename T>
inline constexpr Vector2<T> operator-(const T & i, const Vector2<T>& vec)
{
	return Vector2<T>(i - vec.x, i - vec.y);
}

template<typename T>
inline constexpr Vector2<T> operator*(const T & i, const Vector2<T>& vec)
{
	return Vector2<T>(i * vec.x, i * vec.y);
}

template<typename T>
inline constexpr Vector2<T> operator/(const T & i, const Vector2<T>& vec)
{
	if (vec == T(0))
	{
		return Vector2<T>(T(0));
	}

	return Vector2<T>(i / vec.x, i / vec.y);
}

template <typename T>
inline constexpr T Dot(const Vector2<T>& vec1, const Vector2<T>& vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

template<typename T>
inline T Distance(const Vector2<T>& vec1, const Vector2<T>& vec2)
{
	return T();
}

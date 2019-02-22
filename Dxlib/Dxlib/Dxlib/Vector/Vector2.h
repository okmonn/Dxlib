#pragma once

template <typename T>
class Vector2
{
public:
	// X要素
	T x;
	// Y要素
	T y;


	// コンストラクタ
	inline constexpr Vector2();
	inline constexpr Vector2(const T& x, const T& y);
	inline constexpr Vector2(const T& i);
	// デストラクタ
	~Vector2();

	// 長さ
	inline T Length(void) const;

	// 内積
	inline constexpr T Dot(const Vector2<T>& vec) const;

	// 距離
	inline T Distance(const Vector2<T>& vec) const;

	// 正規化
	inline constexpr Vector2<T> Normalized(void) const;

	// 演算子オーバーロード

	inline constexpr bool operator==(const T& i) const;
	inline constexpr bool operator!=(const T& i) const;
	inline constexpr bool operator==(const Vector2<T>& vec) const;
	inline constexpr bool operator!=(const Vector2<T>& vec) const;

	inline constexpr bool operator<(const T& i) const;
	inline constexpr bool operator>(const T& i) const;
	inline constexpr bool operator<(const Vector2<T>& vec) const;
	inline constexpr bool operator>(const Vector2<T>& vec) const;

	inline constexpr bool operator<=(const T& i) const;
	inline constexpr bool operator>=(const T& i) const;
	inline constexpr bool operator<=(const Vector2<T>& vec) const;
	inline constexpr bool operator>=(const Vector2<T>& vec) const;

	inline constexpr void operator+(const T& i);
	inline constexpr void operator-(const T& i);
	inline constexpr void operator*(const T& i);
	inline constexpr void operator/(const T& i);
	inline constexpr void operator+(const Vector2<T>& vec);
	inline constexpr void operator-(const Vector2<T>& vec);
	inline constexpr void operator*(const Vector2<T>& vec);
	inline constexpr void operator/(const Vector2<T>& vec);
	
	inline constexpr Vector2<T> operator+(void) const;
	inline constexpr Vector2<T> operator-(void) const;

	inline constexpr Vector2<T> operator+(const T& i) const;
	inline constexpr Vector2<T> operator-(const T& i) const;
	inline constexpr Vector2<T> operator*(const T& i) const;
	inline constexpr Vector2<T> operator/(const T& i) const;
	inline constexpr Vector2<T> operator+(const Vector2<T>& vec) const;
	inline constexpr Vector2<T> operator-(const Vector2<T>& vec) const;
	inline constexpr Vector2<T> operator*(const Vector2<T>& vec) const;
	inline constexpr Vector2<T> operator/(const Vector2<T>& vec) const;

private:
};

template<typename T>
inline constexpr Vector2<T> operator+(const T & i, const Vector2<T>& vec);
template<typename T>
inline constexpr Vector2<T> operator-(const T & i, const Vector2<T>& vec);
template<typename T>
inline constexpr Vector2<T> operator*(const T & i, const Vector2<T>& vec);
template<typename T>
inline constexpr Vector2<T> operator/(const T & i, const Vector2<T>& vec);

template <typename T>
inline constexpr T Dot(const Vector2<T>& vec1, const Vector2<T>& vec2);

template <typename T>
inline T Distance(const Vector2<T>& vec1, const Vector2<T>& vec2);

typedef Vector2<int> Vec2;
typedef Vector2<float> Vec2f;

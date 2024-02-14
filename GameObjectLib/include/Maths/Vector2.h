#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace Maths 
{
	template <typename T>
	class Vector2 {

	public:
		T X;
		T Y;
		Vector2();
		Vector2(T x, T y);
		T getX() { return X; }
		T getY() { return Y; }
		void setX(T x);
		void setY(T y);
		void set(T x, T y);
		static Vector2<T> down();
		static Vector2<T> left();
		static Vector2<T> right();
		static Vector2<T> up();
		static Vector2<T> zero();
		static Vector2<T> one();
		float magnitude() const;
		Vector2<T> normalized();
		float sqrMagnitude() const;
		T operator[](const T& index);
		void normalize();
		Vector2<T> copy() const;
		static float angle(const Vector2<T>& vectA, const Vector2<T>& vectB);
		static float signedAngle(const Vector2<T>& vectA, const Vector2<T>& vectB);
		static Vector2<T> clampMagnitude(const Vector2<T>& vect, float newMagnitude);
		static float distance(const Vector2<T>& vectA, const Vector2<T>& vectB);
		static float dot(const Vector2<T>& vectA, const Vector2<T>& vectB);
		static Vector2<T> lerp(const Vector2<T>& vectA, const Vector2<T>& vectB, float t);
		static Vector2<T> moveTowards(const Vector2<T>& current, const Vector2<T>& target, float maxDistanceDelta);
		static Vector2<T> lerpUnclamped(const Vector2<T>& vectA, const Vector2<T>& vectB, float t);
		bool equals(Vector2<T> vector);
		std::string toString();
		Vector2<T> operator-(const Vector2<T>& vectB) const;
		Vector2<T> operator+(const Vector2<T>& vectB) const;
		Vector2<T> operator*(const float val) const;
		Vector2<T> operator/(const float val) const;
		Vector2 operator+=(const Vector2& rhs);
		Vector2 operator-=(const Vector2& rhs);
		Vector2 operator*=(const Vector2& rhs);
		Vector2 operator/=(const Vector2& rhs);
		bool operator==(const Vector2<T>& vectB) const;
		static Vector2<T> max(const Vector2<T>& vectA, const Vector2<T>& vectB);
		static Vector2<T> min(const Vector2<T>& vectA, const Vector2<T>& vectB);
		static Vector2<T> scale(const Vector2<T>& vectA, const Vector2<T>& vectB);
		static Vector2<T> reflect(const Vector2<T>& vectA, const Vector2<T>& vectB);
	};
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}
template class Maths::Vector2<int>;
template class Maths::Vector2<unsigned int>;
template class Maths::Vector2<float>;
template class Maths::Vector2<double>;
#include "Vector2.inl"
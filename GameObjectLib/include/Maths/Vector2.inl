#pragma once
#include "Vector2.h"
#pragma warning(push)
#pragma warning(disable : 4244)


namespace Maths
{
	template <typename T>
	Vector2<T>::Vector2() :X(0), Y(0) {}

	template <typename T>
	Vector2<T>::Vector2(T x, T y) : X(x), Y(y) {}

	template <typename T>
	void Vector2<T>::setX(T x) {
		X = x;
	}

	template <typename T>
	void Vector2<T>::setY(T y) {
		Y = y;
	}

	template <typename T>
	void Vector2<T>::set(T x, T y) {
		X = x;
		Y = y;
	}

	template <typename T>
	Vector2<T> Vector2<T>::down() {
		return Vector2(0, -1);
	}

	template <typename T>
	Vector2<T> Vector2<T>::right() {
		return Vector2(1, 0);
	}

	template <typename T>
	Vector2<T> Vector2<T>::up() {
		return Vector2(0, 1);
	}

	template <typename T>
	Vector2<T> Vector2<T>::left() {
		return Vector2(-1, 0);
	}

	template <typename T>
	Vector2<T> Vector2<T>::zero() {
		return Vector2(0, 0);
	}

	template <typename T>
	Vector2<T> Vector2<T>::one() {
		return Vector2(1, 1);
	}

	template <typename T>
	float Vector2<T>::magnitude() const {
		return sqrt(X * X + Y * Y);
	}

	template <typename T>
	Vector2<T> Vector2<T>::lerp(const Vector2<T>& vectA, const Vector2<T>& vectB, float t) {
		t = std::max(0.0f, std::min(1.0f, t));
		T lerpX = vectA.X + t * (vectB.X - vectA.X);
		T lerpY = vectA.Y + t * (vectB.Y - vectA.Y);
		return Vector2(lerpX, lerpY);
	}

	template <typename T>
	Vector2<T> Vector2<T>::lerpUnclamped(const Vector2<T>& vectA, const Vector2<T>& vectB, float t) {
		T lerpX = vectA.X + t * (vectB.X - vectA.X);
		T lerpY = vectA.Y + t * (vectB.Y - vectA.Y);
		return Vector2(lerpX, lerpY);
	}

	template <typename T>
	Vector2<T> Vector2<T>::moveTowards(const Vector2<T>& current, const Vector2<T>& target, float maxDistanceDelta) {
		T distanceX = target.X - current.X;
		T distanceY = target.Y - current.Y;
		T distance = sqrt(distanceX * distanceX + distanceY * distanceY);
		if (distance <= maxDistanceDelta) {
			return target;
		}
		else {
			float ratio = maxDistanceDelta / distance;
			T newX = current.X + distanceX * ratio;
			T newY = current.Y + distanceY * ratio;
			return Vector2(newX, newY);
		}
	}

	template <typename T>
	Vector2<T> Vector2<T>::normalized() {
		float length = magnitude();
		if (length != 0) {
			T newX = X / length;
			T newY = Y / length;
			return Vector2(newX, newY);
		}
		else {
			throw std::invalid_argument("Vector's magnitude = 0.");
		}

	}

	template <typename T>
	T Vector2<T>::operator[](const T& index) {
		if ((index < 2) && (index >= 0)) {
			return index == 0 ? X : Y;
		}
		else {
			throw std::out_of_range("Index out of range.");
		}

	}

	template <typename T>
	Vector2<T> Vector2<T>::copy() const {
		Vector2<T> copyVector(X, Y);
		return copyVector;
	}

	template <typename T>
	float Vector2<T>::angle(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		return std::acos(dot(vectA, vectB) / (vectA.magnitude() * vectB.magnitude()));
	}

	template <typename T>
	Vector2<T> Vector2<T>::clampMagnitude(const Vector2<T>& vect, float newMagnitude) {
		T mag = vect.magnitude();
		T newX = vect.X * (newMagnitude / mag);
		T newY = vect.Y * (newMagnitude / mag);
		Vector2<T> copyVectNewMag(newX, newY);
		return copyVectNewMag;
	}

	template <typename T>
	float Vector2<T>::distance(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		T newX = vectB.X - vectA.X;
		T newY = vectB.Y - vectA.Y;
		return std::sqrt((newX * newX) + (newY * newY));
	}

	template <typename T>
	bool Vector2<T>::equals(Vector2<T> vector) {

		if ((X == vector.getX()) && (Y == vector.getY())) {
			return true;
		}
		else {
			return false;
		}
	}

	template <typename T>
	float Vector2<T>::dot(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		return (vectA.X * vectB.X) + (vectA.Y * vectB.Y);
	}

	template <typename T>
	void Vector2<T>::normalize() {
		float length = magnitude();
		if (length != 0) {
			X /= length;
			Y /= length;
		}
	}

	template <typename T>
	float Vector2<T>::sqrMagnitude() const {
		T res = pow(magnitude(), 2.f);
		return res;
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2<T>& vectB) const {
		T newX = (X - vectB.X);
		T newY = (Y - vectB.Y);
		Vector2<T> newVect(newX, newY);
		return newVect;
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator+(const Vector2<T>& vectB) const {
		return Vector2(X + vectB.X, Y + vectB.Y);
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator*(const float val) const {
		T newX = (X * val);
		T newY = (Y * val);
		Vector2<T> newVect(newX, newY);
		return newVect;
	}

	template <typename T>
	Vector2<T> Vector2<T>::operator/(const float val) const {
		if (val != 0) {
			T newX = (X / val);
			T newY = (Y / val);
			Vector2<T> newVect(newX, newY);
			return newVect;
		}
		else {
			throw std::invalid_argument("Division by 0.");
		}
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator+=(const Vector2& vectB)
	{
		X += vectB.X;
		Y += vectB.Y;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-=(const Vector2& vectB)
	{
		X -= vectB.X;
		Y -= vectB.Y;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*=(const Vector2& vectB)
	{
		X *= vectB.X;
		Y *= vectB.Y;
		return *this;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/=(const Vector2& vectB)
	{
		X /= vectB.X;
		Y /= vectB.Y;
		return *this;
	}


	template <typename T>
	Vector2<T> Vector2<T>::max(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		T sousX = (vectA.X - vectB.X);
		T sousY = (vectA.Y - vectB.Y);
		T xMax, yMax;
		if (sousX <= 0) {
			xMax = vectB.X;
		}
		else {
			xMax = vectA.X;
		}
		if (sousY <= 0) {
			yMax = vectB.Y;
		}
		else {
			yMax = vectA.Y;
		}
		Vector2<T> newVectmax(xMax, yMax);
		return newVectmax;
	}

	template <typename T>
	Vector2<T> Vector2<T>::min(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		T sousX = (vectA.X - vectB.X);
		T sousY = (vectA.Y - vectB.Y);
		T xMin, yMin;
		if (sousX <= 0) {
			xMin = vectA.X;
		}
		else {
			xMin = vectB.X;
		}
		if (sousY <= 0) {
			yMin = vectA.Y;
		}
		else {
			yMin = vectB.Y;
		}
		Vector2<T> newVectmin(xMin, yMin);
		return newVectmin;
	}

	template <typename T>
	bool Vector2<T>::operator==(const Vector2<T>& vectB) const {
		return X == vectB.X && Y == vectB.Y;
	}

	template <typename T>
	std::string Vector2<T>::toString() {
		std::string ret = "(" + std::to_string(X) + "," + std::to_string(Y) + ")";
		return ret;
	}

	template <typename T>
	float Vector2<T>::signedAngle(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		T normalizedFrom = vectA.magnitude();
		T normalizedTo = vectB.magnitude();
		float prodScal = dot(vectA, vectB);
		T sub = (vectA.X * vectB.Y - vectA.Y * vectB.X);
		float sign = 1.0f;
		if (sub < 0) {
			sign = -1.0f;
		}
		float signedAngle = (sign * (std::acos(prodScal / (normalizedFrom * normalizedTo))));
		return signedAngle;
	}

	template <typename T>
	Vector2<T> Vector2<T>::scale(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		T newX = (vectA.X * vectB.X);
		T newY = (vectA.Y * vectB.Y);
		Vector2<T> newVect(newX, newY);
		return newVect;
	}

	template <typename T>
	Vector2<T> Vector2<T>::reflect(const Vector2<T>& vectA, const Vector2<T>& vectB) {
		float prodScal = dot(vectA, vectB);
		Vector2<T> Vectref = (vectA - (vectB * (2 * prodScal)));
		return Vectref;
	}
}
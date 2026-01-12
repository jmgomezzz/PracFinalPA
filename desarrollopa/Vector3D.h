#pragma once
#include <GL/glut.h>
#include <cmath>
#include <iostream>

template <class S> class Vector3Dx;

typedef Vector3Dx<float> Vector3D;
//typedef Vector3Dx<float> Vector3Df;
typedef Vector3Dx<double> Vector3Dd;
typedef Vector3Dx<int> Vector3Di;
template <class S> class Vector3Dx
{
private:
	S X;
	S Y;
	S Z;
public:
	Vector3Dx(S x = 0, S y = 0, S z = 0) :X(x), Y(y), Z(z) {};
	
	inline S GetX() const { return X; }
	inline S GetY() const { return Y; }
	inline S GetZ() const { return Z; }

	inline void SetX(S XToSet) { X = XToSet; }
	inline void SetY(S YToSet) { Y = YToSet; }
	inline void SetZ(S ZToSet) { Z = ZToSet; }

	Vector3Dx<S> Add(Vector3Dx<S> b) const;
	Vector3Dx<S> Substract(Vector3Dx<S> b) const;
	Vector3Dx<S> Product(S b) const;
	S DotProduct(Vector3Dx<S> v) const;
	S Magnitude() const;

	Vector3Dx<S> operator+(Vector3Dx<S> vector)const;
	Vector3Dx<S> operator-(Vector3Dx<S> vector)const;
	Vector3Dx<S> operator*(S value)const;
	Vector3Dx<S> operator/(S value)const;
	S operator*(const Vector3Dx<S>& vector) const;
	void Normalize();

};

//Como es una platilla la definición de sus funciones se implementa en la cabecera también

template <class S> Vector3Dx<S> Vector3Dx<S>::Add(const Vector3Dx<S> b)const {
	return Vector3Dx<S>(this->GetX() + b.GetX(), this->GetY() + b.GetY(), this->GetZ() + b.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Substract(const Vector3Dx<S> b)const {
	return Vector3Dx<S>(this->GetX() - b.GetX(), this->GetY() - b.GetY(), this->GetZ() - b.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::Product(S b)const {
	return Vector3Dx<S>(this->GetX() * b, this->GetY() * b, this->GetZ() * b);
}

template <class S> S Vector3Dx<S>::DotProduct(Vector3Dx<S> v)const {
	return (this->GetX() * v.GetX() + this->GetY() * v.GetY() + this->GetZ() * v.GetZ());
}

template <class S> S Vector3Dx<S>::Magnitude()const {
	return std::sqrt(this->GetX() * this->GetX() + this->GetY() * this->GetY() + this->GetZ() * this->GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator+(const Vector3Dx<S> vector)const {
	return Vector3Dx<S>(this->GetX() + vector.GetX(), this->GetY() + vector.GetY(), this->GetZ() + vector.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator-(const Vector3Dx<S> vector) const {
	return Vector3Dx<S>(this->GetX() - vector.GetX(), this->GetY() - vector.GetY(), this->GetZ() - vector.GetZ());
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator*(S value)const {
	return Vector3Dx<S>(this->GetX() * value, this->GetY() * value, this->GetZ() * value);
}

template <class S> Vector3Dx<S> Vector3Dx<S>::operator/(S value)const {
	return Vector3Dx<S>(this->GetX() / value, this->GetY() / value, this->GetZ() / value);
}

template <class S> S Vector3Dx<S>::operator*(const Vector3Dx<S>& vector) const {
	return S(this->GetX() * vector.GetX() + this->GetY() * vector.GetY() + this->GetZ() * vector.GetZ());
}
//Operador libre para soportar escalar * vector
template <class S> inline Vector3Dx<S> operator*(S value, const Vector3Dx<S>& v) {
	return v * value;
}
template <class S> void Vector3Dx<S>::Normalize() {
	S mag = Magnitude();
	if (mag > static_cast<S>(0.000001)) {
		X /= mag;
		Y /= mag;
		Z /= mag;
	}
}

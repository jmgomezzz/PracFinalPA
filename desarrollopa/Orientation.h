#pragma once
#include "Vector3D.h"
class Orientation
{
private:
	Vector3D rotacion;
public:
	Orientation() :rotacion(0.0f,0.0f,0.0f) {}
	Orientation(Vector3D v):rotacion(v) {}
	inline Vector3D GetRotacion() { return this->rotacion; }
	inline void SetRotacion(const Vector3D& r) { this->rotacion = r;}

};


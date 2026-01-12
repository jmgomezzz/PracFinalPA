#pragma once
#include "Vector3D.h"
#include "Color.h"
class Vertice
{
private:
	Vector3D posicion;
	Vector3D normal;
	Color color;
public:
	Vertice(Vector3D p= Vector3D(0.0, 0.0, 0.0), Vector3D n= Vector3D(1.0,1.0,1.0), Color c=Color(1.0,0.0,0.0)) {
		this->posicion = Vector3D(0.0, 0.0, 0.0);
		this->normal = Vector3D(1.0, 1.0, 1.0);
		this->color = Color(1.0,0.0,0.0);
	}

	inline Vector3D GetNormal() { return this->normal; }
	inline Color GetColor() { return this->color; }
	inline Vector3D GetPosicion() { return this->posicion; }

	void SetNormal(Vector3D normalToSet) { this->normal = normalToSet; }
	void SetColor(Color colorToSet) { this->color = colorToSet; }
	void SetPosicion(Vector3D posicionToSet) { this->posicion = posicionToSet; }
};


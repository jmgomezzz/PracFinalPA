#pragma once
#include "Solid.h"
class Camera:public Solid
{
private:
	Vector3D posicion;
public:
	Camera(const Vector3D& pos= Vector3D()) {
		this->posicion = pos;
	}
	void Render();
	Solid* Clone() override;
};


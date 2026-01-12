#pragma once
#include "Solid.h"

class Particle
{
private:
	Solid* modelo;
	long tiempoCreacion;

public:
	Particle(Solid* modelo, long tiempoCreacion) {
		this->modelo = modelo;
		this->tiempoCreacion = tiempoCreacion;
	}

	//Destructor
	~Particle() {
		if (this->modelo != nullptr) {
			delete this->modelo;
			this->modelo = nullptr;
		}
	}
	//Delegamos el renderizado y update al modelo interno
	void Render() {
		if (this->modelo != nullptr) this->modelo->Render();
	}

	void Update(const float& time, const Vector3D& gravity) {
		if (this->modelo != nullptr) this->modelo->Update(time,gravity);
	}

	long GetTiempoCreacion() { return this->tiempoCreacion; }
};
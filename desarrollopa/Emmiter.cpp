#include "Emmiter.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std::chrono;

float RandomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

Emmiter::Emmiter() {
	this->configuracion = EmmiterConfiguration();
	this->particulasGeneradas = {};
	this->initialMilliseconds = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	this->lastUpdatedTime = -999999;
	srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Emmiter::Render() {
	for (int i = 0; i < particulasGeneradas.size(); i++) {
		particulasGeneradas[i]->Render();
	}
}

Solid* Emmiter::Clone() {
	return new Emmiter(*this);
}

void Emmiter::Update(const float& time, const Vector3D& gravity) {
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long currentMillis = currentTime.count() - this->initialMilliseconds.count();

	//Actualizamos las partículas existentes
	for (int i = 0; i < particulasGeneradas.size(); i++) {
		particulasGeneradas[i]->Update(time,gravity);

		// Comprobamos si ha muerto por tiempo
		if ((currentMillis - particulasGeneradas[i]->GetTiempoCreacion()) > this->configuracion.GetTiempoVida()) {

			//Eliminamos la particula
			delete particulasGeneradas[i];

			particulasGeneradas.erase(particulasGeneradas.begin() + i);
			i--;
		}
	}

	//Emisión
	if ((currentMillis - this->lastUpdatedTime) >= this->configuracion.GetPeriodoEmision()) {

		if (this->particulasGeneradas.size() < this->configuracion.GetMaxParticulas()) {

			if (this->configuracion.GetParticula() != nullptr) {
				Solid* newSolid = this->configuracion.GetParticula()->Clone();

				//Ajustamos la logica para que parezca fuego
				Vector3D emitterPos = this->GetCoord();
				float jitter = 0.1f;

				newSolid->SetCoordinates(Vector3D(
					emitterPos.GetX() + RandomFloat(-jitter, jitter),
					emitterPos.GetY() + RandomFloat(-jitter, jitter),
					emitterPos.GetZ() + RandomFloat(-jitter, jitter)
				));

				Vector3D baseForce = this->configuracion.GetAceleracion();
				float spread = 0.035f; //Muy poco spread para fuego

				newSolid->SetSpeed(Vector3D(
					baseForce.GetX() + RandomFloat(-spread / 2.0f, spread / 2.0f),
					baseForce.GetY() + RandomFloat(0.0f, 0.05f),
					baseForce.GetZ() + RandomFloat(-spread / 2.0f, spread / 2.0f)
				));

				newSolid->SetRot(Orientation(Vector3D(
					RandomFloat(0.0f, 90.0f),
					RandomFloat(0.0f, 90.0f),
					RandomFloat(0.0f, 90.0f)
				)));

				newSolid->SetColor(Color(
					RandomFloat(0.8f, 1.0f),
					RandomFloat(0.0f, 0.6f),
					0.0f
				));

				newSolid->SetOrientationSpeed(Vector3D(
					RandomFloat(-5.0f, 5.0f),
					RandomFloat(-5.0f, 5.0f),
					RandomFloat(-5.0f, 5.0f)
				));

				//Crea la particula y la añade al vector
				Particle* newParticle = new Particle(newSolid, currentMillis);
				this->particulasGeneradas.push_back(newParticle);
			}
		}
		this->lastUpdatedTime = currentMillis;
	}
}
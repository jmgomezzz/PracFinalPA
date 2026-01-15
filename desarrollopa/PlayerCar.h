#pragma once
#include "Car.h"

// Estados del adelantamiento
// Controla toda la maniobra con un solo boton
enum class OvertakeState {
	IDLE,				// En carril derecho, velocidad normal
	CHANGING_LEFT,      // Cambiando al carril izquierdo
	OVERTAKING,			// En carril izquierdo, acelerando
	CHANGING_RIGHT		// Volviendo al carril derecho
};

// Coche del jugador
// El jugador solo tiene que pulsar ESPACIO para adelantar
class PlayerCar : public Car
{
private:
	float minSpeed;          // Velocidad base en carril derecho
	float maxSpeed;			 // Velocidad maxima posible
	float overtakeSpeed;     // Velocidad mientras adelanta
	float acceleration;      // Aceleracion al adelantar
	float laneChangeSpeed;   // Velocidad de cambio de carril

	OvertakeState overtakeState;
	float rightLaneX;        // Posicion X del carril derecho
	float leftLaneX;         // Posicion X del carril izquierdo

	bool overtakeButtonPressed;  // Si el boton esta pulsado

public:
	PlayerCar() : Car() {
		// Velocidades MUY diferenciadas para que se note
		this->minSpeed = 10.0f;      // Velocidad base
		this->maxSpeed = 50.0f;
		this->overtakeSpeed = 35.0f;     // El doble de rapido al adelantar
		this->acceleration = 100.0f;     // Aceleracion instantanea
		this->laneChangeSpeed = 12.0f;   // Cambio de carril muy rapido
		this->overtakeState = OvertakeState::IDLE;
		this->rightLaneX = 2.0f;
		this->leftLaneX = -2.0f;
		this->overtakeButtonPressed = false;
		
		// Empezamos en el carril derecho
		this->currentSpeed = minSpeed;
		this->isInLeftLane = false;
	}

	// Getters
	inline float GetMinSpeed() const { return this->minSpeed; }
	inline float GetMaxSpeed() const { return this->maxSpeed; }
	inline OvertakeState GetOvertakeState() const { return this->overtakeState; }
	inline bool IsOvertaking() const { return overtakeState != OvertakeState::IDLE; }

	// Setters
	void SetMinSpeed(float speed) { this->minSpeed = speed; }
	void SetMaxSpeed(float speed) { this->maxSpeed = speed; }

	// Control de adelantamiento
	// Llamar cuando se PRESIONA el boton
	void StartOvertake();
	// Llamar cuando se SUELTA el boton
	void EndOvertake();

	void Update(const float& time, const Vector3D& gravity) override;
	void Reset();
	Solid* Clone() override;
};

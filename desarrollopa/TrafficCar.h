#pragma once
#include "Car.h"

// Coche de trafico (los que hay que adelantar o esquivar)
class TrafficCar : public Car
{
private:
	bool isOvertaken;        // Si ya fue adelantado
	bool hasGivenPoints;     // Si ya dio puntos (para no dar dos veces)
	float spawnZ;			 // Donde aparecio

public:
	TrafficCar(bool leftLane = false) : Car() {
		this->isOvertaken = false;
		this->hasGivenPoints = false;
		this->spawnZ = 0.0f;
		this->isInLeftLane = leftLane;
	}

	// Getters
	inline bool IsOvertaken() const { return this->isOvertaken; }
	inline bool HasGivenPoints() const { return this->hasGivenPoints; }
	inline float GetSpawnZ() const { return this->spawnZ; }

	// Setters
	void SetOvertaken(bool overtaken) { this->isOvertaken = overtaken; }
	void SetHasGivenPoints(bool given) { this->hasGivenPoints = given; }
	void SetSpawnZ(float z) { this->spawnZ = z; }

	void Update(const float& time, const Vector3D& gravity) override;
	
	// Comprueba si el jugador nos ha adelantado
	bool CheckIfOvertakenBy(Car* player);
	
	Solid* Clone() override;
};

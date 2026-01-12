#pragma once
#include "Vector3D.h"
#include "Orientation.h"
#include "Color.h"
class Solid
{
private:
	int incrementoTiempo;

	Vector3D coord;

	Color color;

	Orientation rot;

	Vector3D orientationSpeed;

	Vector3D speed;

	bool isAffectedByGravity;

public:
	Solid() {
		this->incrementoTiempo = 1;
		this->coord = Vector3D(0.0, 0.0, 0.0);
		this->rot = Orientation(Vector3D(0.0,0.0,0.0));
		this->color = Color(0.0, 0.0, 0.0);
		this->orientationSpeed = Vector3D(0.0, 0.0, 0.0);
		this->speed = Vector3D(0.0, 0.0, 0.0);
		this->isAffectedByGravity = false;
	}
	inline Vector3D GetCoord() { return this->coord; }
	inline Orientation GetRot() { return this->rot; }
	inline Color GetColor() { return this->color; }
	inline Vector3D GetOrientationSpeed() { return this->orientationSpeed; }
	inline Vector3D GetSpeed() { return this->speed; }
	inline bool GetAffectedG() { return this->isAffectedByGravity; }

	void SetCoordinates(Vector3D coordsToSet) { this->coord = coordsToSet; }
	void SetRot(Orientation orientationToSet) { this->rot = orientationToSet; }
	virtual void SetColor(Color colorToSet) { this->color = colorToSet; }
	void SetOrientationSpeed(Vector3D orientationSpeedToSet) { this->orientationSpeed = orientationSpeedToSet; }
	void SetSpeed(Vector3D speedToSet) { this->speed = speedToSet; }
	void SetAffectedG(bool boolToSet) { this->isAffectedByGravity = boolToSet; }

	virtual Solid* Clone()=0;
	virtual void Render() = 0;
	virtual void Update(const float& time, const Vector3D& gravity);
};



#include "TrafficCar.h"

void TrafficCar::Update(const float& time, const Vector3D& gravity)
{
	Vector3D pos = GetCoord();
	
	// Los coches de trafico se mueven hacia el jugador (Z positivo)
	// porque la carretera viene hacia nosotros
	pos.SetZ(pos.GetZ() + currentSpeed * time);
	SetCoordinates(pos);
}

bool TrafficCar::CheckIfOvertakenBy(Car* player)
{
	if (!player || hasGivenPoints) return false;

	Vector3D playerPos = player->GetCoord();
	Vector3D myPos = GetCoord();

	// El jugador adelanta cuando su Z es menor (esta mas cerca de la camara)
	// y el coche de trafico ya paso de largo
	if (myPos.GetZ() > playerPos.GetZ() + player->GetCarLength()) {
		isOvertaken = true;
		return true;
	}
	return false;
}

Solid* TrafficCar::Clone()
{
	return new TrafficCar(*this);
}

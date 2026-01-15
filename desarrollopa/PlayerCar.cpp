#include "PlayerCar.h"
#include <algorithm>
#include <cmath>
#include <iostream>

void PlayerCar::StartOvertake()
{
	if (overtakeState == OvertakeState::IDLE) {
		overtakeState = OvertakeState::CHANGING_LEFT;
		overtakeButtonPressed = true;
		std::cout << "[PLAYER] Iniciando adelantamiento..." << std::endl;
	}
}

void PlayerCar::EndOvertake()
{
	overtakeButtonPressed = false;

	if (overtakeState == OvertakeState::OVERTAKING) {
		overtakeState = OvertakeState::CHANGING_RIGHT;
		std::cout << "[PLAYER] Volviendo al carril..." << std::endl;
	}
}

void PlayerCar::Update(const float& time, const Vector3D& gravity)
{
	Vector3D pos = GetCoord();
	float currentX = pos.GetX();

	switch (overtakeState) {
	case OvertakeState::IDLE:
		currentSpeed = minSpeed;
		break;

	case OvertakeState::CHANGING_LEFT:
		// Aceleracion MUY rapida - casi instantanea
		currentSpeed += acceleration * time;
		if (currentSpeed >= overtakeSpeed) {
			currentSpeed = overtakeSpeed;
		}

		// Movemos hacia la izquierda
		currentX -= laneChangeSpeed * time;
		if (currentX <= leftLaneX) {
			currentX = leftLaneX;
			overtakeState = OvertakeState::OVERTAKING;
			isInLeftLane = true;
			std::cout << "[PLAYER] En carril izquierdo! Velocidad: " << currentSpeed << std::endl;
		}
		pos.SetX(currentX);
		SetCoordinates(pos);
		break;

	case OvertakeState::OVERTAKING:
		// Mantenemos velocidad alta
		currentSpeed = overtakeSpeed;

		if (!overtakeButtonPressed) {
			overtakeState = OvertakeState::CHANGING_RIGHT;
		}
		break;

	case OvertakeState::CHANGING_RIGHT:
		// Frenamos gradualmente
		currentSpeed -= acceleration * 0.3f * time;
		if (currentSpeed < minSpeed) {
			currentSpeed = minSpeed;
		}

		// Movemos hacia la derecha
		currentX += laneChangeSpeed * time;
		if (currentX >= rightLaneX) {
			currentX = rightLaneX;
			overtakeState = OvertakeState::IDLE;
			isInLeftLane = false;
			currentSpeed = minSpeed;
			std::cout << "[PLAYER] De vuelta en carril derecho. Velocidad: " << currentSpeed << std::endl;
		}
		pos.SetX(currentX);
		SetCoordinates(pos);
		break;
	}
}

void PlayerCar::Reset()
{
	SetCoordinates(Vector3D(rightLaneX, 0.0f, 0.0f));
	currentSpeed = minSpeed;
	overtakeState = OvertakeState::IDLE;
	isInLeftLane = false;
	overtakeButtonPressed = false;
}

Solid* PlayerCar::Clone()
{
	return new PlayerCar(*this);
}

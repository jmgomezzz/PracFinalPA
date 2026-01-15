#include "TrafficManager.h"
#include <iostream>

TrafficManager::TrafficManager()
	: spawnDistance(80.0f), despawnDistance(-30.0f), spawnTimer(0.0f),
	spawnInterval(0.6f),  // Spawn mas frecuente
	rightLaneBaseSpeed(0.0f), leftLaneBaseSpeed(20.0f),
	rightLaneX(2.0f), leftLaneX(-2.0f), rng(std::random_device{}()),
	spawnChance(0.0f, 1.0f)
{
}

TrafficManager::~TrafficManager()
{
	Clear();
}

void TrafficManager::Init(float playerMinSpeed)
{
	rightLaneBaseSpeed = 0.0f;
	leftLaneBaseSpeed = 25.0f;
}

TrafficCar* TrafficManager::CreateTrafficCar(bool leftLane)
{
	TrafficCar* car = new TrafficCar(leftLane);

	float xPos = leftLane ? leftLaneX : rightLaneX;
	float speed = leftLane ? leftLaneBaseSpeed : rightLaneBaseSpeed;

	car->SetCoordinates(Vector3D(xPos, 0.0f, -spawnDistance));
	car->SetCurrentSpeed(speed);
	car->SetSpawnZ(-spawnDistance);

	if (leftLane) {
		car->SetColor(Color(0.9f, 0.1f, 0.1f));
	}
	else {
		car->SetColor(Color(0.1f, 0.4f, 0.9f));
	}

	return car;
}

void TrafficManager::SpawnCars(const float& time)
{
	spawnTimer += time;

	if (spawnTimer >= spawnInterval) {
		spawnTimer = 0.0f;

		// Carril derecho - mas coches para dar reto
		float chance = spawnChance(rng);
		if (chance > 0.25f) {  // 75% de probabilidad
			trafficCars.push_back(CreateTrafficCar(false));
			std::cout << "[TRAFFIC] Coche en carril derecho" << std::endl;
		}

		// Carril izquierdo - menos frecuente pero presente
		chance = spawnChance(rng);
		if (chance > 0.6f) {  // 40% de probabilidad
			trafficCars.push_back(CreateTrafficCar(true));
			std::cout << "[TRAFFIC] Coche en carril izquierdo" << std::endl;
		}
	}
}

void TrafficManager::Update(const float& time, PlayerCar* player)
{
	SpawnCars(time);

	float playerSpeed = player->GetCurrentSpeed();

	for (auto* car : trafficCars) {
		if (car->IsInLeftLane()) {
			car->SetCurrentSpeed(leftLaneBaseSpeed + playerSpeed);
		}
		else {
			car->SetCurrentSpeed(playerSpeed);
		}
		
		car->Update(time, Vector3D());
	}

	RemoveOffscreenCars();
}

void TrafficManager::RemoveOffscreenCars()
{
	auto it = trafficCars.begin();
	while (it != trafficCars.end()) {
		if ((*it)->GetCoord().GetZ() > 10.0f) {
			delete* it;
			it = trafficCars.erase(it);
		}
		else {
			++it;
		}
	}
}

int TrafficManager::CheckOvertakes(PlayerCar* player)
{
	int points = 0;

	for (auto* car : trafficCars) {
		if (!car->IsInLeftLane() && !car->HasGivenPoints()) {
			if (car->CheckIfOvertakenBy(player)) {
				car->SetHasGivenPoints(true);
				points += 10;
				std::cout << "[TRAFFIC] Adelantamiento!" << std::endl;
			}
		}
	}

	return points;
}

bool TrafficManager::CheckCollisions(PlayerCar* player)
{
	for (auto* car : trafficCars) {
		if (player->CheckCollision(car)) {
			return true;
		}
	}
	return false;
}

void TrafficManager::Render()
{
	for (auto* car : trafficCars) {
		car->Render();
	}
}

void TrafficManager::Clear()
{
	for (auto* car : trafficCars) {
		delete car;
	}
	trafficCars.clear();
}

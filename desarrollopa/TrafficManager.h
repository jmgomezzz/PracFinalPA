#pragma once
#include "TrafficCar.h"
#include "PlayerCar.h"
#include <vector>
#include <random>

// Gestor de todo el trafico del juego
// Se encarga de crear coches, moverlos y detectar colisiones
class TrafficManager
{
private:
	std::vector<TrafficCar*> trafficCars;
	
	float spawnDistance;     // A que distancia aparecen
	float despawnDistance;   // Cuando desaparecen
	float spawnTimer;
	float spawnInterval;  // Cada cuanto aparece un coche
	
	float rightLaneBaseSpeed;    // Velocidad base de coches en carril derecho
	float leftLaneBaseSpeed;     // Velocidad base de coches en carril izquierdo
	float rightLaneX;
	float leftLaneX;

	// Para generar numeros aleatorios
	std::mt19937 rng;
	std::uniform_real_distribution<float> spawnChance;

	TrafficCar* CreateTrafficCar(bool leftLane);

public:
	TrafficManager();
	~TrafficManager();

	void Init(float playerMinSpeed);
	void Update(const float& time, PlayerCar* player);
	void SpawnCars(const float& time);
	void RemoveOffscreenCars();
	
	int CheckOvertakes(PlayerCar* player);
	bool CheckCollisions(PlayerCar* player);
	
	void Render();
	void Clear();

	inline std::vector<TrafficCar*>& GetTrafficCars() { return trafficCars; }
};

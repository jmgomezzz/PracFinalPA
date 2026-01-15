#pragma once
#include <string>
#include <algorithm>

// Configuracion de un nivel
// Cada nivel tiene diferentes parametros de dificultad
class Level
{
private:
	int levelNumber;
	std::string levelName;
	
	// Parametros de dificultad
	float spawnInterval;     // Tiempo entre spawns
	float rightLaneProb;     // Probabilidad carril derecho
	float leftLaneProb;      // Probabilidad carril izquierdo
	float trafficSpeed;      // Velocidad base del trafico
	int scoreToNext;      // Puntos para pasar al siguiente nivel

public:
	Level(int num = 1);

	// Getters
	inline int GetLevelNumber() const { return levelNumber; }
	inline std::string GetLevelName() const { return levelName; }
	inline float GetSpawnInterval() const { return spawnInterval; }
	inline float GetRightLaneProb() const { return rightLaneProb; }
	inline float GetLeftLaneProb() const { return leftLaneProb; }
	inline float GetTrafficSpeed() const { return trafficSpeed; }
	inline int GetScoreToNext() const { return scoreToNext; }

	// Configurar nivel segun numero
	void ConfigureLevel(int num);

	// Comprobar si se pasa de nivel
	bool CheckLevelUp(int currentScore);
};

#include "Level.h"

Level::Level(int num) {
	ConfigureLevel(num);
}

void Level::ConfigureLevel(int num)
{
	levelNumber = num;

	// Cada nivel es mas dificil
	switch (num) {
	case 1:
		levelName = "Carretera Tranquila";
		spawnInterval = 2.0f;
		rightLaneProb = 0.5f;
		leftLaneProb = 0.3f;
		trafficSpeed = 20.0f;
		scoreToNext = 100;
		break;

	case 2:
		levelName = "Hora Punta";
		spawnInterval = 1.2f;
		rightLaneProb = 0.6f;
		leftLaneProb = 0.4f;
		trafficSpeed = 25.0f;
		scoreToNext = 250;
		break;

	case 3:
		levelName = "Autopista Infernal";
		spawnInterval = 0.8f;
		rightLaneProb = 0.75f;
		leftLaneProb = 0.5f;
		trafficSpeed = 30.0f;
		scoreToNext = 500;
		break;

	default:
		// Niveles superiores: cada vez mas dificil
		levelName = "Nivel " + std::to_string(num);
		spawnInterval = std::max(0.4f, 2.0f - (num * 0.3f));
		rightLaneProb = std::min(0.9f, 0.5f + (num * 0.1f));
		leftLaneProb = std::min(0.7f, 0.3f + (num * 0.1f));
		trafficSpeed = 20.0f + (num * 5.0f);
		scoreToNext = num * 150;
		break;
	}
}

bool Level::CheckLevelUp(int currentScore)
{
	return currentScore >= scoreToNext;
}

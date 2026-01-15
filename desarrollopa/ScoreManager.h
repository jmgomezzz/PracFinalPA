#pragma once
#include <string>

// Gestor de puntuacion
// Lleva la cuenta de adelantamientos y puntos
class ScoreManager
{
private:
	int score;
	int overtakenCars;       // Cuantos coches hemos adelantado
	int highScore;           // Mejor puntuacion

public:
	ScoreManager() : score(0), overtakenCars(0), highScore(0) {}

	// Getters
	inline int GetScore() const { return score; }
	inline int GetOvertakenCars() const { return overtakenCars; }
	inline int GetHighScore() const { return highScore; }

	void AddPoints(int points);
	void AddOvertake();
	void Reset();
	void UpdateHighScore();
	
	// Para mostrar en pantalla
	std::string GetScoreText() const;
};

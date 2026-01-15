#include "ScoreManager.h"
#include <sstream>
#include <algorithm>

void ScoreManager::AddPoints(int points)
{
	score += points;
}

void ScoreManager::AddOvertake()
{
	overtakenCars++;
	AddPoints(10);  // 10 puntos por adelantamiento
}

void ScoreManager::Reset()
{
	UpdateHighScore();
	score = 0;
	overtakenCars = 0;
}

void ScoreManager::UpdateHighScore()
{
	highScore = std::max(highScore, score);
}

std::string ScoreManager::GetScoreText() const
{
	std::stringstream ss;
	ss << "Puntos: " << score << " | Adelantamientos: " << overtakenCars;
	return ss.str();
}

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>

// Estructura para guardar una puntuacion
struct ScoreEntry {
	std::string playerName;
	int score;
	int level;

	ScoreEntry(std::string name = "AAA", int s = 0, int l = 1)
		: playerName(name), score(s), level(l) {}
};

// Gestor de puntuaciones con guardado en disco
// Usa excepciones para manejar errores de archivo
class HighScoreManager
{
private:
	std::vector<ScoreEntry> scores;
	std::string filename;
	int maxScores;

public:
	HighScoreManager(std::string file = "highscores.dat", int max = 10)
		: filename(file), maxScores(max) {}

	// Cargar puntuaciones del archivo
	void LoadScores();

	// Guardar puntuaciones al archivo
	void SaveScores();

	// Añadir nueva puntuacion
	void AddScore(const std::string& name, int score, int level);

	// Comprobar si una puntuacion entra en el ranking
	bool IsHighScore(int score);

	// Getters
	inline std::vector<ScoreEntry>& GetScores() { return scores; }
	inline int GetMaxScores() { return maxScores; }
};

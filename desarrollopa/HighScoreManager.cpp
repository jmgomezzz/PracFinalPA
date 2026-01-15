#include "HighScoreManager.h"
#include <iostream>

void HighScoreManager::LoadScores()
{
	scores.clear();

	try {
		std::ifstream file(filename, std::ios::binary);
		if (!file.is_open()) {
			throw std::runtime_error("No se pudo abrir el archivo de puntuaciones");
		}

		int count;
		file.read(reinterpret_cast<char*>(&count), sizeof(count));

		for (int i = 0; i < count && i < maxScores; i++) {
			ScoreEntry entry;
			int nameLength;
			file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

			entry.playerName.resize(nameLength);
			file.read(&entry.playerName[0], nameLength);
			file.read(reinterpret_cast<char*>(&entry.score), sizeof(entry.score));
			file.read(reinterpret_cast<char*>(&entry.level), sizeof(entry.level));

			scores.push_back(entry);
		}

		file.close();
		std::cout << "Puntuaciones cargadas correctamente" << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Aviso: " << e.what() << ". Se creara uno nuevo." << std::endl;
		// No es error grave, simplemente no hay archivo todavia
	}
}

void HighScoreManager::SaveScores()
{
	try {
		std::ofstream file(filename, std::ios::binary | std::ios::trunc);
		if (!file.is_open()) {
			throw std::runtime_error("No se pudo crear el archivo de puntuaciones");
		}

		int count = static_cast<int>(scores.size());
		file.write(reinterpret_cast<char*>(&count), sizeof(count));

		for (auto& entry : scores) {
			int nameLength = static_cast<int>(entry.playerName.length());
			file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
			file.write(entry.playerName.c_str(), nameLength);
			file.write(reinterpret_cast<char*>(&entry.score), sizeof(entry.score));
			file.write(reinterpret_cast<char*>(&entry.level), sizeof(entry.level));
		}

		file.close();
		std::cout << "Puntuaciones guardadas correctamente" << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error al guardar puntuaciones: " << e.what() << std::endl;
		throw;  // Re-lanzamos la excepcion
	}
}

void HighScoreManager::AddScore(const std::string& name, int score, int level)
{
	ScoreEntry newEntry(name, score, level);
	scores.push_back(newEntry);

	// Ordenar de mayor a menor
	std::sort(scores.begin(), scores.end(),
		[](const ScoreEntry& a, const ScoreEntry& b) {
			return a.score > b.score;
		});

	// Mantener solo los mejores
	if (scores.size() > static_cast<size_t>(maxScores)) {
		scores.resize(maxScores);
	}

	SaveScores();
}

bool HighScoreManager::IsHighScore(int score)
{
	if (scores.size() < static_cast<size_t>(maxScores)) {
		return true;
	}
	return score > scores.back().score;
}

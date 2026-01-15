#pragma once
// Objetos
#include "Model.h"
#include "ModelLoader.h"
#include "Teapot.h"
#include "Cube.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Solid.h"
#include "Scene.h"
#include "Toroid.h"
#include "Cylinder.h"
#include "Road.h"

// Sistema de carreras
#include "PlayerCar.h"
#include "TrafficCar.h"
#include "TrafficManager.h"
#include "ScoreManager.h"
#include "HighScoreManager.h"
#include "Level.h"

// El sistema de partículas
#include "Emmiter.h"
#include "EmmiterConfiguration.h"

#include <chrono>
using namespace std::chrono;
using namespace std;

enum class GameState {
	MENU,
	PLAYING,
	GAME_OVER,
	HIGH_SCORES
};

class Game
{
private:
	// Gestion de multiples escenas
	Scene* menuScene;
	Scene* gameScene;
	Scene* gameOverScene;
	Scene* activeScene;
	vector<Scene*> scenes;

	// Objetos decorativos
	Teapot teapot;
	Cube cube;
	Cuboid cuboid;
	Sphere sphere;
	Cylinder cylinder;
	Toroid toroid;

	// Emisores
	Emmiter* emisores[3];
	Solid* particulaBase;

	// Control de tiempo
	std::chrono::milliseconds initialMilliseconds;
	long lastUpdatedTime;

	// Sistema de carreras
	GameState gameState;
	PlayerCar* playerCar;
	TrafficManager trafficManager;
	ScoreManager scoreManager;
	HighScoreManager highScoreManager;
	Level currentLevel;
	Road* road;

	// Metodos privados
	void InitScenes();
	void InitRacingGame();
	void UpdateRacingGame(const float& time);
	void RenderMenu();
	void RenderRacingGame();
	void RenderHUD();
	void RenderGameOver();
	void RenderHighScores();
	void HandleCollision();
	void CheckLevelUp();
	void ApplyLevelSettings();

public:
	const float TIME_INCREMENT = 0.016f;
	const float UPDATE_PERIOD = 10;

	Game();
	~Game();

	void Init();
	void Render();
	void Update(const float& time, const Vector3D& gravity);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessKeyReleased(unsigned char key, int px, int py);
	void ProcessMouseMovement(int x, int y);
	void ProcessMouseClicked(int button, int state, int x, int y);

	void StartGame();
	void RestartGame();
	void GoToMenu();
	void ShowHighScores();
};



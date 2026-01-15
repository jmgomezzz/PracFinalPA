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

// El sistema de partículas
#include "Emmiter.h"
#include "EmmiterConfiguration.h"

//Control de periodo de actualización
#include <chrono>
using namespace std::chrono;

using namespace std;

// Estados del juego
enum class GameState {
	MENU,
	PLAYING,
	GAME_OVER
};

class Game
{
private:
	Scene escena;

	// Objetos decorativos
	Teapot teapot;
	Cube cube;
	Cuboid cuboid;
	Sphere sphere;
	Cylinder cylinder;
	Toroid toroid;

	// VARIABLES DEL EMISOR
	Emmiter* emisores[3];
	Solid* particulaBase;

	//Gestión de múltiples escenas
	Scene* activeScene;
	vector<Scene*> scenes;

	//Control de periodo de actualización
	std::chrono::milliseconds initialMilliseconds;
	long lastUpdatedTime;

	// ===============================
	// SISTEMA DE CARRERAS
	// ===============================
	GameState gameState;
	PlayerCar* playerCar;
	TrafficManager trafficManager;
	ScoreManager scoreManager;
	Road* road;

	// Metodos privados del juego de carreras
	void InitRacingGame();
	void UpdateRacingGame(const float& time);
	void RenderRacingGame();
	void RenderHUD();
	void RenderGameOver();
	void HandleCollision();

public:
	//Control de periodo de actualización
	const float TIME_INCREMENT = 0.016f;  // ~60 FPS
	const float UPDATE_PERIOD = 10;

	Game();
	~Game();

	void Init();
	void Render();
	void Update(const float& time, const Vector3D& gravity);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessKeyReleased(unsigned char key, int px, int py);  // Para detectar cuando se suelta
	void ProcessMouseMovement(int x, int y);
	void ProcessMouseClicked(int button, int state, int x, int y);

	void RestartGame();
};



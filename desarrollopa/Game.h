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

// El sistema de partículas
#include "Emmiter.h"
#include "EmmiterConfiguration.h"

//Control de periodo de actualización
#include <chrono>
using namespace std::chrono;

using namespace std;

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

	//Controles de movimiento (sobre objeto)
	Model* player;
	

public:
	//Control de periodo de actualización
	const float TIME_INCREMENT = 0.4;
	const float UPDATE_PERIOD = 10;

	Game() : emisores(), particulaBase(nullptr), activeScene(nullptr), initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())), lastUpdatedTime(0), player(nullptr){}

	void Init();
	void Render();
	void Update(const float& time, const Vector3D& gravity);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessMouseMovement(int x, int y);
	void ProcessMouseClicked(int button, int state, int x, int y);
};



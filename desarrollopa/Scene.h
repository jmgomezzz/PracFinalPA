#pragma once
#include <vector>
#include "Solid.h"
#include "Camera.h"
using namespace std;
class Scene
{
private:
	vector<Solid*> gameObjects;
	Camera* camara;
	Vector3D boundary;
	
	void checkBoundary() {
		bool X = false;
		bool Y = false;
		bool Z = false;
		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i]->GetCoord().GetX() > this->GetBoundary().GetX()) { X = true; }
			else if (gameObjects[i]->GetCoord().GetX()< (this->GetBoundary().GetX())*-1) { X = true; }
			else if (gameObjects[i]->GetCoord().GetY() > this->GetBoundary().GetY()) { Y = true; }
			else if (gameObjects[i]->GetCoord().GetY() < (this->GetBoundary().GetY()) * -1) { Y = true; }
			else if (gameObjects[i]->GetCoord().GetZ() > this->GetBoundary().GetZ()) { Z = true; }
			else if (gameObjects[i]->GetCoord().GetZ() < (this->GetBoundary().GetZ()) * -1) { Z = true; }
		
			if (X) {gameObjects[i]->SetSpeed(Vector3D(gameObjects[i]->GetSpeed().GetX() * -1, gameObjects[i]->GetSpeed().GetY(), gameObjects[i]->GetSpeed().GetZ()));}
			if (Y) { gameObjects[i]->SetSpeed(Vector3D(gameObjects[i]->GetSpeed().GetX(), gameObjects[i]->GetSpeed().GetY() * -1, gameObjects[i]->GetSpeed().GetZ())); }
			if (Z) { gameObjects[i]->SetSpeed(Vector3D(gameObjects[i]->GetSpeed().GetX(), gameObjects[i]->GetSpeed().GetY(), gameObjects[i]->GetSpeed().GetZ() * -1)); }
		}
	};
public:
	Vector3D G;//factor de Gravedad 

	Scene() {
		this->boundary = Vector3D(8.0,6.0,4.0);
		this->gameObjects = {};
		this->camara= new Camera(Vector3D(0.0,0.0,16.0));
		this->G = Vector3D(0, -4, 0);//'x' y 'z' en 0 y en 'y' un valor negativo
	}

	inline Vector3D GetBoundary() { return this->boundary; }

	void AddGameObject(Solid* objeto);
	void Render();
	void Update(const float& time, const Vector3D& gravity);
};


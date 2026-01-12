#include "Scene.h"
#include <iostream>
#include <vector>
void Scene::AddGameObject(Solid* objeto)
{
	gameObjects.push_back(objeto);
}
void Scene::Render() {
	this->camara->Render();
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Render();
	}
}
void Scene::Update(const float& time, const Vector3D& gravity) {
	this->camara->Update(time,this->G);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Update(time,this->G);
	}
	checkBoundary();
}


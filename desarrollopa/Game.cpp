#include "Game.h"
#include <iostream>
void Game::Init() {
	/////////////////////////////
	//EMISORES///////////////////
	/////////////////////////////
	/*this->particulaBase = new Cube();
	//Le damos un color base aunque cammbie luego
	((Cube*)this->particulaBase)->SetSize(0.1f);

	this->particulaBase->SetColor(Color(1.0, 0.0, 0.0));
	//Cambiamos tamaño de los cubos

	//Config
	EmmiterConfiguration config(300, 0, this->particulaBase, Vector3D(0.00, 0.02, 0.00), 750);


	//Varios emisores para dar efecto de fuego
	for (int i = 0; i < 3; i++) {
		this->emisores[i] = new Emmiter();
		this->emisores[i]->SetConfiguration(config);
	}

	//Emisor en el centro y cercanos
	this->emisores[0]->SetCoordinates(Vector3D(-0.3, -2.0, -5.0));
	this->emisores[1]->SetCoordinates(Vector3D(0.0, -2.0, -5.0));
	this->emisores[2]->SetCoordinates(Vector3D(0.3, -2.0, -5.0));*/

	/////////////////////////////
	//ESCENAS////////////////////
	/////////////////////////////
	Scene* mainScene = new(nothrow) Scene();

	this->scenes.push_back(mainScene);
	this->activeScene = mainScene;

	//Configuración de cámara
	Camera* cam = activeScene->GetCamera();
	cam->SetCoordinates(Vector3D(0.0f, 5.0, 10.0f));    
	cam->SetRot(Orientation(Vector3D(-10.0f, 0.0f, 0.0f))); // Rotación: inclinada hacia abajo


	/*teapot.SetCoordinates(Vector3D(-1.6, 1.3, -3.0));
	teapot.SetColor(Color(0.2f, 0.4f, 0.6f));
	teapot.SetOrientationSpeed(Vector3D(1.0, 3.0, 0.0));
	activeScene->AddGameObject(&teapot);*/

	//Instanciación de modelo
	/*ModelLoader* loader = new ModelLoader();
	Model* star= new Model();
	//METER RUTA DE ARCHIVO DE OBJETO AQUI (descomentar)
	loader->LoadModel("../modelos/star.obj");
	*star = loader->GetModel();
	star->SetCoordinates(Vector3D(0.0, 0.6, -3.0));
	star->SetOrientationSpeed(Vector3D(1.0, 3.0, 0.0));
	//star->SetSpeed(Vector3D(0.0, 0.0, 0.0));
	star->SetColor(Color(0.2f, 0.4f, 0.6f));
	activeScene->AddGameObject(star);
	loader->Clear();*/

	ModelLoader* loader = new ModelLoader();
	// Mejor no metemos modelo de carretera <3
	// Crear la carretera y asignarle el modelo
	Road* carretera = new Road(30, 5.0f, 8.0f, 15.0f);

	activeScene->AddGameObject(carretera);



}

void Game::Render() {

	// Emisor
	for (int i = 0; i < 3; i++) {
		if (this->emisores[i] != nullptr) {
			this->emisores[i]->Render();
		}
	}

	//Escena
	this->activeScene->Render();
	
}

void Game::Update(const float& time, const Vector3D& gravity) {

	// Emisor
	for (int i = 0; i < 3; i++) {
		if (this->emisores[i] != nullptr) {
			this->emisores[i]->Update(TIME_INCREMENT,gravity);
		}
	}

	//Escena
	//this->activeScene->Update(TIME_INCREMENT,gravity);

	//Control de periodo de actualización
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD) {
		this->activeScene->Update(TIME_INCREMENT,gravity);
		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}

}

void Game::ProcessKeyPressed(unsigned char key, int px, int py)
{
	cout << "[GAME] Key:" << key << endl;
	if (key == 'w') {
		this->player->SetSpeed(
		Vector3D(
		this->player->GetSpeed().GetX(),
			this->player->GetSpeed().GetY()+0.01,
			this->player->GetSpeed().GetZ()));
	}
	if (key == 's') {
		this->player->SetSpeed(
			Vector3D(
				this->player->GetSpeed().GetX(),
				this->player->GetSpeed().GetY() - 0.01,
				this->player->GetSpeed().GetZ()));
	}
	if (key == 'a') {
		this->player->SetSpeed(
			Vector3D(
				this->player->GetSpeed().GetX() - 0.01,
				this->player->GetSpeed().GetY(),
				this->player->GetSpeed().GetZ()));
	}
	if (key == 'a') {
		this->player->SetSpeed(
			Vector3D(
				this->player->GetSpeed().GetX() + 0.01,
				this->player->GetSpeed().GetY(),
				this->player->GetSpeed().GetZ()));
	}

}

void Game::ProcessMouseClicked(int button, int state, int x, int y)
{
	cout << "[GAME] Click:" << button << endl;
	
}

void Game::ProcessMouseMovement(int x, int y)
{
	cout << "[GAME] Movement:" << x << ", " << y << endl;
}

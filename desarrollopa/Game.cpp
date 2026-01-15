#include "Game.h"
#include <GL/glut.h>
#include <iostream>

Game::Game() : emisores(), particulaBase(nullptr), activeScene(nullptr),
	initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())),
	lastUpdatedTime(0), gameState(GameState::MENU), playerCar(nullptr), road(nullptr)
{
}

Game::~Game()
{
	delete playerCar;
	delete road;
	// Limpiamos las escenas
	for (auto* scene : scenes) {
		delete scene;
	}
}

void Game::Init() {
	InitRacingGame();
}

void Game::InitRacingGame()
{
	/////////////////////////////
	// ESCENA PRINCIPAL /////////
	/////////////////////////////
	Scene* mainScene = new(nothrow) Scene();
	this->scenes.push_back(mainScene);
	this->activeScene = mainScene;

	// Camara - valores que funcionan con la implementacion actual
	Camera* cam = activeScene->GetCamera();
	cam->SetCoordinates(Vector3D(0.0f, 5.0f, 15.0f));  // Mas atras para ver bien
	cam->SetRot(Orientation(Vector3D(20.0f, 0.0f, 0.0f)));  // Rotacion positiva mira hacia abajo

	/////////////////////////////
	// CARRETERA ////////////////
	/////////////////////////////
	road = new Road(30, 5.0f, 8.0f, 10.0f);
	activeScene->AddGameObject(road);

	/////////////////////////////
	// COCHE DEL JUGADOR ////////
	/////////////////////////////
	playerCar = new PlayerCar();
	playerCar->SetCoordinates(Vector3D(2.0f, 0.0f, 0.0f));
	playerCar->SetColor(Color(0.1f, 0.8f, 0.2f));

	/////////////////////////////
	// TRAFICO //////////////////
	/////////////////////////////
	trafficManager.Init(playerCar->GetMinSpeed());

	gameState = GameState::PLAYING;

	cout << "Pulsa ESPACIO para adelantar!" << endl;
	cout << "Manten pulsado para quedarte en el carril izquierdo" << endl;
}

void Game::Update(const float& time, const Vector3D& gravity) {
	switch (gameState) {
	case GameState::PLAYING:
		UpdateRacingGame(time);
		break;
	case GameState::GAME_OVER:
		break;
	default:
		break;
	}
}

void Game::UpdateRacingGame(const float& time)
{
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD) {
		
		// Actualizamos el jugador
		playerCar->Update(time, Vector3D());

		// IMPORTANTE: La velocidad del jugador afecta a la carretera y al trafico
		// Cuanto mas rapido va el jugador, mas rapido viene todo hacia el
		float playerSpeed = playerCar->GetCurrentSpeed();
		road->SetSpeed(playerSpeed);

		// Actualizamos el trafico con la velocidad del jugador
		trafficManager.Update(time, playerCar);

		// Actualizamos la carretera
		this->activeScene->Update(time, Vector3D());

		// Comprobamos adelantamientos
		int points = trafficManager.CheckOvertakes(playerCar);
		if (points > 0) {
			scoreManager.AddPoints(points);
			cout << "+10 puntos! Total: " << scoreManager.GetScore() << endl;
		}

		// Comprobamos colisiones
		if (trafficManager.CheckCollisions(playerCar)) {
			HandleCollision();
		}

		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}
}

void Game::Render() {
	switch (gameState) {
	case GameState::PLAYING:
		RenderRacingGame();
		break;
	case GameState::GAME_OVER:
		RenderRacingGame();  // Renderizamos el juego de fondo
		RenderGameOver();
		break;
	default:
		break;
	}
}

void Game::RenderRacingGame()
{
	// Renderizamos la escena (camara + carretera)
	this->activeScene->Render();

	// Renderizamos el jugador
	playerCar->Render();

	// Renderizamos el trafico
	trafficManager.Render();

	// Renderizamos el HUD
	RenderHUD();
}

void Game::RenderHUD()
{
	// Cambiamos a proyeccion ortografica para el HUD
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	
	glColor3f(1.0f, 1.0f, 1.0f);

	// Texto del score
	std::string scoreText = scoreManager.GetScoreText();
	glRasterPos2i(10, 570);
	for (char c : scoreText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	// Instrucciones
	std::string helpText = "ESPACIO = Adelantar | R = Reiniciar";
	glRasterPos2i(10, 20);
	for (char c : helpText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Game::RenderGameOver()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Fondo semitransparente (simulado con un rectangulo)
	glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
	glBegin(GL_QUADS);
	glVertex2i(150, 200);
	glVertex2i(650, 200);
	glVertex2i(650, 400);
	glVertex2i(150, 400);
	glEnd();

	// Texto GAME OVER
	glColor3f(1.0f, 0.0f, 0.0f);
	std::string gameOverText = "GAME OVER";
	glRasterPos2i(330, 350);
	for (char c : gameOverText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	// Puntuacion final
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string finalScore = "Puntuacion: " + std::to_string(scoreManager.GetScore());
	glRasterPos2i(320, 300);
	for (char c : finalScore) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	// Instrucciones para reiniciar
	std::string restartText = "Pulsa R para reiniciar";
	glRasterPos2i(310, 250);
	for (char c : restartText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Game::HandleCollision()
{
	cout << "COLISION! Game Over!" << endl;
	cout << "Puntuacion final: " << scoreManager.GetScore() << endl;
	gameState = GameState::GAME_OVER;
	scoreManager.UpdateHighScore();
}

void Game::ProcessKeyPressed(unsigned char key, int px, int py)
{
	cout << "Key:" << key << endl;

	if (gameState == GameState::PLAYING) {
		// ESPACIO = iniciar adelantamiento
		if (key == ' ') {
			playerCar->StartOvertake();
		}
	}
	else if (gameState == GameState::GAME_OVER) {
		if (key == 'r' || key == 'R') {
			RestartGame();
		}
	}
}

void Game::ProcessKeyReleased(unsigned char key, int px, int py)
{
	if (gameState == GameState::PLAYING) {
		// ESPACIO soltado = terminar adelantamiento
		if (key == ' ') {
			playerCar->EndOvertake();
		}
	}
}

void Game::RestartGame()
{
	cout << "Reiniciando..." << endl;
	scoreManager.Reset();
	trafficManager.Clear();

	playerCar->Reset();

	gameState = GameState::PLAYING;
}

void Game::ProcessMouseClicked(int button, int state, int x, int y)
{
	// No usamos el raton en este juego
}

void Game::ProcessMouseMovement(int x, int y)
{
	// No usamos el raton en este juego
}

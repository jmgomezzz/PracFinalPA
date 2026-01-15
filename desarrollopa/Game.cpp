#include "Game.h"
#include <GL/glut.h>
#include <iostream>

Game::Game() : emisores(), particulaBase(nullptr), activeScene(nullptr),
	menuScene(nullptr), gameScene(nullptr), gameOverScene(nullptr),
	initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())),
	lastUpdatedTime(0), gameState(GameState::MENU), playerCar(nullptr), 
	road(nullptr), currentLevel(1), highScoreManager("highscores.dat", 10)
{
}

Game::~Game()
{
	delete playerCar;
	delete road;
	for (auto* scene : scenes) {
		delete scene;
	}
}

void Game::Init() {
	// Cargar puntuaciones guardadas
	highScoreManager.LoadScores();
	
	InitScenes();
	gameState = GameState::MENU;
}

void Game::InitScenes()
{
	// Escena del menu
	menuScene = new Scene();
	menuScene->GetCamera()->SetCoordinates(Vector3D(0.0f, 0.0f, 10.0f));
	scenes.push_back(menuScene);

	// Escena del juego
	gameScene = new Scene();
	gameScene->GetCamera()->SetCoordinates(Vector3D(0.0f, 5.0f, 15.0f));
	gameScene->GetCamera()->SetRot(Orientation(Vector3D(20.0f, 0.0f, 0.0f)));
	scenes.push_back(gameScene);

	// Escena de game over
	gameOverScene = new Scene();
	gameOverScene->GetCamera()->SetCoordinates(Vector3D(0.0f, 0.0f, 10.0f));
	scenes.push_back(gameOverScene);

	activeScene = menuScene;
}

void Game::InitRacingGame()
{
	// Crear carretera
	road = new Road(30, 5.0f, 8.0f, 10.0f);
	gameScene->AddGameObject(road);

	// Crear coche del jugador
	playerCar = new PlayerCar();
	playerCar->SetCoordinates(Vector3D(2.0f, 0.0f, 0.0f));
	// Intentae cargar modelo con materiales
	playerCar->LoadMaterialModel("NormalCar2.obj", 1.0f); // Escalar para que no sea gigante

	// Configurar nivel inicial
	currentLevel.ConfigureLevel(1);
	trafficManager.Init(playerCar->GetMinSpeed());
	ApplyLevelSettings();

	activeScene = gameScene;
}

void Game::ApplyLevelSettings()
{
	// Los ajustes del nivel se aplican automaticamente por ahora
	// El TrafficManager usa sus propios valores
	cout << "=== NIVEL " << currentLevel.GetLevelNumber() << " ===" << endl;
	cout << currentLevel.GetLevelName() << endl;
	cout << "Siguiente nivel en: " << currentLevel.GetScoreToNext() << " puntos" << endl;
}

void Game::CheckLevelUp()
{
	if (currentLevel.CheckLevelUp(scoreManager.GetScore())) {
		int nextLevel = currentLevel.GetLevelNumber() + 1;
		currentLevel.ConfigureLevel(nextLevel);
		ApplyLevelSettings();
		cout << "*** SUBISTE AL NIVEL " << nextLevel << "! ***" << endl;
	}
}

void Game::StartGame()
{
	scoreManager.Reset();
	trafficManager.Clear();
	currentLevel.ConfigureLevel(1);
	
	if (playerCar == nullptr) {
		InitRacingGame();
	}
	else {
		playerCar->Reset();
	}

	gameState = GameState::PLAYING;
	activeScene = gameScene;
}

void Game::Update(const float& time, const Vector3D& gravity) {
	switch (gameState) {
	case GameState::MENU:
		// Menu estatico
		break;
	case GameState::PLAYING:
		UpdateRacingGame(time);
		break;
	case GameState::GAME_OVER:
	case GameState::HIGH_SCORES:
		break;
	}
}

void Game::UpdateRacingGame(const float& time)
{
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD) {
		
		playerCar->Update(time, Vector3D());

		float playerSpeed = playerCar->GetCurrentSpeed();
		road->SetSpeed(playerSpeed);

		trafficManager.Update(time, playerCar);
		gameScene->Update(time, Vector3D());

		int points = trafficManager.CheckOvertakes(playerCar);
		if (points > 0) {
			scoreManager.AddPoints(points);
			cout << "+10 puntos! Total: " << scoreManager.GetScore() << endl;
			CheckLevelUp();
		}

		if (trafficManager.CheckCollisions(playerCar)) {
			HandleCollision();
		}

		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}
}

void Game::Render() {
	switch (gameState) {
	case GameState::MENU:
		RenderMenu();
		break;
	case GameState::PLAYING:
		RenderRacingGame();
		break;
	case GameState::GAME_OVER:
		RenderRacingGame();
		RenderGameOver();
		break;
	case GameState::HIGH_SCORES:
		RenderHighScores();
		break;
	}
}

void Game::RenderMenu()
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

	// Titulo
	glColor3f(1.0f, 1.0f, 0.0f);
	std::string title = "JUEGO DE ADELANTAMIENTOS";
	glRasterPos2i(250, 400);
	for (char c : title) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	// Opciones
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string opt1 = "Pulsa ENTER para jugar";
	glRasterPos2i(280, 300);
	for (char c : opt1) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	std::string opt2 = "Pulsa H para ver puntuaciones";
	glRasterPos2i(260, 250);
	for (char c : opt2) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	// Controles
	glColor3f(0.7f, 0.7f, 0.7f);
	std::string controls = "Controles: ESPACIO = Adelantar";
	glRasterPos2i(280, 150);
	for (char c : controls) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Game::RenderRacingGame()
{
	gameScene->Render();
	playerCar->Render();
	trafficManager.Render();
	RenderHUD();
}

void Game::RenderHUD()
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
	
	glColor3f(1.0f, 1.0f, 1.0f);

	// Score
	std::string scoreText = scoreManager.GetScoreText();
	glRasterPos2i(10, 570);
	for (char c : scoreText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	// Nivel actual
	std::string levelText = "Nivel: " + std::to_string(currentLevel.GetLevelNumber()) + " - " + currentLevel.GetLevelName();
	glRasterPos2i(10, 545);
	for (char c : levelText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
	}

	// Progreso al siguiente nivel
	int progress = (scoreManager.GetScore() * 100) / currentLevel.GetScoreToNext();
	progress = std::min(progress, 100);
	std::string progressText = "Siguiente nivel: " + std::to_string(progress) + "%";
	glRasterPos2i(10, 525);
	for (char c : progressText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
	}

	// Controles
	std::string helpText = "ESPACIO = Adelantar | ESC = Menu";
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

	// Fondo oscuro
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2i(150, 180);
	glVertex2i(650, 180);
	glVertex2i(650, 420);
	glVertex2i(150, 420);
	glEnd();

	// Titulo GAME OVER
	glColor3f(1.0f, 0.0f, 0.0f);
	std::string gameOverText = "GAME OVER";
	glRasterPos2i(330, 370);
	for (char c : gameOverText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	// Puntuacion final
	glColor3f(1.0f, 1.0f, 1.0f);
	std::string finalScore = "Puntuacion: " + std::to_string(scoreManager.GetScore());
	glRasterPos2i(320, 320);
	for (char c : finalScore) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	// Nivel alcanzado
	std::string levelReached = "Nivel alcanzado: " + std::to_string(currentLevel.GetLevelNumber());
	glRasterPos2i(300, 290);
	for (char c : levelReached) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	// Aviso de highscore
	if (highScoreManager.IsHighScore(scoreManager.GetScore())) {
		glColor3f(1.0f, 1.0f, 0.0f);
		std::string highScoreText = "*** NUEVO RECORD! ***";
		glRasterPos2i(310, 250);
		for (char c : highScoreText) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
	}

	// Instrucciones
	glColor3f(0.8f, 0.8f, 0.8f);
	std::string restartText = "R = Reiniciar | ESC = Menu";
	glRasterPos2i(290, 210);
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

void Game::RenderHighScores()
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

	// Titulo
	glColor3f(1.0f, 1.0f, 0.0f);
	std::string title = "MEJORES PUNTUACIONES";
	glRasterPos2i(270, 520);
	for (char c : title) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	// Lista de puntuaciones
	glColor3f(1.0f, 1.0f, 1.0f);
	auto& scores = highScoreManager.GetScores();
	int y = 450;
	int rank = 1;

	for (auto& entry : scores) {
		std::string line = std::to_string(rank) + ". " + entry.playerName + 
			" - " + std::to_string(entry.score) + " pts (Nivel " + 
			std::to_string(entry.level) + ")";
		glRasterPos2i(250, y);
		for (char c : line) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
		y -= 35;
		rank++;
		if (rank > 10) break;
	}

	if (scores.empty()) {
		std::string noScores = "No hay puntuaciones todavia";
		glRasterPos2i(290, 350);
		for (char c : noScores) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
	}

	// Volver al menu
	glColor3f(0.7f, 0.7f, 0.7f);
	std::string back = "Pulsa ESC para volver al menu";
	glRasterPos2i(270, 50);
	for (char c : back) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
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
	cout << "=== GAME OVER ===" << endl;
	cout << "Puntuacion final: " << scoreManager.GetScore() << endl;
	cout << "Nivel alcanzado: " << currentLevel.GetLevelNumber() << endl;
	
	// Guardar puntuacion si es alta
	if (highScoreManager.IsHighScore(scoreManager.GetScore())) {
		highScoreManager.AddScore("PLY", scoreManager.GetScore(), currentLevel.GetLevelNumber());
		cout << "*** Nueva puntuacion alta guardada! ***" << endl;
	}

	gameState = GameState::GAME_OVER;
}

void Game::ProcessKeyPressed(unsigned char key, int px, int py)
{
	switch (gameState) {
	case GameState::MENU:
		if (key == 13) {  // ENTER
			StartGame();
		}
		else if (key == 'h' || key == 'H') {
			ShowHighScores();
		}
		break;

	case GameState::PLAYING:
		if (key == ' ') {
			playerCar->StartOvertake();
		}
		else if (key == 27) {  // ESC
			GoToMenu();
		}
		break;

	case GameState::GAME_OVER:
		if (key == 'r' || key == 'R') {
			RestartGame();
		}
		else if (key == 27) {
			GoToMenu();
		}
		break;

	case GameState::HIGH_SCORES:
		if (key == 27) {
			GoToMenu();
		}
		break;
	}
}

void Game::ProcessKeyReleased(unsigned char key, int px, int py)
{
	if (gameState == GameState::PLAYING && key == ' ') {
		playerCar->EndOvertake();
	}
}

void Game::RestartGame()
{
	scoreManager.Reset();
	trafficManager.Clear();
	currentLevel.ConfigureLevel(1);
	playerCar->Reset();
	gameState = GameState::PLAYING;
}

void Game::GoToMenu()
{
	gameState = GameState::MENU;
	activeScene = menuScene;
}

void Game::ShowHighScores()
{
	gameState = GameState::HIGH_SCORES;
}

void Game::ProcessMouseClicked(int button, int state, int x, int y) {}
void Game::ProcessMouseMovement(int x, int y) {}

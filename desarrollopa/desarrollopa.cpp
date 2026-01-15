#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Game.h"
#include "Coordinate.h"
using namespace std;

///////////////////// CONSTANTES ////////////////////////

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WINDOW_POSITION_X = 300;
const int WINDOW_POSITION_Y = 100;
const char TITLE[] = "JUEGO DE ADELANTAMIENTOS";

// Fondo azul cielo, mucho mas alegre
const GLclampf RED = 0.4f;
const GLclampf GREEN = 0.6f;
const GLclampf BLUE = 0.9f;
const GLclampf ALPHA = 1.0;

Vector3D gravedad = Vector3D(0.0f, -9.81f, 0.0f);

bool fullScreenMode = false;

/////////////////////////////////////////////////////////////////

Game game;

/////////////////////////////////////////////////////////////////

///////////////////// FUNCIONES OPENGL //////////////////////////


void initGraphics()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(RED, GREEN, BLUE, ALPHA);

    game.Init();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    game.Render();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
  glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, aspectRatio, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Función timer para limitar a 60 FPS
void timer(int value)
{
    game.Update(game.TIME_INCREMENT,gravedad);
    glutPostRedisplay();
    // 1000 ms / 60 fps = ~16 ms
    glutTimerFunc(1000 / 60, timer, 0);
}

void keyPressed(unsigned char key, int px, int py)
{
  game.ProcessKeyPressed(key, px, py);
    glutPostRedisplay();
}

// Detectar cuando se SUELTA una tecla (para el adelantamiento)
void keyReleased(unsigned char key, int px, int py)
{
    game.ProcessKeyReleased(key, px, py);
    glutPostRedisplay();
}

void mouseMoved(int x, int y)
{
    game.ProcessMouseMovement(x, y);
    glutPostRedisplay();
}

void mouseClicked(int button, int state, int x, int y)
{
    game.ProcessMouseClicked(button, state, x, y);
    glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F11:
   fullScreenMode = !fullScreenMode;
        if (fullScreenMode)
        {
  glutFullScreen();
        }
   else
 {
        glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
            glutPositionWindow(WINDOW_POSITION_X, WINDOW_POSITION_Y);
        }
     break;
    }
}

ostream& operator<<(ostream& os, const Coordinate& coord) {
    os << "(" << coord.x << "," << coord.y << ")";
    return os;
}

/////////////////////// MAIN ////////////////////////////////////

int main(int argc, char** argv)
{
    cout << "==================================" << endl;
    cout << "  JUEGO DE ADELANTAMIENTOS" << endl;
    cout << "==================================" << endl;
cout << endl;
    cout << "CONTROLES:" << endl;
    cout << "  ESPACIO - Adelantar (manten pulsado)" << endl;
    cout << "  R       - Reiniciar partida" << endl;
    cout << "  F11     - Pantalla completa" << endl;
    cout << endl;
    cout << "OBJETIVO:" << endl;
    cout << "  Adelanta coches del carril derecho para ganar puntos." << endl;
    cout << "  Cuidado con los coches del carril izquierdo!" << endl;
    cout << "==================================" << endl;
    cout << endl;

    cout << "Generando ventana..." << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow(TITLE);

    cout << "Registrando funciones de tratamiento de eventos..." << endl;
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyReleased);  // Para detectar cuando se suelta ESPACIO
    glutSpecialFunc(specialKey);
    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouseClicked);

    glutTimerFunc(0, timer, 0);

    cout << "Iniciando graficos..." << endl;
    initGraphics();

    cout << "Iniciando bucle infinito..." << endl;
    glutMainLoop();
}
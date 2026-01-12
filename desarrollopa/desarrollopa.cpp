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
const char TITLE[] = "PARTE 2";

const GLclampf RED = 0.5;
const GLclampf GREEN = 0.5;
const GLclampf BLUE = 0.5;
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

// CAMBIO: Función timer para limitar a 60 FPS
void timer(int value)
{
    game.Update(game.TIME_INCREMENT,gravedad);
    glutPostRedisplay();
    // 1000 ms / 60 fps = ~16 ms. Se llama a sí misma recursivamente.
    glutTimerFunc(1000 / 60, timer, 0);
}

void keyPressed(unsigned char key, int px, int py)
{
    game.ProcessKeyPressed(key, px, py);
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
    cout << "Hello world con OpenGL" << endl;

    cout << "Generando ventana..." << endl;
    glutInit(&argc, argv);                                          // Inicializa GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);      // doble buffer, modo RGBA, depth buffer
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);                // tamaño inicial de la ventana
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);   // posición inicial de la ventana
    glutCreateWindow(TITLE);                                        // crea una ventana con el título dado

    cout << "Registrando funciones de tratamiento de eventos..." << endl;
    glutReshapeFunc(reshape);                                       // tratamiento del evento de redimensionado de la ventana
    glutDisplayFunc(display);                                       // tratamiento del evento de repintado de la ventana
    glutKeyboardFunc(keyPressed);                                   // tratamiento del evento de tecla pulsada
    glutSpecialFunc(specialKey);                                    // tratamiento del evento de tecla especial pulsada
    glutMotionFunc(mouseMoved);                                     // tratamiento del evento de movimiento del ratón
    glutMouseFunc(mouseClicked);                                    // tratamiento del evento de clic del ratón

    // CAMBIO: Usamos timer en vez de idle
    // glutIdleFunc(idle);                                             
    glutTimerFunc(0, timer, 0);                                     // Iniciamos el temporizador

    //Coordinate coord(1.2, 4.5);//con esto podemos modelar coordenadas dentro de un espacio
   //cout<<"Coordenada:" << coord <<endl;
    cout << "Iniciando gráficos..." << endl;
    initGraphics();                                                 // Iniciamos OpenGL

    cout << "Iniciando bucle infinito..." << endl;
    cout << "Pulse F11 para activar/desactivar el modo de pantalla completa." << endl;
    glutMainLoop();
}
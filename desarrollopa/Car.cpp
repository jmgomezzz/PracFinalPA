#include "Car.h"
#include <GL/glut.h>
#include <cmath>

void Car::LoadCarModel(const std::string& path)
{
	// Intentamos cargar el modelo .obj
	ModelLoader loader;
	loader.LoadModel(path);
	
	// Copiamos los triangulos del modelo cargado
	Model loaded = loader.GetModel();
	// Si no carga bien, usamos el placeholder
}

void Car::Update(const float& time, const Vector3D& gravity)
{
	// Actualizamos posicion segun velocidad
	Vector3D pos = GetCoord();
	pos.SetZ(pos.GetZ() - currentSpeed * time);
	SetCoordinates(pos);
}

bool Car::CheckCollision(Car* other)
{
	if (!other) return false;

	Vector3D myPos = GetCoord();
	Vector3D otherPos = other->GetCoord();

	// Calculamos distancia en X y Z
	float dx = std::abs(myPos.GetX() - otherPos.GetX());
	float dz = std::abs(myPos.GetZ() - otherPos.GetZ());

	// Sumamos mitades de dimensiones para saber si colisionan
	float combinedWidth = (carWidth + other->GetCarWidth()) / 2.0f;
	float combinedLength = (carLength + other->GetCarLength()) / 2.0f;

	// Hay colision si estan dentro de ambos rangos
	return (dx < combinedWidth && dz < combinedLength);
}

void Car::RenderPlaceholder()
{
	// Dibujamos un cubo simple como coche temporal
	glPushMatrix();
	
	Vector3D pos = GetCoord();
	glTranslatef(pos.GetX(), pos.GetY() + 0.5f, pos.GetZ());
	
	Color col = GetColor();
	glColor3f(col.GetR(), col.GetG(), col.GetB());
	
	// Cuerpo del coche (un cubo alargado)
	glPushMatrix();
	glScalef(carWidth, 0.6f, carLength);
	glutSolidCube(1.0f);
	glPopMatrix();
	
	// Techo del coche (mas pequeño)
	glPushMatrix();
	glTranslatef(0.0f, 0.4f, -0.2f);
	glScalef(carWidth * 0.8f, 0.4f, carLength * 0.5f);
	glutSolidCube(1.0f);
	glPopMatrix();
	
	glPopMatrix();
}

void Car::Render()
{
	// Por ahora usamos el placeholder
	// Si tuvieras modelos .obj se renderizaria con Model::Render()
	RenderPlaceholder();
}

Solid* Car::Clone()
{
	Car* clone = new Car(*this);
	return clone;
}

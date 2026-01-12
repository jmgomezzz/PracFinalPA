#pragma once
#include "Solid.h"
class Triangle :public Solid
{
private:
	//vertice 1 
	Vector3D pos1;
	Vector3D norm1;
	Color col1;

	//vertice 2
	Vector3D pos2;
	Vector3D norm2;
	Color col2;

	//vertice 3
	Vector3D pos3;
	Vector3D norm3;
	Color col3;
	
public:
	Triangle(Vector3D p1= Vector3D(0.0, 0.0, 1.0), Vector3D p2 = Vector3D(0.0, 1.0, 0.0), Vector3D p3 = Vector3D(1.0, 0.0, 0.0), 
		Vector3D n1 = Vector3D(0.0, 0.0, 0.0), Vector3D n2 = Vector3D(0.0, 0.0, 0.0), Vector3D n3 = Vector3D(0.0, 0.0, 0.0),
		Color c1 = Color(1.0, 0.0, 0.0), Color c2 = Color(1.0, 0.0, 0.0), Color c3 = Color(1.0, 0.0, 0.0)):Solid() {

		this->pos1 = p1;
		this->norm1 = n1;
		this->col1 = c1;

		this->pos2 = p2;
		this->norm2 = n2;
		this->col2 = c2;

		this->pos3 = p3;
		this->norm3 = n3;
		this->col3 = c3;

	}

	inline Vector3D GetNormal1() { return this->norm1; }
	inline Color GetColor1() { return this->col1; }
	inline Vector3D GetPosicion1() { return this->pos1; }

	inline Vector3D GetNormal2() { return this->norm2; }
	inline Color GetColor2() { return this->col2; }
	inline Vector3D GetPosicion2() { return this->pos2; }

	inline Vector3D GetNormal3() { return this->norm3; }
	inline Color GetColor3() { return this->col3; }
	inline Vector3D GetPosicion3() { return this->pos3; }

	void SetNormal1(Vector3D normalToSet) { this->norm1 = normalToSet; }
	void SetColor1(Color colorToSet) { this->col1 = colorToSet; }
	void SetPosicion1(Vector3D posicionToSet) { this->pos1 = posicionToSet; }

	void SetNormal2(Vector3D normalToSet) { this->norm2 = normalToSet; }
	void SetColor2(Color colorToSet) { this->col2 = colorToSet; }
	void SetPosicion2(Vector3D posicionToSet) { this->pos2 = posicionToSet; }

	void SetNormal3(Vector3D normalToSet) { this->norm3 = normalToSet; }
	void SetColor3(Color colorToSet) { this->col3 = colorToSet; }
	void SetPosicion3(Vector3D posicionToSet) { this->pos3 = posicionToSet; }

	void Render();
	Solid* Clone();
};


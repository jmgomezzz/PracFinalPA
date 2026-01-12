#pragma once
#include "Model.h"
#include <string>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
using namespace std;
class ModelLoader
{
protected:
	//Atributos privados
	float escala;
	Model modelo;
	vector<Vector3D> verticesArchivo;
	vector<Vector3D> normalesArchivo;
	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

	//Metodos privados
	inline float GetWidth() { return (this->maxX - this->minX); }
	inline float GetHeight() { return (this->maxY - this->minY); }
	inline float GetLength() { return (this->maxZ - this->minZ); }
	void CalcBoundaries(Vector3D vectorPoint);
	Triangle Center(Triangle triangle);
	Vector3D parseObjLineToVector3D(const string& line);
	Triangle parseObjTriangle(const string& line);
	Vector3D parseObjVertex(const std::string& line); 
	Vector3D parseObjNormal(const std::string& line); 
	

public:

	ModelLoader() :
		escala(1.0f), 
		maxX(-99999), minX(99999), 
		maxY(-99999), minY(99999), 
		maxZ(-99999), minZ(99999) 
	{}
	

	//Métodos públicos
	Model GetModel() {return this->modelo; }
	float GetEscala() { return this->escala; }

	void Clear();
	void SetEscala(float escalaToSet) { this->escala = escalaToSet; }
	void LoadModel(const string& filePath);
};


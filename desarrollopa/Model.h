#pragma once
#include "Solid.h"
#include <vector>
#include "Triangle.h"
#include "Vertice.h"
using namespace std;
class Model :public Solid
{
private:
	vector<Triangle> triangulos;

public:
	Model(): Solid(){
		this->triangulos = {};
	}
	void Render();
	Solid* Clone();
	void AddTriangle(Triangle t);
	void SetColor(Color c) override;
	void Clear();
};


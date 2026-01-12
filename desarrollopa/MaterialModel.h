#pragma once
#include "Solid.h"
#include "MaterialTriangle.h"
#include <vector>
#include <GL/glut.h>
using namespace std;
class MaterialModel : public Solid
{
private:
	vector<MaterialTriangle> triangles;
public:
	MaterialModel():Solid() {}
	void AddMaterialTriangle(MaterialTriangle triangle);
	void Clear();
	void Render();
};


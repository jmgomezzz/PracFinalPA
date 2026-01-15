#include "MaterialModel.h"
#include <iostream>
void MaterialModel::AddMaterialTriangle(MaterialTriangle triangle)
{
	this->triangles.push_back(triangle);
}
void MaterialModel::Render()
{
	glPushMatrix();
	glTranslatef(GetCoord().GetX(), GetCoord().GetY(), GetCoord().GetZ());
	glColor3f(GetColor().GetR(), GetColor().GetG(), GetColor().GetB());
	glRotatef(GetRot().GetRotacion().GetX(), 1.0, 0.0, 0.0);
	glRotatef(GetRot().GetRotacion().GetY(), 0.0, 1.0, 0.0);
	glRotatef(GetRot().GetRotacion().GetZ(), 0.0, 0.0, 1.0);
	for (MaterialTriangle triangle : this->triangles)
	{
		triangle.Render();
	}
	glPopMatrix();
}
void MaterialModel::Clear()
{
	this->triangles.clear();
}

Solid* MaterialModel::Clone()
{
	MaterialModel* copy = new MaterialModel();
	copy->triangles = this->triangles;
	return copy;
}
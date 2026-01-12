#include "Cylinder.h"
void Cylinder::Render()
{
	GLUquadricObj* quadricTemp = gluNewQuadric();
	glPushMatrix();
	glTranslatef(this->GetCoord().GetX(), this->GetCoord().GetY(), this->GetCoord().GetZ());
	glColor3f(this->GetColor().GetR(), this->GetColor().GetG(), this->GetColor().GetB());
	glRotatef(this->GetRot().GetRotacion().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetZ(), 0.0, 0.0, 1.0);
	gluCylinder(quadricTemp,this->GetBRad(), this->GetTRad(), this->GetHeight(), this->GetSlices(), this->GetStacks());
	glPopMatrix();
	gluDeleteQuadric(quadricTemp);
}

Solid* Cylinder::Clone() {
	return new Cylinder(*this);
}
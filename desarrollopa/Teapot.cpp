#include "Teapot.h"
void Teapot::Render()
{
	glPushMatrix();
	glTranslatef(this->GetCoord().GetX(), this->GetCoord().GetY(), this->GetCoord().GetZ());
	glColor3f(this->GetColor().GetR(), this->GetColor().GetG(),this->GetColor().GetB());
	glRotatef(this->GetRot().GetRotacion().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetZ(), 0.0, 0.0, 1.0);
	glutSolidTeapot(this->GetSize());
	glPopMatrix();
}
Solid* Teapot::Clone() {
	return new Teapot(*this);
}

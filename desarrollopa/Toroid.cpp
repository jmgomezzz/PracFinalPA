#include "Toroid.h"
void Toroid::Render()
{
	glPushMatrix();
	glTranslatef(this->GetCoord().GetX(), this->GetCoord().GetY(), this->GetCoord().GetZ());
	glColor3f(this->GetColor().GetR(), this->GetColor().GetG(), this->GetColor().GetB());
	glRotatef(this->GetRot().GetRotacion().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetZ(), 0.0, 0.0, 1.0);
	glutSolidTorus(this->GetIRad(), this->GetERad(), this->GetFaces(), this->GetRings());
	glPopMatrix();
}
Solid* Toroid::Clone() {
	return new Toroid(*this);
}
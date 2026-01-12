#include "Triangle.h"
void Triangle::Render()
{
glBegin(GL_TRIANGLES);
//vértice 1
glColor3f(this->GetColor1().GetR(), this->GetColor1().GetG(), this->GetColor1().GetB());
glNormal3f(this->GetNormal1().GetX(), this->GetNormal1().GetY(), this->GetNormal1().GetZ());
glVertex3f(this->GetPosicion1().GetX(), this->GetPosicion1().GetY(), this->GetPosicion1().GetZ());
//vértice 2
glColor3f(this->GetColor2().GetR(), this->GetColor2().GetG(), this->GetColor2().GetB());
glNormal3f(this->GetNormal2().GetX(), this->GetNormal2().GetY(), this->GetNormal2().GetZ());
glVertex3f(this->GetPosicion2().GetX(), this->GetPosicion2().GetY(), this->GetPosicion2().GetZ());
//vértice 3
glColor3f(this->GetColor3().GetR(), this->GetColor3().GetG(), this->GetColor3().GetB());
glNormal3f(this->GetNormal3().GetX(), this->GetNormal3().GetY(), this->GetNormal3().GetZ());
glVertex3f(this->GetPosicion3().GetX(), this->GetPosicion3().GetY(), this->GetPosicion3().GetZ());

glEnd();

}
Solid* Triangle::Clone() {
	return new Triangle(*this);
}
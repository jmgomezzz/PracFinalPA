#include "Text.h"
void Text::Render()
{
	glPushMatrix();
	glTranslatef(this->GetCoord().GetX(), this->GetCoord().GetY(), this->GetCoord().GetZ());
	glColor3f(this->GetColor().GetR(), this->GetColor().GetG(), this->GetColor().GetB());
	glRasterPos3d(0, 0, 0);
	for (char c : texto)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	glPopMatrix();
}
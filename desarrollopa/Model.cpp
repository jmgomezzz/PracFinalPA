#include "Model.h"
void Model::Render()
{
    glPushMatrix();

    glTranslatef(GetCoord().GetX(), GetCoord().GetY(), GetCoord().GetZ());

    glRotatef(GetRot().GetRotacion().GetX(), 1, 0, 0);
    glRotatef(GetRot().GetRotacion().GetY(), 0, 1, 0);
    glRotatef(GetRot().GetRotacion().GetZ(), 0, 0, 1);

    glColor3f(GetColor().GetR(), GetColor().GetG(), GetColor().GetB());

    for (Triangle& t : triangulos)
        t.Render();

    glPopMatrix();
}

void Model::Clear() {
	triangulos.clear();
}
void Model::SetColor(Color c) {
	for (Triangle& triangle : this->triangulos) {
		//Establecemos el color a cada uno de los vertices del triangulo
		triangle.SetColor1(c);
		triangle.SetColor2(c);
		triangle.SetColor3(c);
	}
}
void Model::AddTriangle(Triangle t) {
	//Añadimos el triangulo (dirección) del triangulo al vector de triangulos
	this->triangulos.push_back(t);
}
Solid* Model::Clone() {
	return new Model(*this);
}
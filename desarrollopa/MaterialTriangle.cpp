#include "MaterialTriangle.h"
void MaterialTriangle::Render() {
	glDisable(GL_COLOR_MATERIAL);
	this->useMaterial();
	glBegin(GL_TRIANGLES);
	glNormal3f(this->GetNormal1().GetX(), this->GetNormal1().GetY(), this -> GetNormal1().GetZ());
	glVertex3f(this->GetPosicion1().GetX(), this->GetPosicion1().GetY(), this ->GetPosicion1().GetZ());
	glNormal3f(this->GetNormal2().GetX(), this->GetNormal2().GetY(), this ->GetNormal2().GetZ());
	glVertex3f(this->GetPosicion2().GetX(), this->GetPosicion2().GetY(), this ->GetPosicion2().GetZ());
	glNormal3f(this->GetNormal3().GetX(), this->GetNormal3().GetY(), this -> GetNormal3().GetZ());
	glVertex3f(this->GetPosicion3().GetX(), this->GetPosicion3().GetY(), this ->GetPosicion3().GetZ());
glEnd();
}
void MaterialTriangle::useMaterial()
{
	float MatAmbient[] = { this->material.GetAmbientColor().GetR(), this -> material.GetAmbientColor().GetG(), this->material.GetAmbientColor().GetB(), 1.0f };
	float MatDiffuse[] = { this->material.GetDiffuseColor().GetR(), this -> material.GetDiffuseColor().GetG(), this->material.GetDiffuseColor().GetB(), 1.0f };
	float MatSpecular[] = { this->material.GetSpecularColor().GetR(), this -> material.GetSpecularColor().GetG(), this->material.GetSpecularColor().GetB(), 0.1f };
	float MatShininess = 60;
	float black[] = { 0.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
}
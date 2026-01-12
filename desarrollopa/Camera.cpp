#include "Camera.h"
void Camera::Render() {
	glTranslatef((this->GetCoord().GetX())*-1,(this->GetCoord().GetY())*-1, (this->GetCoord().GetZ())*-1);
	glRotatef(this->GetRot().GetRotacion().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetRot().GetRotacion().GetZ(), 0.0, 0.0, 1.0);
}
//NO SE POR QUE QUERRIAMOS HACER ESTO PERO HAY QUE PONERLO PORQUE POR ALGUNA RAZON CAMARA HEREDA DE SOLID
Solid* Camera::Clone() {
	return new Camera(*this);
}
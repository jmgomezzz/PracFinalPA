#include "FirstPersonCamera.h"
void FirstPersonCamera::Render() {
	glRotatef(this->GetOrientationSpeed().GetX(), 1, 0, 0);
	glRotatef(this->GetOrientationSpeed().GetY(), 0, 1, 0);
	glRotatef(this->GetOrientationSpeed().GetZ(), 0, 0, 1);
	glTranslatef(-1*this->GetCoord().GetX(),-1*this->GetCoord().GetY(),this->GetCoord().GetZ());
}
void FirstPersonCamera::Update(const float& time, const Vector3D& gravity) {
	this -> SetSpeed(this->calcSpeedVector());
	Camera::Update(time,gravity);
}
Vector3D FirstPersonCamera::calcSpeedVector() {
	float yOrientation = degToRad(this->GetOrientationSpeed().GetY());
	float xOrientation = degToRad(this->GetOrientationSpeed().GetX());

	//Camara voladora
	float xComponent = sin(yOrientation) * cos(xOrientation);
	float yComponent = -sin(xOrientation);
	float zComponent = -cos(yOrientation) * cos(xOrientation);
	//Camara andante 
	//float xComponent = sin(yOrientation);
	//float yComponent = 0;
	//float zComponent = -cos(yOrientation);
	
	Vector3D speedVector = { xComponent,yComponent,zComponent };
	return speedVector;
}
void FirstPersonCamera::ProcessKeyPressed(unsigned char key, int px, int py) {
	switch (key) {
	case 'w':
	case'W':
		this->Update(this->cameraStep,Vector3D(0,0,-4));
		break;
	case 's':
	case 'S':
		this->Update(-1 * this->cameraStep, Vector3D(0, 0, -4));
		break;
	}
}
void FirstPersonCamera::ProcessMouseMovement(int x, int y) {
	if (this->GetMouseX() >= 0 && this->GetMouseY() >= 0) {
		Vector3D orientacion = this->GetRot().GetRotacion() + Vector3D(y - this->GetMouseY(), x - this->GetMouseX(), 0);
		this->SetRot(orientacion);
	}
	this->SetMouseX(x);
	this->SetMouseY(y);
}
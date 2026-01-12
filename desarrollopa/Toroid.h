#pragma once
#include <GL/glut.h>
#include "Solid.h"
class Toroid:public Solid
{
private:
	float iRad;
	float eRad;
	int faces;
	int rings;
public:
	Toroid():Solid() {
		this->iRad = 0.2;
		this->eRad = 0.4;
		this->faces = 4;
		this->rings = 6 ;
	}
	inline float GetIRad() { return this->iRad; }
	inline float GetERad() { return this->eRad; }
	inline float GetFaces() { return this->faces; }
	inline float GetRings() { return this->rings; }

	void SetIRad(float iRadToSet) { this->iRad = iRadToSet; }
	void SetERad(float eRadToSet) { this->eRad = eRadToSet; }
	void SetFaces(float facesToSet) { this->faces = facesToSet; }
	void SetRings(float ringsToSet) { this->rings = ringsToSet; }

	void Render();
	Solid* Clone() override;
};


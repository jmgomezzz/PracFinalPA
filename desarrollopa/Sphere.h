#pragma once
#include <GL/glut.h>
#include "Solid.h"
class Sphere: public Solid
{
private:

	float radius;
	float slices;
	float slacks;


public:

	Sphere():Solid()
	{
		this->radius = 0.4;
		this->slices = 10;
		this->slacks = 8;

	}
	
	inline float GetRadius() { return this->radius; }
	inline float GetSlices() { return this->slices; }
	inline float GetSlacks() { return this->slacks; }

	void SetRadius(float radiusToSet) { this->radius = radiusToSet; }
	void SetSlices(int slicesToSet) { this->slices = slicesToSet; }
	void SetSlacks(int slacksToSet) { this->slacks = slacksToSet; }


	void Render();
	Solid* Clone() override;
};


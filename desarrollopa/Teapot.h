#pragma once
#include <GL/glut.h>
#include "Solid.h"
class Teapot : public Solid
{
private:

	float size;

public:

	Teapot():Solid()
	{
		this->size = 0.4;
	}


	inline float GetSize() { return this->size; }

	void SetSize(float sizeToSet) { this->size = sizeToSet; }
	void Render();
	Solid* Clone() override;
};


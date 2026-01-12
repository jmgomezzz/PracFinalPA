#pragma once
#include <GL/glut.h>
#include "Solid.h"
class Cylinder :public Solid
{
private:
	float bRad;
	float tRad;
	float height;
	int slices;
	int stacks;
public:
	Cylinder() :Solid() {
		this->bRad = 0.6;
		this->tRad = 0.3;
		this->height = 1;
		this->slices = 4;
		this->stacks = 4;
	}

	inline float GetBRad() { return this->bRad; }
	inline float GetTRad() { return this->tRad; }
	inline float GetHeight() { return this->height; }
	inline float GetSlices() { return this->slices; }
	inline float GetStacks() { return this->stacks; }

	void SetBRad(float bRadToSet) { this->bRad = bRadToSet; }
	void SetTRad(float tRadToSet) { this->tRad = tRadToSet; }
	void SetHeight(float heightToSet) { this->height = heightToSet; }
	void SetSlices(float slicesToSet) { this->slices = slicesToSet; }
	void SetStacks(float stacksToSet) { this->stacks = stacksToSet; }

	void Render();
	Solid* Clone() override;
};


#pragma once
#include <GL/glut.h>
#include "Solid.h"
class Cube : public Solid
{
private:
    float size;

public:
    Cube() : Solid()
    {
        this->size = 0.4;
    }

    inline float GetSize() { return this->size; }
    void SetSize(float sizeToSet) { this->size = sizeToSet; }
    void Render() override;
    Solid* Clone() override;
};


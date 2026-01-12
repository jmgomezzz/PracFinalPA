#include "Road.h"
void Road::Update(const float& time, const Vector3D& gravity)//En este caso no necesitamso la gravedad
{
    for (int i = 0; i < 2; i++) {
        segments[i].pos.SetZ(segments[i].pos.GetZ() - (this->GetSpeed() * time)); //Desplazamos el segmento hacia atrás

        // Si el segmento ya salió del campo de visión, lo volvemos a mover hacia adelante, delante del otro.
        if (segments[i].pos.GetZ() <= -length) {
            segments[i].pos.SetZ(segments[i].pos.GetZ()+length * 2.0f);
        }
    }
}
void Road::Render() {
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(
            segments[i].pos.GetX(),
            segments[i].pos.GetY(),
            segments[i].pos.GetZ());
        model->Render();
        glPopMatrix();
    }
}


Solid* Road::Clone()  {
    // Creamos una nueva instancia de Road con el mismo modelo, longitud y velocidad
    Road* newRoad = new Road(this->model, this->length, this->speed);
    return newRoad;
}


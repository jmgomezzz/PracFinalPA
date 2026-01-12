#pragma once
#include "Model.h"
#include "Solid.h"
//La carretera va a estar formada por dos piezas las cuales vamos a ir desplazando hasta que se salgan fuera de la vista y entonces posicionandola detrás de la que aún si que es visible
//En el juego, lo que se va a ir desplazando en el eje z es la carretera, el coche se mantendrá en su posición z pero se moverá en las coordenadas x
class Road:public Solid
{
private:
	Model* model;
	struct Segment {
		Vector3D pos;
	};
	Segment segments[2];
	float length;//lo que mide la pieza
	float speed;
public:
	Road(Model* m=nullptr, float l=40.0f,float s=1.0f): Solid(){
		this->model = m;
		this->speed = s;
		this->length = l;
		segments[0].pos = Vector3D(0.0f,-2.0f,0.0f);
		segments[1].pos = Vector3D(0.0f,-2.0f,-length);
	}

	inline Model* GetModel() { return this->model; }
	inline float GetLength() { return this->length; }
	inline float GetSpeed() { return this->speed; }

	void SetModel(Model* modelToSet) { this->model = modelToSet; }
	void SetLength(float lengthToSet) { this->length = lengthToSet; }
	void SetSpeed(float speedToSet) { this->speed = speedToSet; }


	void Update(const float& time, const Vector3D& gravity)override;
	void Render()override;
	Solid* Clone() override;
};


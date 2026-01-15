#pragma once
#include "Model.h"
#include "ModelLoader.h"
#include "Cuboid.h"

// Clase base para todos los coches del juego
// Hereda de Model para poder cargar modelos .obj
class Car : public Model
{
protected:
	float currentSpeed;
	float lanePosition;  // -1 izquierda, 1 derecha
	bool isInLeftLane;
	
	// Dimensiones para las colisiones
	float carLength;
	float carWidth;

public:
	Car() : Model() {
		this->currentSpeed = 0.0f;
		this->lanePosition = 1.0f;
		this->isInLeftLane = false;
		this->carLength = 2.0f;
		this->carWidth = 1.2f;
	}

	// Getters
	inline float GetCurrentSpeed() const { return this->currentSpeed; }
	inline float GetLanePosition() const { return this->lanePosition; }
	inline bool IsInLeftLane() const { return this->isInLeftLane; }
	inline float GetCarLength() const { return this->carLength; }
	inline float GetCarWidth() const { return this->carWidth; }

	// Setters
	void SetCurrentSpeed(float speed) { this->currentSpeed = speed; }
	void SetLanePosition(float lane) { this->lanePosition = lane; }
	void SetIsInLeftLane(bool left) { this->isInLeftLane = left; }
	void SetCarLength(float length) { this->carLength = length; }
	void SetCarWidth(float width) { this->carWidth = width; }

	// Metodos principales
	virtual void LoadCarModel(const std::string& path);
	virtual void Update(const float& time, const Vector3D& gravity) override;
	bool CheckCollision(Car* other);
	
	// Para renderizar sin modelo (un cubo de placeholder)
	void RenderPlaceholder();
	void Render() override;
	Solid* Clone() override;
};

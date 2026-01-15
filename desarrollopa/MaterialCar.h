#pragma once
#include "Car.h"
#include "MaterialModel.h"
#include "MaterialModelLoader.h"

// Coche que carga modelos .obj con materiales .mtl
// Hereda de Car para mantener toda la logica de colisiones y movimiento
class MaterialCar : public Car
{
private:
	MaterialModel* materialModel;
	MaterialModelLoader* loader;
	bool modelLoaded;
	std::string modelsFolder;

public:
	MaterialCar(std::string folder = "modelos/") : Car() {
		this->materialModel = new MaterialModel();
		this->loader = nullptr;
		this->modelLoaded = false;
		this->modelsFolder = folder;
	}

	~MaterialCar() {
		if (materialModel != nullptr) {
			delete materialModel;
		}
		if (loader != nullptr) {
			delete loader;
		}
	}

	// Cargar modelo con materiales
	void LoadMaterialModel(const std::string& objFileName, float scale = 1.0f);

	// Getters
	inline bool IsModelLoaded() const { return modelLoaded; }
	inline MaterialModel* GetMaterialModel() { return materialModel; }

	// Override del render para usar el modelo con materiales
	void Render() override;
	Solid* Clone() override;
};
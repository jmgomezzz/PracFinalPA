#include "MaterialCar.h"
#include <GL/glut.h>
#include <iostream>

void MaterialCar::LoadMaterialModel(const std::string& objFileName, float scale)
{
	try {
		// Limpiar loader anterior
		if (loader != nullptr) {
			delete loader;
			loader = nullptr;
		}

		loader = new MaterialModelLoader(modelsFolder, scale);

		std::string fullPath = modelsFolder + objFileName;
		std::cout << "Cargando modelo: " << fullPath << std::endl;

		loader->LoadModel(fullPath);

		// Obtenemos el modelo del loader
		materialModel = loader->GetMaterialModel();

		// IMPORTANTE: Verificar que realmente se cargaron triangulos
		if (materialModel != nullptr && materialModel->GetTriangleCount() > 0) {
			modelLoaded = true;
			std::cout << "Modelo cargado! Triangulos: " << materialModel->GetTriangleCount() << std::endl;
		}
		else {
			modelLoaded = false;
			std::cout << "ERROR: No se cargaron triangulos del modelo" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		modelLoaded = false;
	}
}

void MaterialCar::Render()
{
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT);  // <-- AÑADIR ESTO


	// Posicion del coche
	Vector3D pos = GetCoord();
	glTranslatef(pos.GetX(), pos.GetY(), pos.GetZ());

	// Rotacion
	Vector3D rot = GetRot().GetRotacion();
	glRotatef(rot.GetX(), 1.0f, 0.0f, 0.0f);
	glRotatef(rot.GetY(), 0.0f, 1.0f, 0.0f);
	glRotatef(rot.GetZ(), 0.0f, 0.0f, 1.0f);

	if (modelLoaded && materialModel != nullptr) {
		// Renderizar el modelo con materiales
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f); 
		materialModel->Render();
	}
	else {
		// Si no hay modelo, usar el placeholder
		RenderPlaceholder();
	}
	 
	glPopAttrib();
	glPopMatrix();
}

Solid* MaterialCar::Clone()
{
	MaterialCar* clone = new MaterialCar(modelsFolder);
	clone->SetCoordinates(GetCoord());
	clone->SetRot(GetRot());
	clone->SetColor(GetColor());
	clone->SetCurrentSpeed(currentSpeed);
	clone->SetIsInLeftLane(isInLeftLane);
	return clone;
}
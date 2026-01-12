#pragma once
#include <string>
#include "Color.h"
#include "Vector3D.h"
#include <vector>
#include "Util.h"
using namespace Util;
using namespace std;

class Material
{
private:
private:
	string materialName;
	Color ambientColor;
	Color diffuseColor;
	Color specularColor;
	Vector3D emissiveCoeficient;
	float specularExponent;
	float dissolved;
	Color transmissionFilterColor;
	float indexOfRefraction;
	int illuminationModel;
public:
	Material(string materialNameArgument = " ") : materialName(materialNameArgument) {}
	inline string GetMaterialName() const { return this->materialName; }
	inline Color GetAmbientColor() const { return this->ambientColor; }
	inline void SetAmbientColor(const Color& ambientColorToSet)
	{
		this->ambientColor = ambientColorToSet;
		cout << this->ambientColor.GetR() << "," << this->ambientColor.GetG() <<
			"," << this->ambientColor.GetB() << endl;
	}
	inline Color GetDiffuseColor() const { return this->diffuseColor; }
	inline void SetDiffuseColor(const Color& diffuseColorToSet)
	{
		this->diffuseColor = diffuseColorToSet;
		cout << this->diffuseColor.GetR() << "," << this->diffuseColor.GetG() <<
			"," << this->diffuseColor.GetB() << endl;
	}
	inline Color GetSpecularColor() const { return this->specularColor; }
	inline void SetSpecularColor(const Color& specularColorToSet) {
		this->specularColor =
			specularColorToSet;
	}
	inline Vector3D GetEmissiveCoeficient() const { return this->emissiveCoeficient; }
	inline void SetEmissiveCoeficient(const Vector3D& emissiveCoeficientToSet) {
		this -> emissiveCoeficient = emissiveCoeficientToSet;
	}
	inline float GetSpecularExponent() const { return this->specularExponent; }
	inline void SetSpecularExponent(const float& specularExponentToSet) {
		this -> specularExponent = specularExponentToSet;
	}
	inline float GetDissolved() const { return this->dissolved; }
	inline void SetDissolved(const float& dissolvedToSet) {
		this->dissolved =
			dissolvedToSet;
	}
	inline Color GetTransmissionFilterColor() const {
		return this -> transmissionFilterColor;
	}
	inline void SetTransmissionFilterColor(const Color& transmissionFilterColorToSet)
	{
		this->transmissionFilterColor = transmissionFilterColorToSet;
	}
	inline float GetIndexOfRefraction() const { return this->indexOfRefraction; }
	inline void SetIndexOfRefraction(const float& indexOfRefractionToSet) {
		this -> indexOfRefraction = indexOfRefractionToSet;
	}
	inline int GetIlluminationModel() const { return this->illuminationModel; }
	inline void SetIlluminationModel(const int& illuminationModelToSet) {
		this -> illuminationModel = illuminationModelToSet;
	}
	void ParseLine(string line);

};


#pragma once
#include <map>
#include "ModelLoader.h"
#include "Material.h"
#include "Util.h"
using namespace Util;
#include "MaterialTriangle.h"
#include "MaterialModel.h"
class MaterialModelLoader : public ModelLoader
{
private:
	MaterialModel* materialModel;
	string currentMaterial;
	map<string, Material> materials;
	string modelsFolder;
	void loadMaterials(string fileName);
	MaterialTriangle parseObjMaterialTriangle(const string& line);
	MaterialTriangle center(MaterialTriangle triangle);
public:
	MaterialModelLoader(string modelsFolderArgument = " ", float scaleArgument = 1) :ModelLoader(){
		this->SetEscala(scaleArgument);
		this->modelsFolder = modelsFolderArgument;
	}
	void LoadModel(const string& filePath);
	inline string GetModelsFolder() const { return this->modelsFolder; }
	inline void SetModelsFolder(const string& modelsFolderToSet) {this->modelsFolder =modelsFolderToSet;}
	inline MaterialModel* GetMaterialModel() { return this->materialModel; }
	void Clear();
};


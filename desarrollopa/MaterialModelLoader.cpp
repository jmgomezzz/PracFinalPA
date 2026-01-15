#include "MaterialModelLoader.h"
void MaterialModelLoader::loadMaterials(string fileName)
{
	string materialName;
	string line;
	string fullFileName = this->GetModelsFolder() + fileName;
	ifstream materialFile(fullFileName);
	if (materialFile.is_open())
	{
		while (getline(materialFile, line)) {
			line = trim(line);
			if (line[0] == '#' || line.size() == 0)
				continue;
			if (line.find("newmtl") != string::npos) {
				vector<string> lineInfo = split(line, ' ');
				materialName = lineInfo[1];
				this->materials[materialName] = Material(this->GetModelsFolder());
			}
			else {
				this->materials[materialName].ParseLine(line);
			}
		}
		materialFile.close();
	}
	else
	{
		throw runtime_error("Error openning file: " + fullFileName + " in MaterialModelLoader::loadMaterials()");
	}
}
void MaterialModelLoader::LoadModel(const string& filePath)
{
	if (materialModel == nullptr)
	{
		materialModel = new MaterialModel(); // Crear un nuevo MaterialModel si no existe
	}
	else {
		materialModel->Clear(); // Limpiar el modelo existente
	}
	try
	{
		ifstream objFile(filePath);
		if (objFile.is_open())
		{
			string line;
			int count = 0;
			while (getline(objFile, line))
			{
				//Si la línea comienza por mtllib, es la definición del archivo de materiales que se usa
				if (line.find("mtllib") != string::npos) {
					vector<string> lineInfo = split(line, ' ');
					this->loadMaterials(lineInfo[1]);
				}
				else if (line.find("usemtl") != string::npos) {
					vector<string> lineInfo = split(line, ' ');
					this->currentMaterial = lineInfo[1];
				}
				else if (line[0] == 'v' && line[1] == 'n') //ejemplo: vn 0.00000.3603 - 0.9328 = > normal
				{
					Vector3D normal = this->parseObjLineToVector3D(line);
					this->normalesArchivo.push_back(normal);
				}
				else if (line[0] == 'v') //ejemplo: v -0.091741 0.641907 0.606832= > vértice
				{
					Vector3D vertex = this->parseObjLineToVector3D(line);
					this->CalcBoundaries(vertex);
					this->verticesArchivo.push_back(vertex);
				}
				else if (line[0] == 'f') //ejemplo: f 2//4 5//4 6//4 => cara,triángulo
				{
					MaterialTriangle triangle = this->parseObjMaterialTriangle(line);
					triangle.SetMaterial(this->materials[this->currentMaterial]);
					materialModel->AddMaterialTriangle(this->center(triangle));
				}
			}
			objFile.close();
		}
		else
		{
			cout << "No se ha podido abrir el archivo: " << filePath << endl;
		}
	}
	catch (exception& ex)
	{
		cout << "Excepción al procesar el archivo: " << filePath << endl;
		cout << ex.what() << endl;
	}
}
MaterialTriangle MaterialModelLoader::parseObjMaterialTriangle(const string& line)
{
	Triangle triangle = this->parseObjTriangle(line);
	MaterialTriangle materialTriangle(triangle);
	return materialTriangle;
}
MaterialTriangle MaterialModelLoader::center(MaterialTriangle triangle)
{
	Vector3D modelCenter(this->minX + this->GetWidth() / 2.0, this->minY + this->GetHeight() / 2.0, this->minZ + this->GetLength() / 2);
	MaterialTriangle centeredTriangle(
		triangle.GetPosicion1() - modelCenter,
		triangle.GetPosicion2() - modelCenter,
		triangle.GetPosicion3() - modelCenter,
		triangle.GetNormal1(),
		triangle.GetNormal2(),
		triangle.GetNormal3());
	centeredTriangle.SetMaterial(triangle.GetMaterial());
	return centeredTriangle;
}
void MaterialModelLoader::Clear()
{
	this->verticesArchivo.clear();
	this->normalesArchivo.clear();
	this->maxX = 0;
	this->maxY = 0;
	this->maxZ = 0;
	this->minX = 0;
	this->minY = 0;
	this->minZ = 0;
	materialModel->Clear();
}

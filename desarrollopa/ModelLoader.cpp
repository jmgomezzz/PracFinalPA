#include "ModelLoader.h"

void ModelLoader::Clear() {
	verticesArchivo.clear();
	normalesArchivo.clear();
	this->modelo.Clear();
	maxX = maxY = maxZ = -99999;
	minX = minY = minZ = 99999;
}

void ModelLoader::CalcBoundaries(Vector3D vectorPoint) {
	this->maxX = fmax(this->maxX, vectorPoint.GetX());
	this->maxY = fmax(this->maxY, vectorPoint.GetY());
	this->maxZ = fmax(this->maxZ, vectorPoint.GetZ());
	this->minX = fmin(this->minX, vectorPoint.GetX());
	this->minY = fmin(this->minY, vectorPoint.GetY());
	this->minZ = fmin(this->minZ, vectorPoint.GetZ());
}
Triangle ModelLoader::Center(Triangle triangle) {
	Vector3D modelCenter(this->minX + this->GetWidth() / 2.0, this->minY + this->GetHeight() / 2.0, this->minZ + this->GetLength() / 2);
	Triangle centeredTriangle(triangle.GetPosicion1() - modelCenter, triangle.GetPosicion2() - modelCenter, triangle.GetPosicion3() - modelCenter, triangle.GetNormal1(), triangle.GetNormal2(), triangle.GetNormal3());
	return centeredTriangle;
}
Vector3D ModelLoader::parseObjLineToVector3D(const string& line) {
	string typeOfPoint;
	float xCoord, yCoord, zCoord;
	istringstream stringStream(line);
	stringStream >> typeOfPoint >> xCoord >> yCoord >> zCoord;
	Vector3D vectorPoint(xCoord, yCoord, zCoord);
	return vectorPoint * this->GetEscala();
}
Triangle ModelLoader::parseObjTriangle(const string& line) {
	char c;
	int idxVertex0, idxVertex1, idxVertex2;
	int idxNormal0, idxNormal1, idxNormal2;

	istringstream stringStream(line);
	stringStream >> c;
	stringStream >> idxVertex0 >> c >> c >> idxNormal0;
	stringStream >> idxVertex1 >> c >> c >> idxNormal1;
	stringStream >> idxVertex2 >> c >> c >> idxNormal2;

	Vector3D vertex0 = this->verticesArchivo[idxVertex0 - 1];
	Vector3D vertex1 = this->verticesArchivo[idxVertex1 - 1];
	Vector3D vertex2 = this->verticesArchivo[idxVertex2 - 1];
	Vector3D normal0 = this->normalesArchivo[idxNormal0 - 1];
	Vector3D normal1 = this->normalesArchivo[idxNormal1 - 1];
	Vector3D normal2 = this->normalesArchivo[idxNormal2 - 1];
	Triangle parsedTriangle(vertex0, vertex1, vertex2, normal0, normal1, normal2);

	return parsedTriangle;
}
void ModelLoader::LoadModel(const string& filePath) {
	Clear();
	try {
		ifstream objFile(filePath);
		if (objFile.is_open()) {
			string line;
			int count = 0; 
			while (getline(objFile, line)) {
				if (line[0] == 'v' && line[1] == 'n') {
					Vector3D normal = this->parseObjLineToVector3D(line);
					this->normalesArchivo.push_back(normal);
				}
				else if (line[0] == 'v') {
					Vector3D vertex = this->parseObjLineToVector3D(line);
					this->CalcBoundaries(vertex);
					this->verticesArchivo.push_back(vertex);
				}
				else if (line[0] == 'f') {
					Triangle triangle = this->parseObjTriangle(line);
					this->modelo.AddTriangle(this->Center(triangle));
				}
			}
			objFile.close();
		}
		else {
			cout << "No se ha podido abrir el archivo: " << filePath << endl;
		}
	}
	catch (exception& ex) {
		cout << "Excepcion al procesar el archivo: " << filePath << endl;
		cout << ex.what() << endl;
	}
}
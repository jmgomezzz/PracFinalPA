#pragma once
#include "Triangle.h"
#include "Material.h"
#include <GL/glut.h>
class MaterialTriangle : public Triangle
{
private:
	Material material;
	void useMaterial();
public:
		MaterialTriangle(
		Vector3D vertex0Argument = Vector3D(),
		Vector3D vertex1Argument = Vector3D(),
		Vector3D vertex2Argument = Vector3D(),
		Vector3D normal0Argument = Vector3D(),
		Vector3D normal1Argument = Vector3D(),
		Vector3D normal2Argument = Vector3D(),
		Color color0Argument = Color(1, 0, 0),
		Color color1Argument = Color(0, 1, 0),
		Color color2Argument = Color(0, 0, 1)) : Triangle(vertex0Argument,vertex1Argument, vertex2Argument,normal0Argument, normal1Argument, normal2Argument, color0Argument,color1Argument, color2Argument){}
		MaterialTriangle(Triangle triangle): MaterialTriangle(
			triangle.GetPosicion1(),
			triangle.GetPosicion2(),
			triangle.GetPosicion3(),
			triangle.GetNormal1(),
			triangle.GetNormal2(),
			triangle.GetNormal3())
	{}
	inline Material GetMaterial() const { return this->material;}
	inline void SetMaterial(const Material& materialToSet) {this->material =materialToSet;}
	void Render();
};

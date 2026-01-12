#include "Material.h"
void Material::ParseLine(string line)
{
	vector<string> lineInfo = split(line, ' ');
	float red = stof(lineInfo[1]);
	if (lineInfo[0] == "Ns") this->SetSpecularExponent(stof(lineInfo[1]));
	else if (lineInfo[0] == "Ka") this->SetAmbientColor(Color(stof(lineInfo[1]),
		stof(lineInfo[2]), stof(lineInfo[3])));
	else if (lineInfo[0] == "Kd") this->SetDiffuseColor(Color(stof(lineInfo[1]),
		stof(lineInfo[2]), stof(lineInfo[3])));
	else if (lineInfo[0] == "Ks") this->SetSpecularColor(Color(stof(lineInfo[1]),
		stof(lineInfo[2]), stof(lineInfo[3])));
	else if (lineInfo[0] == "Ke") this->SetEmissiveCoeficient(Vector3D(stof(lineInfo[1]),
		stof(lineInfo[2]), stof(lineInfo[3])));
	else if (lineInfo[0] == "Ni") this->SetIndexOfRefraction(stof(lineInfo[1]));
	else if (lineInfo[0] == "d") this->SetDissolved(stof(lineInfo[1]));
	else if (lineInfo[0] == "Tf") this->SetTransmissionFilterColor(Color(stof(lineInfo[1]), stof(lineInfo[2]), stof(lineInfo[3])));
}
#pragma once
#include "Solid.h"
#include <string>
using namespace std;
class Text:public Solid
{
private:
	string texto;

public:
	Text():Solid() {
		this->texto = "";
	}
	void Render();
};


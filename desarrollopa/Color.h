#pragma once
class Color
{
private:
	float R;
	float G;
	float B;
public:
	Color() :R(0.0), G(0.0), B(0.0) {

	}
	Color(float red, float green, float blue) {
		this->R = red;
		this->G = green;
		this->B = blue;
	}
	inline float GetR() { return this->R; }
	inline float GetG() { return this->G; }
	inline float GetB() { return this->B; }

	inline void SetRedComponent(float RToSet)
	{
		// Solo asigna redComponent si redToSet está en el rango [0.0, 1.0]
		this->R = (RToSet >= 0.0 && RToSet <= 1.0) ? RToSet : this->R;
	}


	inline void SetGreenComponent(float GToSet)
	{
		if (GToSet >= 0.0 && GToSet <= 1.0)
		{
			this->G = GToSet;
		}
	}

	inline void SetBlueComponent(float BToSet)
	{
		if (BToSet >= 0.0 && BToSet <= 1.0)
		{
			this->B = BToSet;
		}
	}
};


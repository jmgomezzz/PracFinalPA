#include "Solid.h"

void Solid::Update(const float& time, const Vector3D& gravity) {

    this->SetCoordinates(this->GetCoord() + this->GetSpeed() * time);
    this->SetRot(this->GetRot().GetRotacion() + this->GetOrientationSpeed() * time);
    if (this->GetAffectedG()) {
        this->SetSpeed(this->GetSpeed() + gravity * time);
    }
}
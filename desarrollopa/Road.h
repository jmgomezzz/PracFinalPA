#pragma once
#include "Model.h"
#include "Solid.h"
#include <vector>

class Road : public Solid
{
private:
    struct RoadSegment {
        Vector3D pos;
        float width;
        Color asphaltColor;
        Color lineColor;
    };

    std::vector<RoadSegment> segments;
    int numSegments;
    float segmentLength;
    float roadWidth;
    float speed;
    float totalLength;

    void CreateRoadGeometry();
    void RenderSegment(const RoadSegment& segment);

public:
    Road(int numSegs = 20, float segLength = 5.0f, float width = 8.0f, float s = 10.0f) : Solid() {
        this->numSegments = numSegs;
        this->segmentLength = segLength;
        this->roadWidth = width;
        this->speed = s;
        this->totalLength = numSegments * segLength;
        CreateRoadGeometry();
    }

    inline int GetNumSegments() { return this->numSegments; }
    inline float GetSegmentLength() { return this->segmentLength; }
    inline float GetRoadWidth() { return this->roadWidth; }
    inline float GetSpeed() { return this->speed; }

    void SetNumSegments(int numToSet) { this->numSegments = numToSet; }
    void SetSegmentLength(float lengthToSet) { this->segmentLength = lengthToSet; }
    void SetRoadWidth(float widthToSet) { this->roadWidth = widthToSet; }
    void SetSpeed(float speedToSet) { this->speed = speedToSet; }

    void Update(const float& time, const Vector3D& gravity) override;
    void Render() override;
    Solid* Clone() override;
};
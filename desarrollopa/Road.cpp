#include "Road.h"
#include <GL/glut.h>

void Road::CreateRoadGeometry() {
    segments.clear();

    // Colores de la carretera
    Color asphalt(0.2f, 0.2f, 0.25f);
    Color whiteLine(0.9f, 0.9f, 0.9f);

    // Crear segmentos de carretera desde atrás hacia adelante
    for (int i = 0; i < numSegments; i++) {
        RoadSegment seg;
        seg.pos = Vector3D(0.0f, -0.5f, -i * segmentLength);
        seg.width = roadWidth;
        seg.asphaltColor = asphalt;
        seg.lineColor = whiteLine;
        segments.push_back(seg);
    }
}

void Road::RenderSegment(const RoadSegment& segment) {
    float halfWidth = segment.width / 2.0f;
    float z = segment.pos.GetZ();
    float y = segment.pos.GetY();
    float nextZ = z + segmentLength;

    // Renderizar el asfalto (superficie principal)
    glColor3f(segment.asphaltColor.GetR(),
        segment.asphaltColor.GetG(),
        segment.asphaltColor.GetB());

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-halfWidth, y, z);
    glVertex3f(halfWidth, y, z);
    glVertex3f(halfWidth, y, nextZ);
    glVertex3f(-halfWidth, y, nextZ);
    glEnd();

    // Líneas laterales blancas
    float lineWidth = 0.3f;
    glColor3f(segment.lineColor.GetR(),
        segment.lineColor.GetG(),
        segment.lineColor.GetB());

    // Línea izquierda
    glBegin(GL_QUADS);
    glVertex3f(-halfWidth + 0.2f, y + 0.01f, z);
    glVertex3f(-halfWidth + 0.2f + lineWidth, y + 0.01f, z);
    glVertex3f(-halfWidth + 0.2f + lineWidth, y + 0.01f, nextZ);
    glVertex3f(-halfWidth + 0.2f, y + 0.01f, nextZ);
    glEnd();

    // Línea derecha
    glBegin(GL_QUADS);
    glVertex3f(halfWidth - 0.2f - lineWidth, y + 0.01f, z);
    glVertex3f(halfWidth - 0.2f, y + 0.01f, z);
    glVertex3f(halfWidth - 0.2f, y + 0.01f, nextZ);
    glVertex3f(halfWidth - 0.2f - lineWidth, y + 0.01f, nextZ);
    glEnd();

    // Línea central discontinua (solo cada 2 segmentos)
    int segIndex = static_cast<int>(-z / segmentLength);
    if (segIndex % 2 == 0) {
        float centerLineWidth = 0.15f;
        glBegin(GL_QUADS);
        glVertex3f(-centerLineWidth, y + 0.01f, z);
        glVertex3f(centerLineWidth, y + 0.01f, z);
        glVertex3f(centerLineWidth, y + 0.01f, nextZ);
        glVertex3f(-centerLineWidth, y + 0.01f, nextZ);
        glEnd();
    }
}

void Road::Update(const float& time, const Vector3D& gravity) {
    // Mover todos los segmentos hacia adelante (hacia la cámara)
    for (auto& seg : segments) {
        seg.pos.SetZ(seg.pos.GetZ() + (this->speed * time));

        // Si el segmento sale por delante de la cámara, reposicionarlo al final
        if (seg.pos.GetZ() > segmentLength) {
            seg.pos.SetZ(seg.pos.GetZ() - totalLength);
        }
    }
}

void Road::Render() {
    glPushMatrix();

    // Renderizar todos los segmentos
    for (const auto& seg : segments) {
        RenderSegment(seg);
    }

    glPopMatrix();
}

Solid* Road::Clone() {
    Road* newRoad = new Road(this->numSegments, this->segmentLength,
        this->roadWidth, this->speed);
    return newRoad;
}
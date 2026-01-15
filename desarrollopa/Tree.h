#pragma once
#include "Model.h"
#include "ModelLoader.h" // <--- Importante: Incluimos el cargador aquí

// Heredamos de Model (no de MaterialCar)
class Tree : public Model {
public:
    // Constructor
    Tree() : Model() {}

    // --- NUEVA FUNCIÓN DE CARGA ---
    // Esta función usa el ModelLoader para leer el archivo y copiarse los datos a sí mismo
    bool Load(string path, float scale = 1.0f) {
        ModelLoader loader;
        loader.SetEscala(scale); // Configuramos la escala en el loader
        loader.LoadModel(path);  // Cargamos el archivo

        // Aquí está el truco:
        // El loader tiene el modelo cargado. Se lo copiamos a "este" objeto (this).
        // Al hacer esto, copiamos todos los triángulos del loader al árbol.
        Model modeloCargado = loader.GetModel();

        // Llamamos al operador de asignación de la clase base (Model)
        Model::operator=(modeloCargado);

        return true;
    }

    // --- FUNCIONES OBLIGATORIAS ---
    void Update(const float& time, const Vector3D& gravity) override {
        // Los árboles son estáticos
    }

    // En Tree.h

    void Render() override {
        glPushMatrix();

        // 1. Intentamos dibujar el modelo cargado (.obj)
        // Si se cargó bien, se dibujará aquí.
        Model::Render();

        // 2. "ÁRBOL DE RESPALDO" (DEBUG)
        // Dibujamos un árbol simple con código para asegurar que se vean
        // aunque falle el archivo .obj
        glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT); // Guardar estado iluminación/color
        glDisable(GL_LIGHTING); // Desactivar luces para que se vea un color plano y brillante
        glDisable(GL_TEXTURE_2D);

        // Tronco (Marrón)
        glColor3f(0.6f, 0.4f, 0.2f);
        glPushMatrix();
        glRotatef(-90, 1, 0, 0); // Rotar para que apunte arriba
        glutSolidCone(0.5, 2.0, 8, 8); // Radio 0.5, Altura 2
        glPopMatrix();

        // Hojas (Verde)
        glColor3f(0.0f, 0.8f, 0.0f);
        glPushMatrix();
        glTranslatef(0.0f, 1.5f, 0.0f); // Subir la copa
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(1.5, 3.5, 8, 8); // Radio 1.5, Altura 3.5
        glPopMatrix();

        glPopAttrib(); // Restaurar iluminación original
        glPopMatrix();
    }
    Solid* Clone() override {
        return new Tree(*this);
    }
};
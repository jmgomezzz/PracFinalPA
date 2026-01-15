#pragma once
#include <windows.h> // Necesario para leer BMP en Windows
#include <GL/glut.h>
#include <iostream>
#include <vector>

class TextureLoader {
public:
    // Función estática para cargar un BMP y devolver el ID de textura de OpenGL
    static GLuint LoadBMP(const char* imagepath) {
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int width, height;
        unsigned int imageSize;
        unsigned char* data;

        FILE* file;
        fopen_s(&file, imagepath, "rb");
        if (!file) {
            std::cout << "No se pudo abrir la imagen: " << imagepath << std::endl;
            return 0;
        }

        if (fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M') {
            std::cout << "No es un archivo BMP valido: " << imagepath << std::endl;
            fclose(file);
            return 0;
        }

        dataPos = *(int*)&(header[0x0A]);
        imageSize = *(int*)&(header[0x22]);
        width = *(int*)&(header[0x12]);
        height = *(int*)&(header[0x16]);

        if (imageSize == 0) imageSize = width * height * 3;
        if (dataPos == 0) dataPos = 54;

        data = new unsigned char[imageSize];
        fread(data, 1, imageSize, file);
        fclose(file);

        // Crear textura OpenGL
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

        // Filtros para que se vea bien
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        delete[] data;
        return textureID;
    }
};
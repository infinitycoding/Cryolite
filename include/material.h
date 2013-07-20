#ifndef MATERIAL_H
#define MATERIAL_H


#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <cstring>
#include <cstdio>


#define MAX_STRING_LENGTH 40



class Material
{
    public:
        Material();
        Material(const char *filename, const char *matname);
        ~Material();

        void initMaterial();

        bool loadMaterial(const char *filename, const char *matname);

        static GLuint loadTexture(const char *filename);



        char name[MAX_STRING_LENGTH];

        SDL_Color ambiantMatColor;
        SDL_Color diffuseMatColor;
        SDL_Color specularMatColor;
        SDL_Color emissiveMatColor;
        SDL_Color transparancyMatColor;

        GLuint ambiantTexture;
        GLuint diffuseTexture;
        GLuint specularTexture;
        GLuint alphaTexture;
        GLuint bumpMap;

        GLfloat transparancy;
        GLfloat sharpness;
        GLfloat opticalDensity;
        GLfloat specularExponent;

        int illuminationMode;


    protected:
        int extractIntFromLine(const char *line);
        float extractFloatFromLine(const char *line);
        SDL_Color extractColorFromLine(const char *line);
        char *extractStringFromLine(const char *line, char *string);
};

#endif

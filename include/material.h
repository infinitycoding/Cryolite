#ifndef MATERIAL_H
#define MATERIAL_H



#include <cstdio>
#include <cstdlib>

#include <texture.h>


#define MAX_STRING_LENGTH 40



class Material
{
    public:
        Material();
        Material(const char *filename, const char *matname);
        ~Material();

        void initMaterial();

        bool loadMaterial(const char *filename, const char *matname);



        char name[MAX_STRING_LENGTH];

        SDL_Color ambiantMatColor;
        SDL_Color diffuseMatColor;
        SDL_Color specularMatColor;
        SDL_Color emissiveMatColor;
        SDL_Color transparancyMatColor;

        static TextureCache *TexCache;

        Texture *ambiantTexture;
        Texture *diffuseTexture;
        Texture *specularTexture;
        Texture *alphaTexture;
        Texture *bumpMap;

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


class MaterialCache
{
    public:
        MaterialCache();
        ~MaterialCache();

        Material *requestMaterial(const char *filename, const char *matname);
        Material *searchMaterial(const char *matname);
        bool unloadMaterial(const char *matname);


    protected:
        List<Material> *cachedMaterials;
};

#endif

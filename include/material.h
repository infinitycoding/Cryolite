#ifndef MATERIAL_H
#define MATERIAL_H



#include <cstdio>
#include <cstdlib>

#include <parser.h>
#include <texture.h>


#define MAX_STRING_LENGTH 40



class Material : public BasicParser
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

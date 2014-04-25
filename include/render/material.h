#ifndef MATERIAL_H
#define MATERIAL_H



#include <parser.h>
#include <texture.h>


#define MAX_STRING_LENGTH 100

#define STD_AMBIANT_MAT_COLOR {0.2, 0.2, 0.2, 1.0}
#define STD_DIFFUSE_MAT_COLOR {0.8, 0.8, 0.8, 1.0}
#define STD_SPECULAR_MAT_COLOR {0.0, 0.0, 0.0, 1.0}
#define STD_EMISSIVE_MAT_COLOR {0.0, 0.0, 0.0, 1.0}



class Material : public ExtParser
{
    public:
        Material();
        Material(const char *filename, const char *matname);
        ~Material();

        void initMaterial();

        bool loadMaterial(const char *filename, const char *matname);


        char name[MAX_STRING_LENGTH];

        float *ambiantMatColor;
        float *diffuseMatColor;
        float *specularMatColor;
        float *emissiveMatColor;

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

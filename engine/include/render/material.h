#ifndef MATERIAL_H
#define MATERIAL_H
/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <util/parser.h>
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

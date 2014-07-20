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

#include <material.h>




using namespace std;


TextureCache *Material::TexCache;



Material::Material()
{
    initMaterial();
}


Material::Material(const char *filename, const char *matname)
{
    initMaterial();

    loadMaterial(filename, matname);
}


Material::~Material()
{
    delete[] ambiantMatColor;
    delete[] diffuseMatColor;
    delete[] specularMatColor;
    delete[] emissiveMatColor;
}


void Material::initMaterial()
{
    memset(name, '\0', sizeof(name));

    ambiantMatColor = new float[4] STD_AMBIANT_MAT_COLOR;
    diffuseMatColor = new float[4] STD_DIFFUSE_MAT_COLOR;
    specularMatColor = new float[4] STD_SPECULAR_MAT_COLOR;
    emissiveMatColor = new float[4] STD_EMISSIVE_MAT_COLOR;

    ambiantTexture = NULL;
    diffuseTexture = NULL;
    specularTexture = NULL;
    alphaTexture = NULL;
    bumpMap = NULL;

    transparancy = 0.0;
    sharpness = 0.0;
    opticalDensity = 0.0;
    specularExponent = 0.0;

    illuminationMode = 0;

    if(TexCache == NULL)
        TexCache = new TextureCache();
}


bool Material::loadMaterial(const char *filename, const char *matname)
{
    FILE *f;

    char line[MAX_STRING_LENGTH];
    char string[MAX_STRING_LENGTH];

    memset(line, '\0', sizeof(line));
    memset(string, '\0', sizeof(string));

    strncpy(name, matname, MAX_STRING_LENGTH);

    f = fopen(filename, "r");

    if(f == NULL)
    {
        cerr << "error: the file " << filename << " could not be loaded." << endl;
        fclose(f);
        return false;
    }

    strncpy(string, "newmtl ", 7);
    strncat(string, name, MAX_STRING_LENGTH);

    while(!feof(f) && strncmp(line, string, strlen(string)))
        if(fgets(line, MAX_STRING_LENGTH, f) == NULL)
            break;

    if(feof(f))
    {
        cerr << "error: the material " << name << " does not exist in file " << filename << "." << endl;
        fclose(f);
        return false;
    }

    while(!feof(f))
    {
        if(fgets(line, MAX_STRING_LENGTH, f) == NULL)
            break;

        char *line_ptr = line;

        skipUntilCharacters(&line_ptr, breakChars);
        skipCharacters(&line_ptr, placeholders);

        if(!strncmp(line, "Ka", 2))    // ambiant color
        {
            getGLColor(&line_ptr,ambiantMatColor);
        }
        else if(!strncmp(line, "Kd", 2))   // diffuse color
        {
            getGLColor(&line_ptr,diffuseMatColor);
        }
        else if(!strncmp(line, "Ks", 2))   // specular color
        {
            getGLColor(&line_ptr,specularMatColor);
        }
        else if(!strncmp(line, "Ke", 2))     // emissive color
        {
            getGLColor(&line_ptr,emissiveMatColor);
        }
        else if(!strncmp(line, "map_Ka", 6))     // ambiant texture
        {
            ambiantTexture = TexCache->requestTexture(getString(&line_ptr, string, breakChars));
        }
        else if(!strncmp(line, "map_Kd", 6))     // diffuse texture
        {
            diffuseTexture = TexCache->requestTexture(getString(&line_ptr, string, breakChars));
        }
        else if(!strncmp(line, "map_Ks", 6))     // specular texture
        {
            specularTexture = TexCache->requestTexture(getString(&line_ptr, string, breakChars));
        }
        else if(!strncmp(line, "map_d", 5))     // alpha texture
        {
            alphaTexture = TexCache->requestTexture(getString(&line_ptr, string, breakChars));
        }
        else if(!strncmp(line, "map_bump", 8) || !strncmp(line, "bump", 4))     // bump map
        {
            bumpMap = TexCache->requestTexture(getString(&line_ptr, string, breakChars));
        }
        else if(!strncmp(line, "d", 1) || !strncmp(line, "Tr", 2))     // transparancy
        {
            transparancy = getFloat(&line_ptr, breakChars);
        }
        else if(!strncmp(line, "sharpness", 9))     // sharpness
        {
            sharpness = getFloat(&line_ptr, breakChars);
        }
        else if(!strncmp(line, "Ni", 2))     // optical density
        {
            opticalDensity = getFloat(&line_ptr, breakChars);
        }
        else if(!strncmp(line, "Ns", 2))     // specular exponent
        {
            specularExponent = getFloat(&line_ptr, breakChars);
        }
        else if(!strncmp(line, "illum", 5))     // illumination mode
        {
            illuminationMode = getInt(&line_ptr, breakChars);
        }
        else if(!strncmp(line, "newmtl", 6))
        {
            break;
        }
    }

    fclose(f);

    return true;
}


MaterialCache::MaterialCache()
{
    cachedMaterials = new List<Material>;
}


MaterialCache::~MaterialCache()
{
    delete cachedMaterials;
}


Material *MaterialCache::requestMaterial(const char *filename, const char *matname)
{
    Material *requestedMaterial = searchMaterial(matname);

    if(requestedMaterial == NULL)
    {
        requestedMaterial = new Material(filename, matname);
        cachedMaterials->PushFront(requestedMaterial);
    }

    return requestedMaterial;
}


Material *MaterialCache::searchMaterial(const char *matname)
{
    Material *result = NULL;

    ListIterator<Material> i = ListIterator<Material>(cachedMaterials);
    i.SetFirst();

    while(!(i.IsLast()))
    {
        result = i.GetCurrent();

        if(!strncmp(result->name, matname, MAX_STRING_LENGTH))
            break;
        else
            result = NULL;

        i.Next();
    }

    return result;
}


bool MaterialCache::unloadMaterial(const char *matname)
{
    Material *matToDelete = NULL;

    ListIterator<Material> i = ListIterator<Material>(cachedMaterials);
    i.SetFirst();

    while(!(i.IsLast()))
    {
        matToDelete = i.GetCurrent();

        if(!strncmp(matToDelete->name, matname, MAX_STRING_LENGTH))
        {
            i.Remove();
            return true;
        }

        i.Next();
    }

    return false;
}


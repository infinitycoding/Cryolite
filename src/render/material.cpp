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

}


void Material::initMaterial()
{
    memset(name, '\0', sizeof(name));

    memset(&ambiantMatColor, 0.0, sizeof(ambiantMatColor));
    memset(&diffuseMatColor, 0.0, sizeof(diffuseMatColor));
    memset(&specularMatColor, 0.0, sizeof(specularMatColor));
    memset(&emissiveMatColor, 0.0, sizeof(emissiveMatColor));
    memset(&transparancyMatColor, 0.0, sizeof(transparancyMatColor));

    ambiantTexture = 0;
    diffuseTexture = 0;
    specularTexture = 0;
    alphaTexture = 0;
    bumpMap = 0;

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

        if(!strncmp(line, "Ka", 2))    // ambiant color
        {
            ambiantMatColor = getValueColor(line);
        }
        else if(!strncmp(line, "Kd", 2))   // diffuse color
        {
            diffuseMatColor = getValueColor(line);
        }
        else if(!strncmp(line, "Ks", 2))   // specular color
        {
            specularMatColor = getValueColor(line);
        }
        else if(!strncmp(line, "Ke", 2))     // emissive color
        {
            emissiveMatColor = getValueColor(line);
        }
        else if(!strncmp(line, "Tf", 2))     // transparancy color
        {
            transparancyMatColor = getValueColor(line);
        }
        else if(!strncmp(line, "map_Ka", 6))     // ambiant texture
        {
            ambiantTexture = TexCache->requestTexture(getValueString(line, string));
        }
        else if(!strncmp(line, "map_Kd", 6))     // diffuse texture
        {
            diffuseTexture = TexCache->requestTexture(getValueString(line, string));
        }
        else if(!strncmp(line, "map_Ks", 6))     // specular texture
        {
            specularTexture = TexCache->requestTexture(getValueString(line, string));
        }
        else if(!strncmp(line, "map_d", 5))     // alpha texture
        {
            alphaTexture = TexCache->requestTexture(getValueString(line, string));
        }
        else if(!strncmp(line, "map_bump", 8) || !strncmp(line, "bump", 4))     // bump map
        {
            bumpMap = TexCache->requestTexture(getValueString(line, string));
        }
        else if(!strncmp(line, "d", 1) || !strncmp(line, "Tr", 2))     // transparancy
        {
            transparancy = getValueFloat(line);
        }
        else if(!strncmp(line, "sharpness", 9))     // sharpness
        {
            sharpness = getValueFloat(line);
        }
        else if(!strncmp(line, "Ni", 2))     // optical density
        {
            opticalDensity = getValueFloat(line);
        }
        else if(!strncmp(line, "Ns", 2))     // specular exponent
        {
            specularExponent = getValueFloat(line);
        }
        else if(!strncmp(line, "illum", 5))     // illumination mode
        {
            illuminationMode = getValueInt(line);
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
        cachedMaterials->ListPushFront(requestedMaterial);
    }

    return requestedMaterial;
}


Material *MaterialCache::searchMaterial(const char *matname)
{
    Material *result = NULL;

    cachedMaterials->ListSetFirst();

    while(!(cachedMaterials->ListIsLast()))
    {
        result = cachedMaterials->ListGetCurrent();

        if(!strncmp(result->name, matname, MAX_STRING_LENGTH))
            break;
        else
            result = NULL;

        cachedMaterials->ListNext();
    }

    return result;
}


bool MaterialCache::unloadMaterial(const char *matname)
{
    Material *matToDelete = NULL;

    cachedMaterials->ListSetFirst();

    while(!(cachedMaterials->ListIsLast()))
    {
        matToDelete = cachedMaterials->ListGetCurrent();

        if(!strncmp(matToDelete->name, matname, MAX_STRING_LENGTH))
        {
            cachedMaterials->ListRemove();
            return true;
        }

        cachedMaterials->ListNext();
    }

    return false;
}


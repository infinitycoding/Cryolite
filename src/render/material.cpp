#include <material.h>


using namespace std;



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
            ambiantMatColor = extractColorFromLine(line);
        }
        else if(!strncmp(line, "Kd", 2))   // diffuse color
        {
            diffuseMatColor = extractColorFromLine(line);
        }
        else if(!strncmp(line, "Ks", 2))   // specular color
        {
            specularMatColor = extractColorFromLine(line);
        }
        else if(!strncmp(line, "Ke", 2))     // emissive color
        {
            emissiveMatColor = extractColorFromLine(line);
        }
        else if(!strncmp(line, "Tf", 2))     // transparancy color
        {
            transparancyMatColor = extractColorFromLine(line);
        }
        else if(!strncmp(line, "map_Ka", 6))     // ambiant texture
        {
            ambiantTexture = new Texture(extractStringFromLine(line, string));
        }
        else if(!strncmp(line, "map_Kd", 6))     // diffuse texture
        {
            diffuseTexture = new Texture(extractStringFromLine(line, string));
        }
        else if(!strncmp(line, "map_Ks", 6))     // specular texture
        {
            specularTexture = new Texture(extractStringFromLine(line, string));
        }
        else if(!strncmp(line, "map_d", 5))     // alpha texture
        {
            alphaTexture = new Texture(extractStringFromLine(line, string));
        }
        else if(!strncmp(line, "map_bump", 8) || !strncmp(line, "bump", 4))     // bump map
        {
            bumpMap = new Texture(extractStringFromLine(line, string));
        }
        else if(!strncmp(line, "d", 1) || !strncmp(line, "Tr", 2))     // transparancy
        {
            transparancy = extractFloatFromLine(line);
        }
        else if(!strncmp(line, "sharpness", 9))     // sharpness
        {
            sharpness = extractFloatFromLine(line);
        }
        else if(!strncmp(line, "Ni", 2))     // optical density
        {
            opticalDensity = extractFloatFromLine(line);
        }
        else if(!strncmp(line, "Ns", 2))     // specular exponent
        {
            specularExponent = extractFloatFromLine(line);
        }
        else if(!strncmp(line, "illum", 5))     // illumination mode
        {
            illuminationMode = extractIntFromLine(line);
        }
        else if(!strncmp(line, "newmtl", 6))
        {
            break;
        }
    }

    fclose(f);

    return true;
}


int Material::extractIntFromLine(const char *line)
{
    int i, j;
    char string[MAX_STRING_LENGTH];

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_STRING_LENGTH; i++);

    if(line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return 0;
    }

    for(; line[i] == ' ' && i < MAX_STRING_LENGTH; i++);

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return 0;
    }

    for(j = 0; line[i] >= '0' && line[i] <= '9' && i < MAX_STRING_LENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return 0;
    }

    return atoi(string);
}


float Material::extractFloatFromLine(const char *line)
{
    int i, j;
    char string[MAX_STRING_LENGTH];

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_STRING_LENGTH; i++);

    if(line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return 0;
    }

    for(; line[i] == ' ' && i < MAX_STRING_LENGTH; i++);

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return 0;
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') && i < MAX_STRING_LENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return 0;
    }

    return atof(string);
}


SDL_Color Material::extractColorFromLine(const char *line)
{
    int i, j;
    SDL_Color returnValue = {0, 0, 0, 0};
    char string[MAX_STRING_LENGTH];

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_STRING_LENGTH; i++);

    if(line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(; line[i] == ' ' && i < MAX_STRING_LENGTH; i++);

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') && i < MAX_STRING_LENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_STRING_LENGTH || line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    returnValue.r = atof(string);

    for(; line[i] == ' ' && i < MAX_STRING_LENGTH; i++);

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') && i < MAX_STRING_LENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_STRING_LENGTH || line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    returnValue.g = atof(string);

    for(; line[i] == ' ' && i < MAX_STRING_LENGTH; i++);

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    for(j = 0; ((line[i] >= '0' && line[i] <= '9') || line[i] == '.') && i < MAX_STRING_LENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_STRING_LENGTH)
    {
        cerr << "The following line is corrupted. Will return 0." << endl << line;
        return returnValue;
    }

    returnValue.b = atof(string);

    return returnValue;
}


char *Material::extractStringFromLine(const char *line, char *string)
{
    int i, j;

    for(i = 0; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < MAX_STRING_LENGTH; i++);

    if(line[i] != ' ')
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return NULL;
    }

    for(; line[i] == ' ' && i < MAX_STRING_LENGTH; i++);

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return NULL;
    }

    for(j = 0; line[i] != '\n' && line[i] != '\0' && i < MAX_STRING_LENGTH; i++, j++)
        string[j] = line[i];

    string[j] = '\0';

    if(i == MAX_STRING_LENGTH)
    {
        cerr <<  "The following line is corrupted. Will return 0." << endl << line;
        return NULL;
    }

    return string;
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
    Material *matToDelete = searchMaterial(matname);

    if(matToDelete != NULL)
        delete matToDelete;
    else
        return false;

    return true;
}


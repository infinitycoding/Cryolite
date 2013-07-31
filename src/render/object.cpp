#include <object.h>


using namespace std;


MaterialCache *ObjectType::MatCache;
ObjectTypeCache *Object::ObjTypeCache;


ObjectType::ObjectType()
{
    initObjectType();
}

ObjectType::ObjectType(const char *filename, const char *objname)
{
    initObjectType();

    loadObjectTypeFile(filename, objname);
}

ObjectType::~ObjectType()
{
    delete sounds;

    delete vertices;
    delete normvectors;
    delete texvertices;

    delete polygones;

    delete boundBoxes;
    delete boundSpheres;
    delete boundPlanes;
    delete boundCylinders;
    delete boundTriangles;
}

void ObjectType::initObjectType()
{
    memset(objectTypeName, '\0', sizeof(objectTypeName));

    sounds = new List<Sound>;

    vertices = new List<Vertex3D>;
    normvectors = new List<vector>;
    texvertices = new List<Vertex2D>;

    polygones = new List<Polygon>;

    boundBoxes = new List<struct boundBox>;
    boundSpheres = new List<struct boundSphere>;
    boundPlanes = new List<struct boundPlane>;
    boundCylinders = new List<struct boundCylinder>;
    boundTriangles = new List<struct boundTriangel>;

    isPhysicalActor = false;

    if(MatCache == NULL)
        MatCache = new MaterialCache();

    ObjectTypeMaterial = NULL;
}

usedVertices ObjectType::verticesInPolygon(char *line)
{
    usedVertices used = nothingUsed;
    bool firstSlash = true;
    bool resultFound = false;

    for(int i = 2; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && resultFound == false; i++)
    {
        if(line[i] == '/')
        {
            if(firstSlash == true)
            {
                firstSlash = false;

                if(line[++i] == '/')
                {
                    used = normalsUsed;

                    resultFound = true;
                }
                else
                    used = textureUsed;
            }
            else
            {
                used = allUsed;

                resultFound = true;
            }
        }
    }

    return used;
}

struct vertexNumber ObjectType::countVertices(const char *filename, const char *objectname)
{
    FILE *f;
    int i, j;
    char line[50];
    char string[50];
    bool correctObject = false;
    struct vertexNumber vertexCounter = {0, 0, 0};

    f = fopen(filename, "r");

    if(f == NULL)
    {
        printf("the file %s could not be opened.\n", filename);
        exit(-1);
    }

    while(fgets(line, 50, f))
    {
        if(line[0] == 'o')
        {
            for(i = 2, j = 0; line[i] != '\n'; i++, j++)
                string[j] = line[i];

            string[j] = '\0';

            if(!strncmp(string, objectname, strlen(string)))
                correctObject = true;
            else
                break;
        }
        else if(line[0] == 'v' && line[1] == ' ')
        {
            if(correctObject == true)
                vertexCounter.objectVertices++;
        }
        else if(line[0] == 'v' && line[1]== 't')
        {
            if(correctObject == true)
                vertexCounter.textureVertices++;
        }
        else if(line[0] == 'v' && line[1] == 'n')
        {
            if(correctObject == true)
                vertexCounter.normalVectors++;
        }
        else
            continue;
    }

    fclose(f);

    return vertexCounter;
}

void ObjectType::loadObjectTypeFile(const char *objectFile, const char *objectName)
{
    FILE *f;

    char line[50];
    char string[50];
    char matfile[50];

    int h, i , j;
    int vert_id[4], tex_id[4], norm_id[4];

    int vertexNumber = 0;

    bool correctObject = false;
    bool auto_texv_loaded = false;

    usedVertices used = nothingUsed;

    struct vertexNumber otherVertices = {0, 0, 0};
    struct vertexNumber myVertices = {0, 0, 0};
    struct vertexNumber allObjectVertices = countVertices(objectFile, objectName);

    Vertex2D *texvertex_ptr = NULL;
    Vertex2D *autotexvertex_ptrs[4];
    Vertex3D *objvertex_ptr = NULL;
    vector *normvector_ptr = NULL;

    Vertex2D *texvertex_ptrs[allObjectVertices.textureVertices];
    Vertex3D *objvertex_ptrs[allObjectVertices.objectVertices];
    vector *normvector_ptrs[allObjectVertices.normalVectors];

    Polygon *polygon_ptr = NULL;

    strncpy(objectTypeName, objectName, 20);

    if(allObjectVertices.objectVertices == 0)
    {
        cerr << "error: object " << objectName << " in file " << objectFile << " does not exist or has no vertices." << endl;
        return;
    }

    f = fopen(objectFile, "r");

    if(f == NULL)
    {
        cerr << "error: the file " << objectFile << " could not be opened." << endl;
        return;
    }

    do
    {
        fgets(line, 40, f);

        if(!strncmp(line, "mtllib", 6))
        {
            memset(matfile, '\0', sizeof(matfile));
            getValueString(line, matfile);

            continue;
        }

        if(!strncmp(line, "usemtl", 6))
        {
            memset(string, '\0', sizeof(string));
            getValueString(line, string);

            ObjectTypeMaterial = MatCache->requestMaterial(matfile, string);

            continue;
        }

        if(line[0] == 'o')
        {
            memset(string, '\0', sizeof(string));
            if(!strncmp(getValueString(line, string), objectName, strlen(string)))
                correctObject = true;
            else if(correctObject == true)
                break;

            continue;
        }

        if(line[0] == 'v' && line[1] == 't')
        {
            if(correctObject == false)
                otherVertices.textureVertices++;
            else
            {
                Vertex2D tempv2d = getValueVertex2D(line);
                texvertex_ptr = new Vertex2D(&tempv2d);

                texvertices->PushFront(texvertex_ptr);

                texvertex_ptrs[myVertices.textureVertices++] = texvertex_ptr;
            }

            continue;
        }

        if(line[0] == 'v' && line[1] == ' ')
        {
            if(correctObject == false)
                otherVertices.objectVertices++;
            else
            {

                Vertex3D tempv3d = getValueVertex3D(line);
                objvertex_ptr = new Vertex3D(&tempv3d);

                vertices->PushFront(objvertex_ptr);

                objvertex_ptrs[myVertices.objectVertices++] = objvertex_ptr;
            }

	    continue;
        }

	if(line[0] == 'v' && line[1] == 'n')
        {
            if(correctObject == false)
                otherVertices.normalVectors++;
            else
            {
                vector tempvec = getValueVector(line);
                normvector_ptr = new vector(&tempvec);

                normvectors->PushFront(normvector_ptr);

                normvector_ptrs[myVertices.normalVectors++] = normvector_ptr;
            }

            continue;
        }

        if(line[0] == 'f')
        {
            if(correctObject == false)
                continue;
            else
            {
                for(i = 2, vertexNumber = 1; line[i] != '\n' && line[i] != '\0'; i++) // check if it is a triangle or a square
                    if(line[i] == ' ')
                        vertexNumber++;

                used = verticesInPolygon(line);

                polygon_ptr = new Polygon(vertexNumber);

                polygones->PushFront(polygon_ptr);

                i = 1;

                for(h = 0; h < vertexNumber; h++)
                {

                    for(++i, j = 0; line[i] != ' ' && line[i] != '/' && line[i] != '\n' && line[i] != '\0'; i++, j++)
                    {
                        string[j] = line[i];
                    }

                    string[j] = '\0';

                    vert_id[h] = atoi(string);
                    vert_id[h] -= otherVertices.objectVertices+1;

                    if(used == textureUsed || used == allUsed)
                    {

                        for(i++, j = 0; line[i] != ' ' && line[i] != '\n'; i++, j++)
                        {
                            string[j] = line[i];
                        }


                        string[j+1] = '\0';

                        tex_id[h] = atoi(string);
                        tex_id[h] -= otherVertices.textureVertices+1;

                    }

                    if(used == normalsUsed)
                        i++;

                    if(used == normalsUsed || used == allUsed)
                    {
                        for(i++, j = 0; line[i] != ' ' && line[i] != '\n'; i++, j++)
                        {
                            string[j] = line[i];
                        }


                        string[j+1] = '\0';

                        norm_id[h] = atoi(string);
                        norm_id[h] -= otherVertices.normalVectors+1;
                    }

                }

                for(i = 0; i < vertexNumber; i++)
                {

                    polygon_ptr->setObjVertex(i, objvertex_ptrs[vert_id[i]]);

                    if(used == textureUsed || used == allUsed)
                        polygon_ptr->setTexVertex(i, texvertex_ptrs[tex_id[i]]);
                    else if(ObjectTypeMaterial != NULL)
                    {
                        if(auto_texv_loaded == false)
                        {
                            auto_texv_loaded = true;

                            for(j = 0; j < 4; j++)
                                autotexvertex_ptrs[j] = new Vertex2D;

                            autotexvertex_ptrs[0]->set(0, 1);
                            autotexvertex_ptrs[1]->set(0, 0);
                            autotexvertex_ptrs[2]->set(1, 0);
                            autotexvertex_ptrs[3]->set(1, 1);
                        }

                        polygon_ptr->setTexVertex(i, autotexvertex_ptrs[i%5]);
                    }

                    if(used == normalsUsed || used == allUsed)
                        polygon_ptr->setNormVector(i, normvector_ptrs[norm_id[i]]);
                }

                continue;
            }
        }
    }while(!feof(f));

    cout << "object " << objectName << " in file " << objectFile << " successfully loaded." << endl;

    fclose(f);

}


ObjectTypeCache::ObjectTypeCache()
{
    cachedObjectTypes = new List<ObjectType>;
}

ObjectTypeCache::~ObjectTypeCache()
{
    delete cachedObjectTypes;
}

ObjectType *ObjectTypeCache::requestObjectType(const char *filename, const char *objtypename)
{
    ObjectType *requestedObjectType = searchObjectType(objtypename);

    if(requestedObjectType == NULL)
    {
        requestedObjectType = new ObjectType(filename, objtypename);
        cachedObjectTypes->PushFront(requestedObjectType);
    }

    return requestedObjectType;
}

ObjectType *ObjectTypeCache::searchObjectType(const char *objtypename)
{
    ObjectType *result = NULL;

    ListIterator<ObjectType> i = ListIterator<ObjectType>(cachedObjectTypes);
    i.SetFirst();

    while(!(i.IsLast()))
    {
        result = i.GetCurrent();

        if(!strncmp(result->objectTypeName, objtypename, MAX_STRING_LENGTH))
            break;
        else
            result = NULL;

        i.Next();
    }

    return result;
}

bool ObjectTypeCache::unloadObjectType(const char *objtypename)
{
    ObjectType *objTypeToDelete = NULL;

    ListIterator<ObjectType> i = ListIterator<ObjectType>(cachedObjectTypes);
    i.SetFirst();

    while(!(i.IsLast()))
    {
        objTypeToDelete = i.GetCurrent();

        if(!strncmp(objTypeToDelete->objectTypeName, objtypename, MAX_STRING_LENGTH))
        {
            i.Remove();
            return true;
        }

        i.Next();
    }

    return false;
}


Object::Object()
{
    initObject();
}

Object::Object(const char *filename, const char *objname)
{
    initObject();

    objType = ObjTypeCache->requestObjectType(filename, objname);
}

Object::Object(const char *filename, const char *objname, vector pos)
{
    initObject();

    objType = ObjTypeCache->requestObjectType(filename, objname);

    position.setvalue(pos);
}

Object::~Object()
{

}

void Object::initObject()
{
    scale = vector(1, 1, 1);

    position = vector();

    rotationAxis = vector();

    Angle = 0;
    remeaningAngle = 0;
    destAngle = 0;
    rotationVelocity = 0;
    rotationAcceleration = 0;
    startRotationTime = 0;
    remAngleSing = 0;

    Dm = vector();

    V0m = 0; // Velocity Motion
    Am = 0; // Acceleration Motion
    Tms = 0; //Time Motion Start

    if(ObjTypeCache == NULL)
        ObjTypeCache = new ObjectTypeCache();

    objType = NULL;
}

void Object::moveObject(float a ,vector D, float v)
{
    int currentTime = SDL_GetTicks();
    //normize Direction
    D.unify();

    // calculate System V0
    this->V0m = len( (D * v) + ( this->Dm * ( ( (currentTime - this->Tms) / 1000 ) + this->V0m) ) );


    // calculate new acceleration
    /*vector F = unify((D * a) + (this->Dm * this->Am));
    vector Fd = unify(this->Dm);
    int invert;
    if(F.x == Fd.x && F.y == Fd.y && F.z == Fd.z)
        invert = 1;
    else
        invert = -1;*/

    this->Am = len( (D * a) + (this->Dm * this->Am) );

    // generate Direction Vector
    this->Dm = unify(this->Dm+D);

    // save current time
    this->Tms = currentTime;

}

void Object::rotateObject(float angle,float v,float a,vector rotationAxis)
{
    this->startRotationTime = SDL_GetTicks();
    this->remeaningAngle = angle;
    if(angle<0)
        this->remAngleSing = -1;
    else
        this->remAngleSing = 1;
    this->rotationVelocity = v;
    this->rotationAcceleration = a;
    this->rotationAxis = rotationAxis;
    this->destAngle = this->Angle+angle;
}

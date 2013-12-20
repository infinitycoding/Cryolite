#include <object.h>         // makes somehow sense, doesn't it?



using namespace std;      // i want to use the iostream functions



MaterialCache *ObjectType::MatCache;        // this have to be like this to initialize the static variables on startup
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
    delete vertices;    // delete everything
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

    vertices = new List<Vertex3D>;
    normvectors = new List<vector>;
    texvertices = new List<Vertex2D>;

    polygones = new List<Polygon>;

    boundBoxes = new List<boundBox>;
    boundSpheres = new List<boundSphere>;
    boundPlanes = new List<boundPlane>;
    boundCylinders = new List<boundCylinder>;
    boundTriangles = new List<boundTriangel>;

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

    for(int i = 2; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && resultFound == false; i++)   // look through the polygone
    {
        if(line[i] == '/')              // the vertices, texvertices and normalvectors are seperated by slashes
        {
            if(firstSlash == true)
            {
                firstSlash = false;

                if(line[++i] == '/')    // if the second slash is directly after the first slash, only normvectors are used
                {
                    used = normalsUsed;

                    resultFound = true;
                }
                else                    // if the second slash isn't directly after the first slash, texvertices are used
                    used = textureUsed;
            }
            else        // if there are two slashes, texture vertices and normal vectors are used
            {
                used = allUsed;

                resultFound = true;
            }
        }
    }

    return used;
}


vertexNumber ObjectType::countVertices(const char *filename, const char *objectname)
{
    FILE *f;
    int i, j;
    char line[50];
    char string[50];
    bool correctObject = false;
    vertexNumber vertexCounter = {0, 0, 0};

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

    char *line_ptr;

    int h, i , j;
    int vert_id[4], tex_id[4], norm_id[4];

    int vertexnumber = 0;

    bool correctObject = false;
    bool auto_texv_loaded = false;

    usedVertices used = nothingUsed;

    vertexNumber otherVertices = {0, 0, 0};
    vertexNumber myVertices = {0, 0, 0};
    vertexNumber allObjectVertices = countVertices(objectFile, objectName);

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

        line_ptr = line;

        skipUntilCharacters(&line_ptr, breakChars);
        skipCharacters(&line_ptr, placeholders);

        if(!strncmp(line, "mtllib", 6))
        {
            memset(matfile, '\0', sizeof(matfile));
            getString(&line_ptr, matfile, breakChars);

            continue;
        }

        if(!strncmp(line, "usemtl", 6))
        {
            memset(string, '\0', sizeof(string));
            getString(&line_ptr, string, breakChars);

            ObjectTypeMaterial = MatCache->requestMaterial(matfile, string);

            continue;
        }

        if(line[0] == 'o')
        {
            memset(string, '\0', sizeof(string));
            if(!strncmp(getString(&line_ptr, string, breakChars), objectName, strlen(string)))
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
                Vertex2D tempv2d = getVertex2D(&line_ptr);
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

                Vertex3D tempv3d = getVertex3D(&line_ptr);
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
                vector tempvec = getVector(&line_ptr);
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
                for(i = 2, vertexnumber = 1; line[i] != '\n' && line[i] != '\0'; i++) // check if it is a triangle or a square
                    if(line[i] == ' ')
                        vertexnumber++;

                used = verticesInPolygon(line);

                polygon_ptr = new Polygon(vertexnumber);

                polygones->PushFront(polygon_ptr);

                i = 1;

                for(h = 0; h < vertexnumber; h++)
                {

                    for(++i, j = 0; line[i] != ' ' && line[i] != '/' && line[i] != '\n' && line[i] != '\0'; i++, j++)
                    {
                        string[j] = line[i];
                    }

                    string[j] = '\0';

                    vert_id[h] = atoi(string);
                    vert_id[h] -= otherVertices.objectVertices+1;

                    if(vert_id[h] >= allObjectVertices.objectVertices)             // look if the used vertices are defined
                    {
                        cerr << "the file " << objectFile << " is corrupted: undefined vertices used" << endl;
                        exit(-1);
                    }

                    if(used == textureUsed || used == allUsed)
                    {

                        for(i++, j = 0; line[i] != ' ' && line[i] != '\n' && line[i] != '/'; i++, j++)
                        {
                            string[j] = line[i];
                        }

                        string[j+1] = '\0';

                        tex_id[h] = atoi(string);
                        tex_id[h] -= otherVertices.textureVertices+1;

                        if(tex_id[h] >= allObjectVertices.textureVertices)             // if the polygon uses texvertices, look if they are defined
                        {
                            cerr << "the file " << objectFile << " is corrupted: undefined texture vertices used" << endl;
                            exit(-1);
                        }

                    }

                    if(used == normalsUsed)
                    {
                        i++;
                    }

                    if(used == normalsUsed || used == allUsed)
                    {
                        for(i++, j = 0; line[i] != ' ' && line[i] != '\n'; i++, j++)
                        {
                            string[j] = line[i];
                        }


                        string[j+1] = '\0';

                        norm_id[h] = atoi(string);
                        norm_id[h] -= otherVertices.normalVectors+1;

                        if(norm_id[h] >= allObjectVertices.normalVectors)             // if the polygon uses normals, look if they are defined
                        {
                            cerr << "the file " << objectFile << " is corrupted: undefined normals used" << " " << norm_id[h] << " " << allObjectVertices.normalVectors << endl;
                            exit(-1);
                        }
                    }

                }

                for(i = 0; i < vertexnumber; i++)
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

    localPosition.setvalue(pos);
}


Object::~Object()
{
    delete sounds;
}


void Object::initObject()
{
    scale = vector(1, 1, 1);

    Angle = 0;
    rotationAxis = vector();

    relativeToObject = NULL;
    localPosition = vector();

    sounds = new List<Sound>();

    physObj = new PhysicalObject();

    approximationSphere = 10.0;

    if(ObjTypeCache == NULL)
        ObjTypeCache = new ObjectTypeCache();

    objType = NULL;
}


vector Object::getPosition()
{
    if(relativeToObject == NULL)
        return localPosition;
    else
        return relativeToObject->getPosition() + localPosition;
}

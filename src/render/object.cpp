#include <string.h>
#include <iostream>

#include <object.h>


Object::Object()
{
    initObject();
}

Object::Object(const char *filename, const char *objname)
{
    initObject();

    strncpy(objectname, objname, 20);

    loadObjectFile(filename, objname);
}

Object::Object(const char *filename, const char *objname, vector pos)
{
    initObject();

    strncpy(objectname, objname, 20);

    loadObjectFile(filename, objname);

    position.setvalue(pos);
}

/*Object::Object(Object *obj, const char *objname, vector pos, bool copy)
{
    strncpy(objectname, objname, 20);

    if(copy)
    {
        vertices = new List<vertex3D>(obj->vertices);
        normvertices = new List<vector>(obj->normvertices);
        texvertices = new List<vertex2D>(obj->texvertices);
        polygones = new List<Polygone>(obj->polygones);

        boundBoxes = new List<struct boundBox>(obj->boundBoxes);
        boundSpheres = new List<struct boundSphere>(obj->boundSpheres);
        boundPlanes = new List<struct boundPlane>(obj->boundPlanes);
        boundCylinders = new List<struct boundCylinder>(obj->boundCylinders);
        boundTriangles = new List<struct boundTriangel>(obj->boundTriangles);
    }
    else
    {
        vertices = obj->vertices;
        normvertices = obj->normvertices;
        texvertices = obj->texvertices;
        polygones = obj->polygones;

        boundBoxes = obj->boundBoxes;
        boundSpheres = obj->boundSpheres;
        boundPlanes = obj->boundPlanes;
        boundCylinders = obj->boundCylinders;
        boundTriangles = obj->boundTriangles;
    }

    scale = obj->scale;

    ObjectMaterial = obj->ObjectMaterial;

    isPhysicalActor = obj->isPhysicalActor;
    automatical_texturing = obj->automatical_texturing;

    position.setvalue(pos);
}*/

Object::~Object()
{
    delete vertices;
    delete normvertices;
    delete texvertices;

    delete polygones;
}

void Object::initObject()
{
    vertices = new List<vertex3D>;
    normvertices = new List<vector>;
    texvertices = new List<vertex2D>;

    polygones = new List<Polygone>;


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

    isPhysicalActor = false;
    automatical_texturing = true;

    ObjectMaterial = NULL;
}

usedVertices Object::vertices_in_polygone(char *line)
{
    usedVertices used = nothing_used;
    bool firstSlash = true;
    bool resultFound = false;
    int i;

    for(i = 2; line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && resultFound == false; i++)
    {
        if(line[i] == '/')
        {
            if(firstSlash == true)
            {
                firstSlash = false;

                if(line[++i] == '/')
                {
                    used = normals_used;

                    resultFound = true;
                }
                else
                    used = texture_used;
            }
            else
            {
                used = all_used;

                resultFound = true;
            }
        }
    }

    return used;
}

struct numofvertices Object::countVertices(const char *filename, const char *objectname)
{
    FILE *f;
    int i, j;
    char line[50];
    char string[50];
    bool correct_object = false;
    struct numofvertices vertexCounter = {0, 0, 0};

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
                correct_object = true;
            else
                break;
        }
        else if(line[0] == 'v' && line[1] == ' ')
        {
            if(correct_object == true)
                vertexCounter.objectVertices++;
        }
        else if(line[0] == 'v' && line[1]== 't')
        {
            if(correct_object == true)
                vertexCounter.textureVertices++;
        }
        else if(line[0] == 'v' && line[1] == 'n')
        {
            if(correct_object == true)
                vertexCounter.normalVertices++;
        }
        else
            continue;
    }

    fclose(f);

    return vertexCounter;
}

void Object::loadObjectFile(const char *objectFile, const char *objectName)
{
    FILE *f;

    char line[50];
    char string[50];

    int h, i , j;
    int vert_id[4], tex_id[4], norm_id[4];

    int vertexNumber = 0;

    bool correct_object = false;
    bool auto_texv_loaded = false;

    usedVertices used = nothing_used;

    struct numofvertices otherVertices = {0, 0, 0};
    struct numofvertices myVertices = {0, 0, 0};
    struct numofvertices allObjectVertices = countVertices(objectFile, objectName);

    vertex2D *texvertex_ptr = NULL;
    vertex2D *autotexvertex_ptrs[4];
    vertex3D *objvertex_ptr = NULL;
    vector *normvertex_ptr = NULL;

    vertex2D *texvertex_ptrs[allObjectVertices.textureVertices];
    vertex3D *objvertex_ptrs[allObjectVertices.objectVertices];
    vector *normvertex_ptrs[allObjectVertices.normalVertices];

    Polygone *polygone_ptr = NULL;

    if(allObjectVertices.objectVertices == 0)
    {
        fprintf(stderr, "error: object %s does not exist or has no vertices.\n", objectFile);
        return;
    }

    f = fopen(objectFile, "r");

    if(f == NULL)
    {
        printf("the file %s could not be opened.\n", objectFile);
        exit(-1);
    }

    do
    {
        fgets(line, 40, f);

        if(line[0] == '#')
            continue;

        if(line[0] == 'g')
        {
            printf("warning: polygone groups aren't supported yet by cryolite engine.\n");
            continue;
        }

        if(!strncmp(line, "usemtl", 6))
            continue;

        if(!strncmp(line, "mtllib", 6))
        {
            for(i = 7, j = 0; line[i] != '\n'; i++, j++)
                string[j] = line[i];

            string[j] = '\0';

            loadMaterial(string);

            continue;
        }


        if(line[0] == '\n')
            continue;

        if(line[0] == 'o')
        {
            for(i = 2, j = 0; line[i] != '\n'; i++, j++)
                string[j] = line[i];

            string[j] = '\0';

            if(!strncmp(string, objectName, strlen(string)))
                correct_object = true;
            else
                break;

            continue;
        }

        if(line[0] == 'v' && line[1] == 't')
        {
            if(correct_object == false)
                otherVertices.textureVertices++;
            else
            {

                texvertex_ptr = new vertex2D;

                for(i = 3, j = 0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
                    string[j] = line[i];

                if(line[i] == '\0' || line[i] == '\n')
                {
                    printf("error: File is corrupted. programm will be ended.\n");
                    exit(-1);
                }

                string[j+1] = '\0';

                texvertex_ptr->x = atof(string);

                for(i++, j = 0; line[i] != '\n' && line[i] != '\0'; i++, j++)
                    string[j] = line[i];

                string[j+1] = '\0';

                texvertex_ptr->y = atof(string);

                this->addTextureVertex(texvertex_ptr);

                texvertex_ptrs[myVertices.textureVertices] = texvertex_ptr;
                myVertices.textureVertices++;
            }

            continue;
        }

        if(line[0] == 'v' && line[1] == ' ')
        {
            if(correct_object == false)
                otherVertices.objectVertices++;
            else
            {

                objvertex_ptr = new vertex3D;

                for(i = 2, j = 0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
                    string[j] = line[i];

                if(line[i] == '\0' || line[i] == '\n')
                {
                    printf("error: File is corrupted. programm will be ended.\n");
                    exit(-1);
                }

                string[j+1] = '\0';

                objvertex_ptr->x = atof(string);

                for(i++, j = 0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
                    string[j] = line[i];

                if(line[i] == '\0' || line[i] == '\n')
                {
                    printf("error: File is corrupted. programm will be ended.\n");
                    exit(-1);
                }

                string[j+1] = '\0';

                objvertex_ptr->y = atof(string);

                for(i++, j = 0; line[i] != '\n' && line[i] != '\0'; i++, j++)
                    string[j] = line[i];

                string[j+1] = '\0';

                objvertex_ptr->z = atof(string);

                this->addObjectVertex(objvertex_ptr);

                objvertex_ptrs[myVertices.objectVertices] = objvertex_ptr;
                myVertices.objectVertices++;
            }

	    continue;
        }

	if(line[0] == 'v' && line[1] == 'n')
        {
            if(correct_object == false)
                otherVertices.normalVertices++;
            else
            {

                normvertex_ptr = new vector;

                for(i = 3, j = 0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
                    string[j] = line[i];

                if(line[i] == '\0' || line[i] == '\n')
                {
                    printf("error: File is corrupted. programm will be ended.\n");
                    exit(-1);
                }

                string[j+1] = '\0';

                normvertex_ptr->x = atof(string);

                for(i++, j = 0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
                    string[j] = line[i];

                if(line[i] == '\0' || line[i] == '\n')
                {
                    printf("error: File is corrupted. programm will be ended.\n");
                    exit(-1);
                }

                string[j+1] = '\0';

                normvertex_ptr->y = atof(string);

                for(i++, j = 0; line[i] != '\n' && line[i] != '\0'; i++, j++)
                    string[j] = line[i];

                string[j+1] = '\0';

                normvertex_ptr->z = atof(string);

                this->addNormalVertex(normvertex_ptr);

                normvertex_ptrs[myVertices.normalVertices] = normvertex_ptr;
                myVertices.normalVertices++;
            }

            continue;
        }

        if(line[0] == 'f')
        {
            if(correct_object == false)
                continue;
            else
            {
                for(i = 2, vertexNumber = 1; line[i] != '\n' && line[i] != '\0'; i++) // check if it is a triangle or a square
                    if(line[i] == ' ')
                        vertexNumber++;

                used = vertices_in_polygone(line);

                polygone_ptr = new Polygone(vertexNumber);

                addPolygone(polygone_ptr);

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

                    if(used == texture_used || used == all_used)
                    {

                        for(i++, j = 0; line[i] != ' ' && line[i] != '\n'; i++, j++)
                        {
                            string[j] = line[i];
                        }


                        string[j+1] = '\0';

                        tex_id[h] = atoi(string);
                        tex_id[h] -= otherVertices.textureVertices+1;

                    }

                    if(used == normals_used)
                        i++;

                    if(used == normals_used || used == all_used)
                    {
                        for(i++, j = 0; line[i] != ' ' && line[i] != '\n'; i++, j++)
                        {
                            string[j] = line[i];
                        }


                        string[j+1] = '\0';

                        norm_id[h] = atoi(string);
                        norm_id[h] -= otherVertices.normalVertices+1;
                    }

                }

                for(i = 0; i < vertexNumber; i++)
                {

                    polygone_ptr->setObjVertex(i, objvertex_ptrs[vert_id[i]]);

                    if(used == texture_used || used == all_used)
                        polygone_ptr->setTexVertex(i, texvertex_ptrs[tex_id[i]]);
                    else if(automatical_texturing == true && ObjectMaterial != NULL)
                    {
                        if(auto_texv_loaded == false)
                        {
                            auto_texv_loaded = true;

                            for(j = 0; j < 4; j++)
                                autotexvertex_ptrs[j] = new vertex2D;

                            autotexvertex_ptrs[0]->x = 0;
                            autotexvertex_ptrs[0]->y = 1;
                            autotexvertex_ptrs[1]->x = 0;
                            autotexvertex_ptrs[1]->y = 0;
                            autotexvertex_ptrs[2]->x = 1;
                            autotexvertex_ptrs[2]->y = 0;
                            autotexvertex_ptrs[3]->x = 1;
                            autotexvertex_ptrs[3]->y = 1;
                        }

                        polygone_ptr->setTexVertex(i, autotexvertex_ptrs[i%5]);
                    }

                    if(used == normals_used || used == all_used)
                        polygone_ptr->setNormVector(i, normvertex_ptrs[norm_id[i]]);
                }

                continue;

                printf("this should never be displayed.\n");
            }
        }
    }while(!feof(f));

    printf("file %s successfully loaded.\n", objectFile);

    fclose(f);

}

vertex3D *Object::addObjectVertex(vertex3D *new_vertex)
{
    vertices->ListPushFront(new_vertex);
    return new_vertex;
}

vector *Object::addNormalVertex(vector *new_norm_vertex)
{
    normvertices->ListPushFront(new_norm_vertex);
    return new_norm_vertex;
}

vertex2D *Object::addTextureVertex(vertex2D *new_tex_vertex)
{
    texvertices->ListPushFront(new_tex_vertex);
    return new_tex_vertex;
}

void Object::addPolygone(Polygone *newPolygone)
{
    polygones->ListPushFront(newPolygone);
}

void Object::loadMaterial(const char *file)
{
    ObjectMaterial = new Material(file);
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


    printf("V0m: %f Am: %f\n",this->V0m,this->Am);

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

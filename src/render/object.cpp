#include <string.h>

#include <object.h>


Object::Object(const char *objname)
{
    initObject();

    strncpy(objectname, objname, 20);
}

Object::Object(const char *filename, const char *objname)
{
    initObject();

    strncpy(objectname, objname, 20);

    loadObjectFile(filename, objname);
}

Object::~Object()
{
    delete vertices;
    delete normvertices;
    delete texvertices;

    delete triangles;
    delete squares;

    //delete ObjectMaterial;
}

void Object::initObject()
{
    vertices = new List<vertex3D>;
    normvertices = new List<vertex3D>;
    texvertices = new List<vertex2D>;

    triangles = new List<struct triangle>;
    squares = new List<struct square>;


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
    int i;

    for(i = 2; line[i] != '\n' && line[i] != '\0'; i++)
    {
        if(line[i] == '/')
        {
            if(firstSlash == true)
            {
                firstSlash = false;

                if(line[i+1] == '/')
                {
                    used = normals_used;

                    break;
                }
                else
                    used = texture_used;
            }
            else
            {
                used = all_used;

                break;
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
            {
                correct_object = false;
                break;
            }
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

    printf("Found %d Vertices, %d Texturevertices and %d Normalvertices.\n", vertexCounter.objectVertices, vertexCounter.textureVertices, vertexCounter.normalVertices);

    return vertexCounter;
}

void Object::loadObjectFile(const char *objectFile, const char *objectName)
{
    // when normals are fully implemented, activate line 161, line 179 and line 381

    printf("loading file %s...\n", objectFile);

    FILE *f;

    char line[50];
    char string[50];

    int h, i , j;
    int counter = 0;
    int vert_id[4], tex_id[4]/*, norm_id[4]*/;

    bool correct_object = false;
    bool triangle_or_square;
    bool auto_texv_loaded = false;

    usedVertices used = nothing_used;

    struct numofvertices otherVertices = {0, 0, 0};
    struct numofvertices myVertices = {0, 0, 0};
    struct numofvertices allObjectVertices = countVertices(objectFile, objectName);

    vertex2D *texvertex_ptr = NULL;
    vertex2D *autotexvertex_ptrs[4];
    vertex3D *objvertex_ptr = NULL;
    vertex3D *normvertex_ptr = NULL;

    vertex2D *texvertex_ptrs[allObjectVertices.textureVertices];
    vertex3D *objvertex_ptrs[allObjectVertices.objectVertices];
    //vertex3D *normvertex_ptrs[allObjectVertices.normalVertices];

    struct triangle *triangle_ptr = NULL;
    struct square *square_ptr = NULL;

    f = fopen(objectFile, "r");

    if(f == NULL)
    {
        printf("the file %s could not be opened.\n", objectFile);
        exit(-1);
    }

    while(*fgets(line, 40, f) != EOF)
    {

        if(line[0] == '#')
            continue;


        if(line[0] == 's')
        {
            printf("warning: smoothing groups aren't supported yet by cryolite engine.\n");
            continue;
        }

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
            {
                correct_object = false;
                break;
            }

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

                normvertex_ptr = new vertex3D;

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

                //normvertex_ptrs[myVertices.normalVertices] = normvertex_ptr;
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
                for(i = 2, counter = 0; line[i] != '\n' && line[i] != '\0'; i++) // check if it is a triangle or a square
                    if(line[i] == ' ')
                        counter++;

                if(counter == 2)
                    triangle_or_square = false;
                else if(counter == 3)
                    triangle_or_square = true;
                else
                {
                    printf("error: File is corrupted. programm will be ended.\n");
                    exit(-1);
                }

                used = vertices_in_polygone(line);

                if(triangle_or_square)
                {
                     square_ptr = new struct square;

                     this->addSquare(square_ptr);
                }
                else
                {
                    triangle_ptr = new struct triangle;

                    this->addTriangle(triangle_ptr);
                }

                i = 1;

                for(h = 0; h < (triangle_or_square ? 4 : 3); h++)
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

                }

                if(triangle_or_square)
                {

                    for(i = 0; i < 4; i++)
                    {

                        square_ptr->objVertex[i] = objvertex_ptrs[vert_id[i]];

                        if(used == texture_used || used == all_used)
                            square_ptr->texVertex[i] = texvertex_ptrs[tex_id[i]];
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

                            square_ptr->texVertex[i] = autotexvertex_ptrs[i];
                        }
                    }
                }
                else
                {

                    for(i = 0; i < 3; i++)
                    {
                        triangle_ptr->objVertex[i] = objvertex_ptrs[vert_id[i]];

                        if(used == texture_used || used == all_used)
                            triangle_ptr->texVertex[i] = texvertex_ptrs[tex_id[i]];
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

                            triangle_ptr->texVertex[i] = autotexvertex_ptrs[i];
                        }
                    }
                }

                continue;

                printf("this should never be displayed.\n");
            }
        }
    }

    printf("file successfully loaded.\n\n");

    fclose(f);

}

vertex3D *Object::addObjectVertex(vertex3D *new_vertex)
{
    vertices->ListPushFront(new_vertex);
    return new_vertex;
}

vertex3D *Object::addNormalVertex(vertex3D *new_norm_vertex)
{
    normvertices->ListPushFront(new_norm_vertex);
    return new_norm_vertex;
}

vertex2D *Object::addTextureVertex(vertex2D *new_tex_vertex)
{
    texvertices->ListPushFront(new_tex_vertex);
    return new_tex_vertex;
}

void Object::addTriangle(struct triangle *new_triangle)
{
    triangles->ListPushFront(new_triangle);
}

void Object::addSquare(struct square *new_square)
{
    squares->ListPushFront(new_square);
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
    if(F.elements[0] == Fd.elements[0] && F.elements[1] == Fd.elements[1] && F.elements[2] == Fd.elements[2])
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

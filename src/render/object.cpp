#include "object.h"
#include <math.h>



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

void Object::initObject()
{
    vertices = ListCreate();
    triangles = ListCreate();
    squares = ListCreate();
    texvertices = ListCreate();

    scale.x = 1;
    scale.y = 1;
    scale.z = 1;

    position.x = 0;
    position.y = 0;
    position.z = 0;

    distance.x = 0;
    distance.y = 0;
    distance.z = 0;

    rotationAxis.x = 0;
    rotationAxis.y = 0;
    rotationAxis.z = 0;

    colorKey.red = 1.0f;
    colorKey.green = 1.0f;
    colorKey.blue = 1.0f;
    colorKey.transparency = 1.0f;


    rotationAxis.x = 0;
    rotationAxis.y = 0;
    rotationAxis.z = 0;
    Angle = 0;
    remeaningAngle = 0;
    destAngle = 0;
    rotationVelocity = 0;
    rotationAcceleration = 0;
    startRotationTime = 0;
    remAngleSing = 0;

    velocity = 0;
    acceleration = 0;
    startTime = 0;
    destPos.x = 0;
    destPos.y = 0;
    destPos.z = 0;

    numofTextureSpots = 0;
    numofSpots = 0;
    numofTriangles = 0;
    numofSquares = 0;

    isPhysicalActor = false;

    ObjectMaterial = NULL;
}

Object::~Object()
{
    if(ObjectMaterial != NULL)
        ObjectMaterial->~Material();

    // TODO: integrate list destruction function when implemented
}

void Object::loadObjectFile(const char *objectFile, const char *objectName)
{
    FILE *f;                                                 // the file handle
    char line[40];                                          // a line of the file
    char string[40];                                        // string can be many things
    int h, i , j;                                           // h, i and j can too be many things
    int counter = 0;                                        // a general counter, counting what is to count
    int numofotherVertices = 0, numofotherTexVertices = 0;  // counting the vertices and texture vertices not belonging to my object
    int numofmyVertices = 0, numofmyTexVertices = 0;        // counting the vertices and texture vertices created until now to know the new arrey index
    int ObjectVertexCounter = 0, TextureVertexCounter = 0;  // counting the vertices and texture vertices before main parser, to set the array size
    int vert_id[4], tex_id[4];                              // temponary variables
    bool correct_object = false;                           // says if i have found the correct object yet
    bool triangle_or_square;                                // triangle == false, square == true
    bool texture_coordinates = false;
    struct vertex2D *texvertex_ptr = NULL;
    struct vertex3D *objvertex_ptr = NULL;
    struct triangle *triangle_ptr = NULL;
    struct square *square_ptr = NULL;

    printf("loading file %s...\n", objectFile);

    f = fopen(objectFile, "r");

    if(f == NULL)
    {
        printf("the file %s could not be opened.\n", objectFile);
        exit(-1);
    }

    while(fgets(line, 40, f))
    {
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
        }
        else if(line[0] == 'v' && line[1] == ' ')
        {
            if(correct_object == true)
                ObjectVertexCounter++;
        }
        else if(line[0] == 'v' && line[1]== 't')
        {
            if(correct_object == true)
                TextureVertexCounter++;
        }
        else
            continue;
    }

    correct_object = false;

    printf("Found %d Vertices and %d Texturevertices.\n", ObjectVertexCounter, TextureVertexCounter);

    struct vertex2D *texvertex_ptrs[TextureVertexCounter];
    struct vertex3D *objvertex_ptrs[ObjectVertexCounter];

    fseek(f, 0, SEEK_SET);

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

        if(line[0] == 'v' && line[1] == 'n')
        {
            printf("error: normals aren't supported yet by cryolite engine.\n");
            printf("       it's impossible to load object. programm will be ended.\n");
            exit(-1);
        }

        if(!strncmp(line, "usemtl", 6))
            continue;

        if(!strncmp(line, "mtllib", 6))
        {
            for(i = 7, j = 0; line[i] != '\n'; i++, j++)
                string[j] = line[i];

            string[j] = '\0';

            printf("loading texture %s...\n", string);

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
            {
                numofotherTexVertices++;
                continue;
            }
            else
            {

                texvertex_ptr = (struct vertex2D *)malloc(sizeof(struct vertex2D));

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

                texvertex_ptrs[numofmyTexVertices] = texvertex_ptr;
                numofmyTexVertices++;
            }

            continue;
        }

        if(line[0] == 'v' && line[1] == ' ')
        {
            if(correct_object == false)
            {
                numofotherVertices++;
                continue;
            }
            else
            {

                objvertex_ptr = (struct vertex3D *)malloc(sizeof(struct vertex3D));

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

                objvertex_ptrs[numofmyVertices] = objvertex_ptr;
                numofmyVertices++;
            }
        }

        if(line[0] == 'f')
        {
            if(correct_object == false)
                continue;
            else
            {

                for(i = 2, counter = 0; line[i] != '\n' && line[i] != '\0'; i++)     // check if it is a triangle or a square
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

                for(i = 2; line[i] != '\n' && line[i] != '\0'; i++)     // check if there are texture coordinates
                {
                    if(line[i] == '/')
                    {
                        texture_coordinates = true;
                        break;
                    }
                }

                if(triangle_or_square)
                {
                     square_ptr = (struct square *)malloc(sizeof(struct square));

                     if(square_ptr == NULL)
                     {
                         printf("error: unable to malloc enought ram. programm will be ended.\n");
                         exit(-1);
                     }

                     this->addSquare(square_ptr);
                }
                else
                {
                    triangle_ptr = (struct triangle *)malloc(sizeof(struct triangle));

                    if(triangle_ptr == NULL)
                     {
                         printf("error: unable to malloc enought ram. programm will be ended.\n");
                         exit(-1);
                     }

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
                    vert_id[h] -= numofotherVertices+1;

                    if(texture_coordinates)
                    {
                        for(i++, j = 0; line[i] != ' '; i++, j++)
                            string[j] = line[i];

                        string[j+1] = '\0';

                        tex_id[h] = atoi(string);
                        tex_id[h] -= numofotherTexVertices+1;
                    }

                }

                if(triangle_or_square)
                {

                    for(i = 0; i < 4; i++)
                    {

                        square_ptr->objVertex[i] = objvertex_ptrs[vert_id[i]];

                        if(texture_coordinates)
                            square_ptr->texVertex[i] = texvertex_ptrs[tex_id[i]];
                    }
                }
                else
                {

                    for(i = 0; i < 3; i++)
                    {
                        triangle_ptr->objVertex[i] = objvertex_ptrs[vert_id[i]];

                        if(texture_coordinates)
                            triangle_ptr->texVertex[i] = texvertex_ptrs[tex_id[i]];
                    }
                }

                continue;

                printf("this should never be displayed.\n");
            }
        }
    }

    printf("file successfully loaded.\n");

    fclose(f);

}


struct vertex3D *Object::addObjectVertex(struct vertex3D *new_vertex)
{
    numofSpots++;

    vertices = ListPushFront(vertices, new_vertex);
    return new_vertex;
}

struct vertex2D *Object::addTextureVertex(struct vertex2D *new_tex_vertex)
{
    numofTextureSpots++;

    texvertices = ListPushFront(texvertices, new_tex_vertex);
    return new_tex_vertex;
}

void Object::addTriangle(struct triangle *new_triangle)
{
    numofTriangles++;

    triangles = ListPushFront(triangles, new_triangle);
}

void Object::addSquare(struct square *new_square)
{
    numofSquares++;

    squares = ListPushFront(squares, new_square);
}

void Object::loadMaterial(const char *file)
{
    ObjectMaterial = new Material(file);
}


void Object::moveObject(float v,float a , struct vector3D motion)
{
    this->startTime = SDL_GetTicks();
    this->acceleration = a;
    this->distance = motion;
    this->velocity = v;
    this->destPos.x = motion.x+this->position.x;
    this->destPos.y = motion.y+this->position.y;
    this->destPos.z = motion.z+this->position.z;
}

void Object::rotateObject(float angle,float v,float a, struct vector3D rotationAxis)
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



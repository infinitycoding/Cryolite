#include "include/object.h"


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

    movement.x = 0;
    movement.y = 0;
    movement.z = 0;

    rotationAxis.x = 0;
    rotationAxis.y = 0;
    rotationAxis.z = 0;

    colorKey.red = 1.0f;
    colorKey.green = 1.0f;
    colorKey.blue = 1.0f;
    colorKey.transparency = 1.0f;

    rotationAngle = 0;

    velocity = 0;

    remaining_movement = 0;

    numofTextureSpots = 0;
    numofSpots = 0;
    numofTriangles = 0;
    numofSquares = 0;

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
    FILE *f;
    char line[40];
    char string[20];                                // string can be many things
    int i , j;                                      // i and j can too be many things
    int counter = 0;
    int numofotherVertices = 0, numofotherTexVertices = 0;  // counting the vertices and texture vertices not belonging to my object
    bool correct_object = false;
    bool triangle_or_square;                        // triangle == false, square == true
    bool texture_coordinates = false;
    struct vertex2D *texvertex_ptr;
    struct vertex3D *objvertex_ptr;
    struct triangle *triangle_ptr;
    struct square *square_ptr;

    f = fopen(objectFile, "r");
    if(f == NULL)
    {
        printf("Die Datei %s kann nicht geoeffnet werden.\n", objectFile);
        return;
    }

    while(fgets(line, 40, f))
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

        if(strncmp(line, "usemtl", 6))
            continue;

        if(line[0] == '\n')
            continue;

        if(line[0] == 'o')
        {
            for(i = 2, j = 0; line[i] != '\n'; i++, j++)
                string[j] = line[i];

            string[j+1] = '\0';

            if(strncmp(string, objectName, j))
                correct_object = true;
            else
                correct_object = false;

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

                for(i = 2, j = 0; line[i] != ' ' && line[i] != '\0' && line[i] != '\n'; i++, j++)
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
            }
        }

        if(line[0] == 'f')
        {
            if(correct_object == false)
                continue;
            else
            {
                for(i = 2; line[i] != '\n' && line[i] != '\0'; i++)     // check if it is a triangle or a square
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
                    square_ptr = (struct square *)malloc(sizeof(struct square));
                else
                    triangle_ptr = (struct triangle *)malloc(sizeof(struct triangle));


                // TODO: Write the rest of the function


                continue;
            }
        }
    }

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



#include "include/object.h"

void renderObject(struct object *obj,vertex *position){

    glBegin( GL_TRIANGLES );


    for(uint32_t i = 0; i < obj->numofTriangles; i++){

        for(int j = 0; j < 3; j++)
        {
            glColor3f(obj->triangles[i].c[j].red, obj->triangles[i].c[j].green, obj->triangles[i].c[j].blue);
                glVertex3f(obj->vertices[obj->triangles[i].p[j]].x+position->x, obj->vertices[obj->triangles[i].p[j]].y+position->y, obj->vertices[obj->triangles[i].p[j]].z+position->z);
        }

    }

    glEnd();

}

struct object *loadObject(const char *file){
    FILE *src = fopen(file,"r");
    if(!src)
        return NULL;

    fseek( src, 0, SEEK_END );
    size_t size = (size_t) ftell( src);
    fseek( src, 0, SEEK_SET );
    void *buffer = malloc(size);
    size_t readed = fread(buffer,1,size,src);
    if(!readed) return NULL;
    struct object *obj = (struct object*)malloc(sizeof(struct object));
    struct ObjectFileHeader *temp = (struct ObjectFileHeader*) buffer;
    obj->numofSpots = temp->numofSpots;
    obj->numofTriangles = temp->numofTriangles;
    obj->vertices = (struct vertex*) ((unsigned long)temp+sizeof(struct ObjectFileHeader));
    obj->triangles = (struct triangle*) ((unsigned long)obj->vertices+(obj->numofSpots*sizeof(struct vertex)));
    return obj;
}

int saveObject(struct object *obj,const char *file){
    FILE *f = fopen(file, "w");
    struct ObjectFileHeader header;
    header.numofSpots = obj->numofSpots;
    header.numofTriangles = obj->numofTriangles;
    fwrite ( (const void*) &header, 1, sizeof(header), f);

    fwrite (obj->vertices, 1, (obj->numofSpots*sizeof(vertex)), f);
    fwrite (obj->triangles, 1, (obj->numofTriangles*sizeof(triangle)), f);
    fclose(f);
    return 0;
}

struct object_expl *createObject_expl(void){
    struct object_expl *obj = (struct object_expl*)malloc(sizeof(struct object_expl));
    obj->numofSpots = 0;
    obj->numofTriangles = 0;
    obj->vertices = NULL;
    obj->triangles = NULL;
    return obj;
}

#include "include/object.h"

struct vertexlist
{
    struct vertex point;
    struct vertexlist *next;
};

struct trianglelist
{
    struct triangle tri;
    struct trianglelist *next;
};

struct vertexlist *sfirst = NULL;
struct trianglelist *tfirst = NULL;

int vcounter = 0;
int tcounter = 0;

void saveObject()
{
    struct ObjectFileHeader ofh;
    struct vertexlist *vtemp;
    struct trianglelist *ttemp;
    char filename[100];
    FILE *f;
    int i;

    printf("Wie soll die Datei heissen? ");
    scanf("%s", filename);

    f = fopen(filename, "w");

    ofh.numofSpots = vcounter;
    ofh.numofTriangles = tcounter;

    fwrite(&ofh, sizeof(struct ObjectFileHeader), 1, f);

    vtemp = sfirst;

    for(i = 0; i < vcounter; i++)
    {
        fwrite(&(vtemp->point), sizeof(struct vertex), 1, f);
        vtemp = vtemp->next;
    }

    ttemp = tfirst;

    for(i = 0; i < tcounter; i++)
    {
        fwrite(&(ttemp->tri), sizeof(struct triangle), 1, f);
        ttemp = ttemp->next;
    }

    fclose(f);

    printf("Datei erfolgreich geschrieben.\n");
}


void addVertex()
{
    int counter = 0;
    GLfloat x, y, z;
    struct vertexlist *temp;

    printf("Geben sie die Koordinaten des Punktes im Muster x y z an: ");
    scanf("%f %f %f",&x,&y,&z);

    if(sfirst == NULL)
    {
        sfirst = (struct vertexlist *)malloc(sizeof(struct vertexlist));

        sfirst->point.x = x;
        sfirst->point.y = y;
        sfirst->point.z = z;
        sfirst->next = NULL;

    }
    else
    {
        temp = sfirst;
        counter++;

        while(temp->next != NULL)
        {
            temp = temp->next;
            counter++;
        }

        temp->next = (struct vertexlist *)malloc(sizeof(struct vertexlist));
        temp = temp->next;

        temp->point.x = x;
        temp->point.y = y;
        temp->point.z = z;
        temp->next = NULL;
    }

    printf("Der von ihnen definierte Punkt hat die ID %d.\n", counter);

    vcounter++;

    return;
}


void addTriangle()
{
    int i;
    int ctemp[4];
    vertex_t s[3];
    struct color32 color[3];
    struct trianglelist *temp;

    printf("Geben sie die IDs der zu verwendenden Punkte im Muster p1 p2 p3 an: ");
    scanf("%u %u %u", &s[0], &s[1], &s[2]);

    for(i = 0; i < 3; i++)
    {
        printf("Geben sie die Farbwerte der %d.Punktes im Muster r g b t an: ", i);
        scanf("%d %d %d %d",&ctemp[0], &ctemp[1], &ctemp[2], &ctemp[3]);

        color[i].red = ctemp[0];
        color[i].green = ctemp[1];
        color[i].blue = ctemp[2];
        color[i].transparency = ctemp[3];
    }

    if(tfirst == NULL)
    {
        tfirst = (struct trianglelist *)malloc(sizeof(struct trianglelist));

        for(i = 0; i < 3; i++)
            tfirst->tri.p[i] = s[i];

        for(i = 0; i < 3; i++)
        {
            tfirst->tri.c[i].red = color[i].red;
            tfirst->tri.c[i].red = color[i].red;
            tfirst->tri.c[i].red = color[i].red;
            tfirst->tri.c[i].red = color[i].red;
        }

        tfirst->next = NULL;
    }
    else
    {
        temp = tfirst;

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = (struct trianglelist *)malloc(sizeof(struct trianglelist));
        temp = temp->next;

        for(i = 0; i < 3; i++)
            temp->tri.p[i] = s[i];

        for(i = 0; i < 3; i++)
        {
            temp->tri.c[i].red = color[i].red;
            temp->tri.c[i].red = color[i].red;
            temp->tri.c[i].red = color[i].red;
            temp->tri.c[i].red = color[i].red;
        }

        temp->next = NULL;
    }

    printf("Das Dreieck wurde erfolgreich erzeugt.\n");

    tcounter++;

    return;
}


void menue()
{
    int abfrage;

    do
    {
        printf("<1> Objekt erzeugen\n");
        printf("<2> Objekt darstellen\n\n");
        printf("Ihre Wahl < >\b\b");
        scanf("%d", &abfrage);

        if(abfrage == 1)
            printf("Lade Menue...\n\n");
        else if(abfrage == 2)
            return;
        else
            printf("Fehlerhafte Eingabe.\n");

    }while(abfrage != 1);

    do
    {
        printf("<1> Punkt erzeugen\n");
        printf("<2> Dreieck erzeugen\n");
        printf("<3> Objekt speichern\n");
        printf("<4> Programm beenden\n\n");
        printf("Ihre Wahl < >\b\b");
        scanf("%d", &abfrage);

        switch(abfrage)
        {
            case 1:
                addVertex();
                break;
            case 2:
                addTriangle();
                break;
            case 3:
                saveObject();
                break;
            case 4:
                printf("Beende Programm...\n");
                break;
            default:
                printf("Fehlerhafte Eingabe.\n");
        }

    }while(abfrage != 4);

    exit(0);
}

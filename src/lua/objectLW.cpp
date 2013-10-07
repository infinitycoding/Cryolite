#include <lua/script.h>
#include <object.h>
#include <scene.h>



NEWBEGIN(newObject)
    char *arg1 = NULL;
    char *arg2 = NULL;
    vector *arg3 = NULL;

    switch(getargc())
    {
        case 1:
            CONSTRUCT();

            addInstance(Object *, new Object());
        break;

        case 3:
            CHECK(isstring(1) && isstring(2))
                getarg(arg2=LSTR() arg1=LSTR());
            ELSE
                lerror("\nnew(object): invalid types of arguments; expected two strings.\n");
            CHECKEND

            CONSTRUCT();

            addInstance(Object *, new Object(arg1, arg2));
        break;

        case 4:
            CHECK(isobject(1) && isstring(2) && isstring(3))
                getarg(arg3=LDAT(vector *, "vector") arg2=LSTR() arg1=LSTR());
            ELSE
                lerror("\nnew(object): invalid types of arguments; expected two strings and a vector.\n");
            CHECKEND

            CONSTRUCT();

            addInstance(Object *, new Object(arg1, arg2, *arg3));
        break;

        default:
            lerror("\nnew(object): invalid number of arguments; expected 1, 3 or 4; got %d.\n", getargc());
        break;
    }
NEWEND(object)

extern Scene *mainScene;

CBEGIN(addToScene)
    CHECK(getargc() != 1)
        lerror("\nget(fps): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND

    mainScene->addObject(*getInstance(Object **, "object"));
CEND(0)


reg objReg[]
{
    {"new", newObject},
    {"activate", addToScene},
    {NULL, NULL}
};

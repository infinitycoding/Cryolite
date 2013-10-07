#include <lua/script.h>
#include <fps.h>



extern FPS *fps;



NEWBEGIN(newFPS)
    CHECK(getargc() != 1)
        lerror("\nnew(fps): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND

    CONSTRUCT();
    addInstance(FPS *, fps);
NEWEND(fps)


CBEGIN(getFPS)
    CHECK(getargc() != 1)
        lerror("\nget(fps): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND
CEND(1, LDBL((*getInstance(FPS **, "fps"))->get()))


reg fpsReg[]
{
    {"new", newFPS},
    {"get", getFPS},
    {NULL, NULL}
};

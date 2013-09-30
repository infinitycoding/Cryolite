#include <lua/script.h>
#include <fps.h>



extern FPS *fps;



NEWBEGIN(newFPS)
    if(getargc() != 1)
    {
        luaL_error(L, "\nnew(fps): invalid number of arguments; expected 1; got %d.\n", getargc());
    }

    CONSTRUCT();

    FPS **newInstance = addInstance(FPS *);
    *newInstance = fps;
NEWEND(fps)

CBEGIN(getFPS)
    if(getargc() != 1)
    {
        luaL_error(L, "\nget(fps): invalid number of arguments; expected 1; got %d.\n", getargc());
    }

    lua_pushnumber(L, (double)(*getInstance(FPS **, "fps"))->get());

    return 1;
CEND


luaL_Reg fpsReg[]
{
    {"new", newFPS},
    {"get", getFPS},
    {NULL, NULL}
};

#include <lua/script.h>
#include <fps.h>



extern FPS *fps;



NEWBEGIN(newFPS)
    FPS **newInstance = addInstance(FPS *);
    *newInstance = fps;
NEWEND(fps)

CBEGIN(getFPS)
    if(getargc() > 1)
    {
        luaL_error(L, "get(fps): invalid number of arguments; expected 1, got %d.\n", getargc());
    }

    lua_getfield(L, -1, "__self");

    lua_pushnumber(L, (double)(*((FPS **)luaL_checkudata(L, -1, "fps")))->get());

    return 1;
CEND


luaL_Reg fpsReg[]
{
    {"new", newFPS},
    {"get", getFPS},
    {NULL, NULL}
};

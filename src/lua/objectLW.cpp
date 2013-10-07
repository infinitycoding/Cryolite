#include <lua/script.h>
#include <object.h>
#include <scene.h>



NEWBEGIN(newObject)
    char *arg1 = NULL;
    char *arg2 = NULL;
    vector *arg3 = NULL;
    Object **newInstance = NULL;

    switch(getargc())
    {
        case 1:
            CONSTRUCT();

            newInstance = addInstance(Object *);
            *newInstance = new Object();
        break;

        case 3:
            if(lua_isstring(L, -1) && lua_isstring(L, -2))
            {
                getarg(arg2=LSTR() arg1=LSTR());
            }
            else
            {
                luaL_error(L, "\nnew(object): invalid types of arguments; expected two strings.\n");
            }

            CONSTRUCT();

            newInstance = addInstance(Object *);
            *newInstance = new Object(arg1, arg2);
        break;

        case 4:
            if(lua_istable(L, -1) && lua_isstring(L, -2) && lua_isstring(L, -3))
            {
                getarg(arg3=LDAT(vector *, "vector") arg2=LSTR() arg1=LSTR());
            }
            else
            {
                luaL_error(L, "\nnew(object): invalid types of arguments; expected two strings and a vector.\n");
            }

            CONSTRUCT();

            newInstance = addInstance(Object *);
            *newInstance = new Object(arg1, arg2, *arg3);
        break;

        default:
            luaL_error(L, "\nnew(object): invalid number of arguments; expected 1, 3 or 4; got %d.\n", getargc());
        break;
    }
NEWEND(object)

extern Scene *mainScene;

CBEGIN(addToScene)
    if(getargc() != 1)
    {
        luaL_error(L, "\nget(fps): invalid number of arguments; expected 1; got %d.\n", getargc());
    }

    mainScene->addObject(*getInstance(Object **, "object"));

    return 0;
CEND


luaL_Reg objReg[]
{
    {"new", newObject},
    {"activate", addToScene},
    {NULL, NULL}
};

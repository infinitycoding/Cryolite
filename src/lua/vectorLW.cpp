
#include <lua/script.h>
#include <vector.h>


NEWBEGIN(new_vector)
    vector *v;
    vector v1;
    std::cerr<<"vector:"<< getargc() << std::endl;
    switch(getargc())
    {
        case 1: //null constructor
            CONSTRUCT();
            v = addInstance(vector);
            v[0] = vector();
        break;

        case 2:
            if(lua_isnumber(L, -1)) //x-coordinate
            {
                v1 = vector(lua_tonumber(L, -1));
                lua_pop(L,1);
                CONSTRUCT();
                lua_pop(L, 1);
                vector *v = addInstance(vector);
                *v = v1;
            }
            else if(lua_istable(L, -1)) //Copy constructor
            {
                v = getInstance(vector *, "vector");
                lua_pop(L, 1);
            }
            else
            {
                luaL_error(L, "\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            }
        break;

        case 3:
            if(lua_isnumber(L, -1) && lua_isnumber(L, -2)) // x and y coordinate
            {
                v1 = vector(lua_tonumber(L, -1),lua_tonumber(L, -2));
                lua_pop(L,2);
                CONSTRUCT();
                vector *v = addInstance(vector);
                *v = v1;
            }
            else
            {
                luaL_error(L, "\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            }
        break;

        case 4:
            if(lua_isnumber(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3)) // x, y and z coordinate
            {
                v1 = vector(lua_tonumber(L, -1), lua_tonumber(L, -2), lua_tonumber(L, -3));
                lua_pop(L, 3);
                CONSTRUCT();
                vector *v = addInstance(vector);
                *v = v1;
            }
            else
            {
                luaL_error(L, "\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            }
        break;

        default:
            luaL_error(L, "\n vector(new): invalid number of arguments; got %d, expected 1,2 or 3", getargc());
        break;

    };
NEWEND(vector)




luaL_Reg vectorReg[]
{
    {"new", new_vector},
    {NULL, NULL}
};


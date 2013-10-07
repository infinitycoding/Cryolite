
#include <lua/script.h>
#include <vector.h>


NEWBEGIN(new_vector)
    vector v1;
    switch(getargc())
    {
        case 1: //null constructor
            CONSTRUCT();
            addInstance(vector, vector());
        break;

        case 2:
            if(lua_isnumber(L, -1)) //x-coordinate
            {
                v1 = vector(lua_tonumber(L, -1));
                lua_pop(L,1);
                CONSTRUCT();
                lua_pop(L, 1);
                addInstance(vector, v1);
            }
            else if(lua_istable(L, -1)) //Copy constructor
            {
                addInstance(vector, getInstance(vector *, "vector"));
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
                v1 = vector(lua_tonumber(L, -2),lua_tonumber(L, -1));
                lua_pop(L,2);
                CONSTRUCT();
                addInstance(vector, v1);
            }
            else
            {
                luaL_error(L, "\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            }
        break;

        case 4:
            if(lua_isnumber(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3)) // x, y and z coordinate
            {
                v1 = vector(lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1));
                lua_pop(L, 3);
                CONSTRUCT();
                addInstance(vector, v1);
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


CBEGIN(null_vector)
    if(getargc() == 1)
    {
        vector *v = getInstance(vector *, "vector");
        v->null();
    }
    else
    {
        luaL_error(L, "\n vector(null): invalid number of arguments; got %d, expected none", getargc());
    }
CEND(0)

CBEGIN(len_vector)
    if(getargc() == 1)
    {
        vector *v = getInstance(vector *, "vector");
        LDBL(v->len());
        return 1;
    }
    else
    {
        luaL_error(L, "\n vector(len): invalid number of arguments; got %d, expected none", getargc());
    }
CEND(0)

CBEGIN(print_vector)
    if(getargc() == 1)
    {
        vector *v = getInstance(vector *, "vector");
        v->print();
    }
    else
    {
        luaL_error(L, "\n vector(print): invalid number of arguments; got %d, expected none", getargc());
    }
CEND(0)

CBEGIN(set_vector)

CEND(0)

CBEGIN(unify_vector)
    if(getargc() == 1)
    {
        vector *v = getInstance(vector *, "vector");
        v->unify();
    }
    else
    {
        luaL_error(L, "\n vector(unify): invalid number of arguments; got %d, expected none", getargc());
    }
CEND(0)

NEWBEGIN(unifyc_vector)
    if(getargc() == 1)
    {
        vector *v = getInstance(vector *, "vector");
        vector vr = v->unifyc();
        CONSTRUCT();
        LDAT(vector, vr);
    }
    else
    {
        luaL_error(L, "\n vector(unifyc): invalid number of arguments; got %d, expected none", getargc());
    }
NEWEND(vector)




reg vectorReg[]
{
    {"new", new_vector},
    {"null", null_vector},
    {"len", len_vector},
    {"print", print_vector},
    {"set", set_vector},
    {"unify", unify_vector},
    {"unifyc", unifyc_vector},
    {NULL, NULL}
};


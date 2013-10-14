
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
            CHECK(isnumber(1)) //x-coordinate
                double x = getarg(LDBL());
                CONSTRUCT();
                addInstance(vector, vector(x));

            ELSEIF(isobject(1)) //Copy constructor
                addInstance(vector, *getInstance(vector *, "vector"));

            ELSE
                luaL_error(L, "\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            CHECKEND
        break;

        case 3:
            CHECK(isnumber(1) && isnumber(2)) // x and y coordinate
                double y = getarg(LDBL());
                double x = getarg(LDBL());
                CONSTRUCT();
                addInstance(vector, vector(x, y));

            ELSE
                luaL_error(L, "\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            CHECKEND
        break;

        case 4:
            CHECK(isnumber(1) && isnumber(2) && isnumber(3)) // x, y and z coordinate
                double z = getarg(LDBL());
                double y = getarg(LDBL());
                double x = getarg(LDBL());
                CONSTRUCT();
                addInstance(vector, vector(x, y, z));
            ELSE
                luaL_error(L, "\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            CHECKEND
        break;

        default:
            luaL_error(L, "\n vector(new): invalid number of arguments; got %d, expected 1,2 or 3", getargc());
        break;
    };
NEWEND(vector)


CBEGIN(null_vector)
    CHECK(getargc() == 1)
        getInstance(vector *, "vector")->null();
    ELSE
        luaL_error(L, "\n vector(null): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(len_vector)
    CHECK(getargc() == 1)
        RET(1,LDBL(getInstance(vector *, "vector")->len()));
    ELSE
        luaL_error(L, "\n vector(len): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(print_vector)
    CHECK(getargc() == 1)
        getInstance(vector *, "vector")->print();
    ELSE
        luaL_error(L, "\n vector(print): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(set_vector)
        switch(getargc())
        {
            case 2: //instance + 1. arg
                CHECK(isnumber(1))
                    getInstance(vector *, "vector")->setvalue(getarg(LDBL()));
                ELSEIF(isobject(1))
                    getInstance(vector *, "vector")->setvalue(getarg(LDAT(vector *, "vector")));
                ELSE
                    luaL_error(L, "\n vector(set): invalid argument type; Number or vector expected.");
                CHECKEND
            break;

            case 3:
                CHECK(isnumber(1) && isnumber(2))
                    getarg(double y = LDBL(); double x = LDBL());
                    getInstance(vector *, "vector")->setvalue(x,y);
                ELSE
                    luaL_error(L, "\n vector(set): invalid argument type; Two numbers expected.");
                CHECKEND
            break;

            case 4:
                CHECK(isnumber(1) && isnumber(2) && isnumber(3))
                     getarg(double z = LDBL(); double y = LDBL(); double x = LDBL());
                    getInstance(vector *, "vector")->setvalue(x,y,z);
                ELSE
                    luaL_error(L, "\n vector(set): invalid argument type; Three numbers expected.");
                CHECKEND
            break;

            default:
                luaL_error(L, "\n vector(set): invalid number of arguments; got %d, expected 1,2 or 3", getargc());
            break;
        };
CEND(0)


CBEGIN(unify_vector)
    CHECK(getargc() == 1)
        getInstance(vector *, "vector")->unify();
    ELSE
        luaL_error(L, "\n vector(unify): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


NEWBEGIN(unifyc_vector)
    CHECK(getargc() == 1)
        vector v = getInstance(vector *, "vector")->unifyc();
        CONSTRUCT();
        RET(1,LDAT(vector, v));
    ELSE
        luaL_error(L, "\n vector(unifyc): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
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


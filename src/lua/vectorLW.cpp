
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
                lerror("\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            CHECKEND
        break;

        case 3:
            CHECK(isnumber(1) && isnumber(2)) // x and y coordinate
                double y = getarg(LDBL());
                double x = getarg(LDBL());
                CONSTRUCT();
                addInstance(vector, vector(x, y));

            ELSE
                lerror("\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
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
                lerror("\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            CHECKEND
        break;

        default:
            lerror("\n vector(new): invalid number of arguments; got %d, expected 1,2 or 3", getargc());
        break;
    };
NEWEND(vector)


CBEGIN(null_vector)
    CHECK(getargc() == 1)
        getInstance(vector *, "vector")->null();
    ELSE
        lerror("\n vector(null): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(len_vector)
    CHECK(getargc() == 1)
        RET(1,LDBL(getInstance(vector *, "vector")->len()));
    ELSE
        lerror("\n vector(len): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(print_vector)
    CHECK(getargc() == 1)
        getInstance(vector *, "vector")->print();
    ELSE
        lerror("\n vector(print): invalid number of arguments; got %d, expected none", getargc());
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
                    lerror("\n vector(set): invalid argument type; Number or vector expected.");
                CHECKEND
            break;

            case 3:
                CHECK(isnumber(1) && isnumber(2))
                    getarg(double y = LDBL(); double x = LDBL());
                    getInstance(vector *, "vector")->setvalue(x,y);
                ELSE
                    lerror("\n vector(set): invalid argument type; Two numbers expected.");
                CHECKEND
            break;

            case 4:
                CHECK(isnumber(1) && isnumber(2) && isnumber(3))
                     getarg(double z = LDBL(); double y = LDBL(); double x = LDBL());
                    getInstance(vector *, "vector")->setvalue(x,y,z);
                ELSE
                    lerror("\n vector(set): invalid argument type; Three numbers expected.");
                CHECKEND
            break;

            default:
                lerror("\n vector(set): invalid number of arguments; got %d, expected 1,2 or 3", getargc());
            break;
        };
CEND(0)


CBEGIN(unify_vector)
    CHECK(getargc() == 1)
        getInstance(vector *, "vector")->unify();
    ELSE
        lerror("\n vector(unify): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


NEWBEGIN(unifyc_vector)
    CHECK(getargc() == 1)
        vector v = getInstance(vector *, "vector")->unifyc();
        CONSTRUCT();
        RET(1,LDAT(vector, v));
    ELSE
        lerror("\n vector(unifyc): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
NEWEND(vector)


CBEGIN(add_vector)
    switch(getargc())
    {
        case 0:
        case 1:
            lerror("\n vector(add): invalid number of arguments; got %d, expected 2 or 3 ", getargc());
        break;

        case 2:
            CHECK(isobject(1))
                getInstance(vector *, "vector")->add(getarg(LDAT(vector *, "vector")));
            ELSE
                lerror("\n vector(add): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
                getInstance(vector *, "vector")->add(getarg(LDAT(vector *, "vector")),getarg(LDAT(vector *, "vector")));
            ELSE
                lerror("\n vector(add): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
            for(int i = 1; i <= getargc(); i++)
            {
                if(!isobject(i))
                    lerror("\n vector(add): invalid argument %d type; vector expected.", i);
            }
            vector temp = vector();
            while(getargc() > 1)
            {
                temp += getarg(LDAT(vector *, "vector"));
            }
            getInstance(vector *, "vector")->add(temp);
        break;
    };
CEND(0)


CBEGIN(addc_vector)
    switch(getargc())
    {
        case 0:
        case 1:
            lerror("\n vector(addc): invalid number of arguments; got %d, expected 2 or 3 ", getargc());
        break;

        case 2:
            CHECK(isobject(1))
                RET(1, LDAT(vector, *getarg(LDAT(vector *, "vector")) + getInstance(vector *, "vector")));
            ELSE
                lerror("\n vector(addc): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
                RET(1, LDAT(vector, *getarg(LDAT(vector *, "vector")) + *getarg(LDAT(vector *, "vector"))));
            ELSE
                lerror("\n vector(addc): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
            for(int i = 1; i <= getargc(); i++)
            {
                if(!isobject(i))
                    lerror("\n vector(addc): invalid argument %d type; vector expected.", i);
            }
            vector temp = vector();
            while(getargc() > 1)
            {
                temp += getarg(LDAT(vector *, "vector"));
            }
            RET(1, getInstance(vector *, "vector")->addc(temp));
        break;
    };
CEND(0)


CBEGIN(sub_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                getInstance(vector *, "vector")->sub(getarg(LDAT(vector *, "vector")));
            ELSE
                lerror("\n vector(sub): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
            vector v2 = *getarg(LDAT(vector *, "vector"));
                getInstance(vector *, "vector")->sub(getarg(LDAT(vector *, "vector")), v2);
            ELSE
                lerror("\n vector(sub): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(sub): invalid number of arguments; got %d, expected 2 or 3 ", getargc());
        break;
    };
CEND(0)


CBEGIN(subc_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                RET(1, LDAT(vector, *getarg(LDAT(vector *, "vector")) - getInstance(vector *, "vector")));
            ELSE
                lerror("\n vector(subc): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
                RET(1, LDAT(vector, *getarg(LDAT(vector *, "vector")) - *getarg(LDAT(vector *, "vector"))));
            ELSE
                lerror("\n vector(subc): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
                lerror("\n vector(subc): invalid number of arguments; got %d, expected 2 or 3 ", getargc());
        break;

    };
CEND(0)

CBEGIN(scale_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isnumber(1))
                double s = getarg(LDBL());
                getInstance(vector *, "vector")->scale(s);
            ELSE
                lerror("\n vector(scale): invalid argument type; number expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(scale): invalid number of arguments; got %d, expected 2 ", getargc());
        break;
    };
CEND(0)


CBEGIN(scalec_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isnumber(1))
                double s = getarg(LDBL());
                RET(1, LDAT(vector,getInstance(vector *, "vector")->scalec(s)));
            ELSE
                lerror("\n vector(scalec): invalid argument type; number expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(scalec): invalid number of arguments; got %d, expected 2 ", getargc());
        break;
    };
CEND(0)


CBEGIN(cross_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                getInstance(vector *, "vector")->cross(getarg(LDAT(vector *, "vector")));
            ELSE
                lerror("\n vector(cross): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
            vector v2 = *getarg(LDAT(vector *, "vector"));
                getInstance(vector *, "vector")->cross(getarg(LDAT(vector *, "vector")), v2);
            ELSE
                lerror("\n vector(cross): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(cross): invalid number of arguments; got %d, expected 2 or 3 ", getargc());
        break;
    };
CEND(0)

CBEGIN(crossc_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                RET(1, LDAT(vector, *getarg(LDAT(vector *, "vector")) ^ getInstance(vector *, "vector")));
            ELSE
                lerror("\n vector(crossc): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
                RET(1, LDAT(vector, *getarg(LDAT(vector *, "vector")) ^ *getarg(LDAT(vector *, "vector"))));
            ELSE
                lerror("\n vector(crossc): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
                lerror("\n vector(crossc): invalid number of arguments; got %d, expected 2 or 3 ", getargc());
        break;

    };
CEND(0)






reg vectorReg[]
{
    {"new", new_vector},
    {"null", null_vector},
    {"len", len_vector},
    {"print", print_vector},
    {"set", set_vector},
    {"unify", unify_vector},
    {"unifyc", unifyc_vector},
    {"add", add_vector},
    {"addc", addc_vector},
    {"sub", sub_vector},
    {"subc", subc_vector},
    {"scale", scale_vector},
    {"scalec", scalec_vector},
    {"cross", cross_vector},
    {"crossc", crossc_vector},
    {NULL, NULL}
};


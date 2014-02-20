
#include <lua/script.h>
#include <vector.h>
#include <iostream>
using namespace std;

/*CLASS
    OVERLOAD(new_vector)
        SELECT(LDAT(vector,vector()), (istype(float)))
    ENDOVERLOAD

    ASSOCIATION(vector)
        ALIAS(new_vector,"new")
    ENDASSOCIATION

ENDCLASS*/






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
                addInstance(vector, vector(x,0.0,0.0));

            ELSEIF(istobjecttype(vector)) //Copy constructor
                cout<<"done untill here"<<endl;
                addInstance(vector, *getInstance(vector));

            ELSE
                lerror("\n vector(new): invalid arguments; expected vector, number, two numbers or three numbers");
            CHECKEND
        break;

        case 3:
            CHECK(isnumber(1) && isnumber(2)) // x and y coordinate
                double y = getarg(LDBL());
                double x = getarg(LDBL());
                CONSTRUCT();
                addInstance(vector, vector(x, y,0.0));

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


CBEGIN(get_vector)
    vector v = vector();
    CHECK(getargc() == 1)
        v = *getInstance(vector);
    ELSE
        lerror("\n vector(get): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(3,LDBL(v.x[2]); LDBL(v.x[1]); LDBL(v.x[0]))



CBEGIN(null_vector)
    CHECK(getargc() == 1)
        getInstance(vector)->null();
    ELSE
        lerror("\n vector(null): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(len_vector)
    CHECK(getargc() == 1)
        RET(1,LDBL(getInstance(vector)->len()));
    ELSE
        lerror("\n vector(len): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(print_vector)
    CHECK(getargc() == 1)
        getInstance(vector)->print();
    ELSE
        lerror("\n vector(print): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


CBEGIN(set_vector)
        switch(getargc())
        {
            case 2: //instance + 1. arg
                CHECK(isnumber(1))
                    getInstance(vector)->setvalue(getarg(LDBL()));
                ELSEIF(isobject(1))
                    getInstance(vector)->setvalue(getarg(LDAT(vector, "vector")));
                ELSE
                    lerror("\n vector(set): invalid argument type; Number or vector expected.");
                CHECKEND
            break;

            case 3:
                CHECK(isnumber(1) && isnumber(2))
                    getarg(double y = LDBL(); double x = LDBL());
                    getInstance(vector)->setvalue(x,y);
                ELSE
                    lerror("\n vector(set): invalid argument type; Two numbers expected.");
                CHECKEND
            break;

            case 4:
                CHECK(isnumber(1) && isnumber(2) && isnumber(3))
                     getarg(double z = LDBL(); double y = LDBL(); double x = LDBL());
                    getInstance(vector)->setvalue(x,y,z);
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
        getInstance(vector)->unify();
    ELSE
        lerror("\n vector(unify): invalid number of arguments; got %d, expected none", getargc());
    CHECKEND
CEND(0)


NEWBEGIN(unifyc_vector)
    CHECK(getargc() == 1)
        vector v = getInstance(vector)->unifyc();
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
            lerror("\n vector(add): invalid number of arguments; got %d, expected 1 or more ", getargc());
        break;

        case 2:
            CHECK(isobject(1))
                getInstance(vector)->add(getarg(LDAT(vector, "vector")));
            ELSE
                lerror("\n vector(add): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
                getInstance(vector)->add(getarg(LDAT(vector, "vector")),getarg(LDAT(vector, "vector")));
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
                temp += getarg(LDAT(vector, "vector"));
            }
            getInstance(vector)->add(temp);
        break;
    };
CEND(0)

NEWBEGIN(addc_vector)
    vector r = vector();
    switch(getargc())
    {
        case 0:
        case 1:
            lerror("\n vector(addc): invalid number of arguments; got %d, expected 1 or more ", getargc());
        break;

        case 2:
            CHECK(isobject(1))

                r = getInstance(vector) + *getarg(LDAT(vector, "vector"));
            ELSE
                lerror("\n vector(addc): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
                r = getarg(LDAT(vector, "vector")) + *getarg(LDAT(vector, "vector"));
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
                temp += getarg(LDAT(vector, "vector"));
            }
            r = getInstance(vector)->addc(temp);
        break;
    };

    CONSTRUCT();
    addInstance(vector, r);
NEWEND(vector)


CBEGIN(sub_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                getInstance(vector)->sub(getarg(LDAT(vector, "vector")));
            ELSE
                lerror("\n vector(sub): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
            vector v2 = *getarg(LDAT(vector, "vector"));
                getInstance(vector)->sub(getarg(LDAT(vector, "vector")), v2);
            ELSE
                lerror("\n vector(sub): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(sub): invalid number of arguments; got %d, expected 1 or 2 ", getargc());
        break;
    };
CEND(0)


NEWBEGIN(subc_vector)
    vector r = vector();
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                r =  getInstance(vector)->subc(getarg(LDAT(vector, "vector")));
            ELSE
                lerror("\n vector(subc): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
                r = getarg(LDAT(vector, "vector"))->subc(getarg(LDAT(vector, "vector")));
            ELSE
                lerror("\n vector(subc): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
                lerror("\n vector(subc): invalid number of arguments; got %d, expected 1 or 2 ", getargc());
        break;
    };
    CONSTRUCT();
    addInstance(vector, r);
NEWEND(vector)

CBEGIN(scale_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isnumber(1))
                double s = getarg(LDBL());
                getInstance(vector)->scale(s);
            ELSE
                lerror("\n vector(scale): invalid argument type; number expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(scale): invalid number of arguments; got %d, expected 1 ", getargc());
        break;
    };
CEND(0)


NEWBEGIN(scalec_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isnumber(1))
                vector r = getInstance(vector)->scalec(getarg(LDBL()));
                CONSTRUCT();
                addInstance(vector, r);
            ELSE
                lerror("\n vector(scalec): invalid argument type; number expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(scalec): invalid number of arguments; got %d, expected 1 ", getargc());
        break;
    };
NEWEND(vector)


/*CBEGIN(cross_vector)
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                getInstance(vector)->cross(getarg(LDAT(vector, "vector")));
            ELSE
                lerror("\n vector(cross): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
            vector v2 = *getarg(LDAT(vector, "vector"));
                getInstance(vector)->cross(getarg(LDAT(vector, "vector")), v2);
            ELSE
                lerror("\n vector(cross): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(cross): invalid number of arguments; got %d, expected 1 or 2 ", getargc());
        break;
    };
CEND(0)

NEWBEGIN(crossc_vector)
    vector r = vector();
    switch(getargc())
    {
        case 2:
            CHECK(isobject(1))
                r = getInstance(vector)->crossc(getarg(LDAT(vector, "vector")));
            ELSE
                lerror("\n vector(cross): invalid argument type; vector expected.");
            CHECKEND
        break;

        case 3:
            CHECK(isobject(1) && isobject(2))
            vector v2 = *getarg(LDAT(vector, "vector"));
                r = getInstance(vector)->crossc(getarg(LDAT(vector, "vector")), v2);
            ELSE
                lerror("\n vector(cross): invalid argument type; two vectors expected.");
            CHECKEND
        break;

        default:
            lerror("\n vector(cross): invalid number of arguments; got %d, expected 1 or 2 ", getargc());
        break;
    };
    CONSTRUCT();
    addInstance(vector, r);
NEWEND(vector)*/


CBEGIN(equal_vector)
    bool r;
    CHECK(getargc() == 2 && isobject(1) && isobject(2))
        vector a = *getarg(LDAT(vector, "vector"));
        vector b = *getarg(LDAT(vector, "vector"));
        CHECK(a.x[0] == b.x[0] && a.x[1] == b.x[1] && a.x[2] == b.x[2])
            r = true;
        ELSE
            r = false;
        CHECKEND
    ELSE
        CHECK(getargc() != 2)
            lerror("\n vector(==): invalid number of arguments; got %d, expected 2", getargc());
        ELSE
            lerror("\n vector(cross): invalid argument type; two vectors expected.");
        CHECKEND
    CHECKEND
CEND(1,LBOOL(r))



reg vectorReg[]
{
    {"new", new_vector},
    {"get", get_vector},
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
    /*{"cross", cross_vector},
    {"crossc", crossc_vector},*/
    {"__add", addc_vector},
    {"__sub", subc_vector},
    {"__mul", scalec_vector},
    /*{"__pow", crossc_vector},*/
    {"__eq", equal_vector},
    {NULL, NULL}
};



#include <lua/script.h>
#include <vector.h>
#include <iostream>
using namespace std;




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


CLASS
    OVERLOAD(new_vector)
        SELECT(addInstance(vector,vector(LDBL(),LDBL(),LDBL())), 3, (istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2)))
        SELECT(addInstance(vector,vector(LDBL(),LDBL(),0)), 2, (istype(float,ARG0) && istype(float,ARG1)))
        SELECT(addInstance(vector,vector(LDBL(),0,0)), 1, istype(float,ARG0))
        SELECT(addInstance(vector,vector(*getInstance(vector))), 1, (istobjecttype(vector)))
    ENDOVERLOAD

    CBEGIN(get_vector)
        vector v = vector();
        CHECK(getargc() == 1)
            v = *getInstance(vector);
        ELSE
            lerror("\n vector(get): invalid number of arguments; got %d, expected none", getargc());
        CHECKEND
    CEND(3,LDBL(v.x[2]); LDBL(v.x[1]); LDBL(v.x[0]))


    VOIDFUNCTION(null_vector,getInstance(vector)->null(),1,true)
    FUNCTION(len_vector,LDBL(getInstance(vector)->len()),1,true)
    VOIDFUNCTION(print_vector,getInstance(vector)->print(),1,true)

    ASSOCIATION(vector)
        ALIAS(new_vector,"new")
        ALIAS(get_vector,"get")
        ALIAS(null_vector,"null")
        ALIAS(len_vector,"len")
        ALIAS(print_vector,"print")
        ALIAS(set_vector,"set")
        ALIAS(unify_vector,"unify")
        ALIAS(unifyc_vector,"unifyc")
        ALIAS(add_vector,"add")
        ALIAS(addc_vector,"addc")
        ALIAS(sub_vector,"sub")
        ALIAS(subc_vector,"subc")
        ALIAS(scale_vector,"scale")
        ALIAS(scalec_vector,"scalec")
        ALIAS(addc_vector,"__add")
        ALIAS(subc_vector,"__sub")
        ALIAS(scalec_vector,"__mul")
        ALIAS(equal_vector,"__eq")
    ENDASSOCIATION

ENDCLASS


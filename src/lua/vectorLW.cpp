#include <lua/script.h>
#include <vector.h>

CLASS
    OVERLOAD(new_vector)
        SELECT(addInstance(vector,vector(0, 0, 0)), 0, true)
        SELECT(addInstance(vector,vector(LDBL(),LDBL(),LDBL())), 3, (istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2)))
        SELECT(addInstance(vector,vector(LDBL(),LDBL(),0)), 2, (istype(float,ARG0) && istype(float,ARG1)))
        SELECT(addInstance(vector,vector(LDBL(),0,0)), 1, istype(float,ARG0))
        SELECT(addInstance(vector,vector(getInstance(vector))), 1, (istobjecttype(vector)))
    ENDOVERLOAD

    OVERLOAD(set_vector)
        SELECT(VOID getInstance(vector)->setvalue(LDBL(),LDBL(),LDBL()),3,(istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2)))
        SELECT(VOID getInstance(vector)->setvalue(LDBL(),LDBL(),0),2,(istype(float,ARG0) && istype(float,ARG1)))
        SELECT(VOID getInstance(vector)->setvalue(LDBL(),0,0),1,istype(float,ARG0))
        SELECT(VOID getInstance(vector)->setvalue(LDAT(vector, "vector")), 1, (istobjecttype(vector)))
    ENDOVERLOAD

    OVERLOAD(add_vector)
        SELECT(VOID getInstance(vector)->add(LDAT(vector, "vector")),1,true)
        SELECT(VOID getInstance(vector)->add(LDAT(vector, "vector"),LDAT(vector, "vector")),2,true)
    ENDOVERLOAD

    OVERLOAD(addc_vector)
        SELECT(addInstance(vector,getInstance(vector)->addc(LDAT(vector, "vector"))),1,true)
        SELECT(addInstance(vector,getInstance(vector)->addc(LDAT(vector, "vector"),LDAT(vector, "vector"))),2,true)
    ENDOVERLOAD

    OVERLOAD(sub_vector)
        SELECT(VOID getInstance(vector)->sub(LDAT(vector, "vector")),1,true)
        SELECT(VOID getInstance(vector)->sub(LDAT(vector, "vector"),LDAT(vector, "vector")),2,true)
    ENDOVERLOAD

    OVERLOAD(subc_vector)
        SELECT(addInstance(vector,getInstance(vector)->subc(LDAT(vector, "vector"))),1,true)
        SELECT(addInstance(vector,getInstance(vector)->subc(LDAT(vector, "vector"),LDAT(vector, "vector"))),2,true)
    ENDOVERLOAD

    CBEGIN(get_vector)
        vector v = vector();
        CHECK(getargc() == 1)
            v = *getInstance(vector);
        ELSE
            lerror("\n vector(get): invalid number of arguments; got %d, expected none", getargc());
        CHECKEND
    CEND(3,LDBL(v.x[2]); LDBL(v.x[1]); LDBL(v.x[0]))


    FUNCTION(null_vector,VOID getInstance(vector)->null(),1,true)
    FUNCTION(len_vector,LDBL(getInstance(vector)->len()),1,true)
    FUNCTION(print_vector,VOID getInstance(vector)->print(),1,true)
    FUNCTION(scale_vector,VOID getInstance(vector)->scale(LDBL()),2,istype(float,ARG0));
    FUNCTION(scalec_vector,addInstance(vector,getInstance(vector)->scalec(LDBL())),2,istype(float,ARG0));
    FUNCTION(unify_vector,VOID getInstance(vector)->unify(),1,true);
    FUNCTION(unifyc_vector,addInstance(vector,getInstance(vector)->unifyc()),1,true);
    FUNCTION(equal_vector,LBOOL((*getInstance(vector)) == (*LDAT(vector, "vector"))),2,true)

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


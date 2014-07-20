/*
     Copyright 2012-2014 Infinitycoding all rights reserved
     This file is part of the Cryolite Engine.
 
     The Cryolite Engine is free software: you can redistribute it and/or modify
     it under the terms of the GNU Lesser General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     any later version.
 
     The Cryolite Engine is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU Lesser General Public License for more details.
 
     You should have received a copy of the GNU Lesser General Public License
     along with the Cryolite Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <util/script.h>
#include <util/vector.h>

CLASS
    OVERLOAD(new_vector)
        SELECT(addInstance(vector,vector(0, 0, 0)), 0, true)
        SELECT(addInstance(vector,vector(LDBL(),LDBL(),LDBL())), 3, (istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2)))
        SELECT(addInstance(vector,vector(LDBL(),LDBL(),0)), 2, (istype(float,ARG0) && istype(float,ARG1)))
        SELECT(addInstance(vector,vector(LDBL(),0,0)), 1, istype(float,ARG0))
        SELECT(addInstance(vector,vector(getInstance(vector))), 1, istobjecttype(vector))
    ENDOVERLOAD

    OVERLOAD(set_vector)
        SELECT(VOID getInstance(vector)->setvalue(LDBL(),LDBL(),LDBL()),3,(istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2)))
        SELECT(VOID getInstance(vector)->setvalue(LDBL(),LDBL(),0),2,(istype(float,ARG0) && istype(float,ARG1)))
        SELECT(VOID getInstance(vector)->setvalue(LDBL(),0,0),1,istype(float,ARG0))
        SELECT(VOID getInstance(vector)->setvalue(LDAT(vector, "vector")), 1, istobjecttype(vector))
    ENDOVERLOAD

    OVERLOAD(add_vector)
        SELECT(VOID getInstance(vector)->add(LDAT(vector, "vector")),1,istobjecttype(vector))
        SELECT(VOID getInstance(vector)->add(LDAT(vector, "vector"),LDAT(vector, "vector")),2,istobjecttype(vector))
    ENDOVERLOAD

    OVERLOAD(addc_vector)
        SELECT(addInstance(vector,getInstance(vector)->addc(LDAT(vector, "vector"))),1,istobjecttype(vector))
        SELECT(addInstance(vector,getInstance(vector)->addc(LDAT(vector, "vector"),LDAT(vector, "vector"))),2,istobjecttype(vector))
    ENDOVERLOAD

    OVERLOAD(sub_vector)
        SELECT(VOID getInstance(vector)->sub(LDAT(vector, "vector")),1,istobjecttype(vector))
        SELECT(VOID getInstance(vector)->sub(LDAT(vector, "vector"),LDAT(vector, "vector")),2,istobjecttype(vector))
    ENDOVERLOAD

    OVERLOAD(subc_vector)
        SELECT(addInstance(vector,getInstance(vector)->subc(LDAT(vector, "vector"))),1,istobjecttype(vector))
        SELECT(addInstance(vector,getInstance(vector)->subc(LDAT(vector, "vector"),LDAT(vector, "vector"))),2,istobjecttype(vector))
    ENDOVERLOAD

    CBEGIN(get_vector)
        vector v = vector();
        CHECK(getargc() == 1)
            v = *getInstance(vector);
        ELSE
            lerror("\n vector(get): invalid number of arguments; got %d, expected none", getargc());
        CHECKEND
    CEND(3,LDBL(v.x[2]); LDBL(v.x[1]); LDBL(v.x[0]))


    FUNCTION(null_vector,VOID getInstance(vector)->null(),1,istobjecttype(vector))
    FUNCTION(len_vector,LDBL(getInstance(vector)->len()),1,istobjecttype(vector))
    FUNCTION(print_vector,VOID getInstance(vector)->print(),1,istobjecttype(vector))
    FUNCTION(scale_vector,VOID getInstance(vector)->scale(LDBL()),2,istype(float,ARG0));
    FUNCTION(scalec_vector,addInstance(vector,getInstance(vector)->scalec(LDBL())),2,istype(float,ARG0));
    FUNCTION(unify_vector,VOID getInstance(vector)->unify(),1,istobjecttype(vector));
    FUNCTION(unifyc_vector,addInstance(vector,getInstance(vector)->unifyc()),1,istobjecttype(vector));
    FUNCTION(equal_vector,LBOOL((*getInstance(vector)) == (*LDAT(vector, "vector"))),2,istobjecttype(vector))

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


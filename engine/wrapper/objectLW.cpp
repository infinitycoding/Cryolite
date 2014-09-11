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
#include <render/object.h>


CLASS
     OVERLOAD(new_object)
          SELECT(addInstance(Object, Object()                                    ), 0, true                                                                 )
          SELECT(addInstance(Object, Object(LSTR())                              ), 1, istype(char *,ARG0)                                                  )
          SELECT(addInstance(Object, Object(LSTR(), LSTR())                      ), 2, istype(char *,ARG0) && istype(char *,ARG0)                           )
          SELECT(addInstance(Object, Object(LSTR(), LSTR(), LDAT(vector, "vector")) ), 3, istype(char *,ARG0) && istype(char *,ARG0) && istobjecttype(vector)  )
     ENDOVERLOAD;


     FUNCTION(get_object_pos      , addInstance(vector, getInstance(Object)->getPosition()) ,1 ,istobjecttype(Object));
     FUNCTION(get_object_type     , LSTR(getInstance(Object)->objType->objectTypeName)      ,1 ,istobjecttype(Object));
     FUNCTION(get_object_id       , LINT(getInstance(Object)->ID)                           ,1 ,istobjecttype(Object));
     FUNCTION(get_object_scale    , addInstance(vector, getInstance(Object)->scale)         ,1 ,istobjecttype(Object));
     FUNCTION(get_object_local_pos, addInstance(vector, getInstance(Object)->localPosition) ,1 ,istobjecttype(Object));

     FUNCTION(set_object_scale    , VOID getInstance(Object)->scale = LDAT(vector, "vector")        , 1, istobjecttype(Object));
     FUNCTION(set_object_local_pos, VOID getInstance(Object)->localPosition = LDAT(vector, "vector"), 1, istobjecttype(Object));

     ASSOCIATION(Object)
          ALIAS(new_object           , "new"              )
          ALIAS(get_object_local_pos , "getPosition"      )
          ALIAS(get_object_type      , "getType"          )
          ALIAS(get_object_id        , "getId"            )
          ALIAS(get_object_scale     , "getScale"         )
          ALIAS(get_object_local_pos , "getLocalPosition" )
          ALIAS(set_object_scale     , "setScale"         )
          ALIAS(set_object_local_pos , "setLocalPosition" )
     ENDASSOCIATION

ENDCLASS
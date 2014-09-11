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
#include <camera.h>



CLASS
    FUNCTION(new_camera, addInstance(Camera, Camera(NULL,vector(0,0,0),vector(0,0,0),1,10,90)), 1, true)

    FUNCTION(set_local_position, VOID getInstance(Camera)->localPosition.setvalue(LDBL(),LDBL(),LDBL()), 4, istype(int, ARG0) && istype(int, ARG1) && istype(int, ARG2) && istobjecttype(Camera));
    FUNCTION(set_fov, VOID getInstance(Camera)->fov=LDBL(), 2, istype(float, ARG0));

    FUNCTION(get_local_position, LDAT(vector, getInstance(Camera)->localPosition), 1, istobjecttype(Camera))
    FUNCTION(get_position, LDAT(vector, getInstance(Camera)->getPosition()), 1, istobjecttype(Camera))
    FUNCTION(get_fov, LDBL(getInstance(Camera)->fov), 1, istobjecttype(Camera));


    ASSOCIATION(Camera)
        ALIAS(new_camera, "new")
        ALIAS(set_local_position, "setLocalPosition")
        ALIAS(set_fov, "setFOV")
        ALIAS(get_local_position, "getLocalPosition")
        ALIAS(get_position, "getPosition")
        ALIAS(get_fov, "getFOV")
    ENDASSOCIATION
ENDCLASS


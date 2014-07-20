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
#include <level.h>


CLASS
    FUNCTION(new_scene,addInstance(Level,Level()),1,true)
    FUNCTION(add_object,VOID getInstance(Level)->addObject(getInstance(Object)),2,istobjecttype(Object,ARG0) && istobjecttype(Level,ARG1))
    FUNCTION(add_cam,VOID getInstance(Level)->addCam(getInstance(Camera)),2,istobjecttype(Camera,ARG0) && istobjecttype(Level,ARG1))
    FUNCTION(render_scene,VOID getInstance(Level)->render(),1,istobjecttype(Level))
    FUNCTION(get_fps, LDBL(getInstance(Level)->fps->get()),1,istobjecttype(Level))

    ASSOCIATION(Level)
        ALIAS(new_scene,"new")
        ALIAS(add_object,"addObject")
        ALIAS(add_cam,"addCam")
        ALIAS(render_scene,"render")
        ALIAS(get_fps,"getFPS")
    ENDASSOCIATION
ENDCLASS
#ifndef GENERAL_DEF_H_INCLUDED
#define GENERAL_DEF_H_INCLUDED

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

#define STANDART_NEARCLIP 1.5
#define STANDART_FARCLIP 100

#define STANDART_FOV 80

#define STANDART_WIDTH 640
#define STANDART_HEIGHT 480

#define STARTING_X 0
#define STARTING_Y 0
#define STARTING_Z 0

#define STANDARD_SIZED_CACHE 100

#define OBJECT_PATH  "game/resource/objects/"
#define IMAGE_PATH  "game/resource/images/"
#define FONT_PATH "game/resource/fonts/"
#define SOUND_PATH "game/resource/sounds/"
#define RESOURCE_PATH "game/resource/"
#define SCRIPT_PATH "game/scripts/"
#define SHADER_PATH "game/shaders/"

#define OBJECT(FILE) OBJECT_PATH #FILE
#define RESOURCE(FILE) RESOURCE_PATH #FILE
#define IMAGE(FILE) IMAGE_PATH #FILE
#define FONT(FILE) FONT_PATH #FILE
#define SOUND(FILE) SOUND_PATH #FILE
#define SCRIPT(FILE) SCRIPT_PATH #FILE
#define SHADER(FILE) SHADER_PATH #FILE




#endif

#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

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

#include <GL/gl.h>
#include <SDL.h>


#include <util/script.h>
#include <util/general_def.h>



class Settings
{
    public:
        virtual bool loadSettingsFile(const char *filename);
        virtual void activateSettings();

    protected:
        virtual void initSettings();
};


class EngineSettings : public Settings
{
    public:
        EngineSettings();
        EngineSettings(const char *filename);
        virtual ~EngineSettings();

        virtual bool loadSettingsFile(const char *filename);
        virtual void activateSettings();


        bool captureMouse;
        bool hud;
        int width;
        int height;
        int sdlFlags;
        int multisamples;
        float lineWidth;
        float pointSize;
        float fov;

    protected:
        virtual void initSettings();
};


#endif

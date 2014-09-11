#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED
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



#include <SDL.h>



class FPS
{
    public:
        FPS();
        virtual ~FPS();

        void calculate();

        void print();
        float get();

    protected:
        static const int accuracy;

        int lasttick;
        float averageFPS;

        int currenttick;
        int ticcount;
        int tickbundle;
        double sum;

        float lastFPS;
};



#endif
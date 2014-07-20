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

#include <fps.h>


const int FPS::accuracy = 60;



FPS::FPS()
{
    currenttick = 0;
    ticcount = 0;
    tickbundle = 3;
    sum = 0;
    lasttick = SDL_GetTicks();
    averageFPS = 60;
    lastFPS = 0;
}


FPS::~FPS()
{

}


void FPS::calculate()
{
    currenttick = SDL_GetTicks();
    if(ticcount==tickbundle)
    {
        averageFPS = sum/tickbundle;
        sum = 0;
        ticcount = 0;
        tickbundle = accuracy;
    }
    else
    {
        if(currenttick-lasttick > 0)
        {
            sum +=(1000.0/(float)(currenttick-lasttick));
            ticcount++;
        }
    }
    lasttick = currenttick;
}


void FPS::print()
{
    for(int i = 0; i<9;i++)
    {
        printf("\b");
    }

    if(lastFPS<=averageFPS-0.05 || lastFPS>=averageFPS+0.05)
    {

        printf ("%4.1f FPS\n",averageFPS);
        lastFPS = averageFPS;
    }
}


float FPS::get()
{
    return averageFPS;
}

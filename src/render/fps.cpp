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

        printf ("%4.1f FPS",averageFPS);
        lastFPS = averageFPS;
    }
}


float FPS::get()
{
    return averageFPS;
}

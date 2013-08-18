#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED



#include <cstdio>

#include <SDL.h>

#include <settings.h>



class FPS
{
    public:
        FPS();
        virtual ~FPS();

        void calculate();

        void print();
        float get();

    protected:
        int lasttick;
        int accuracy;
        float averageFPS;

        int currenttick;
        int ticcount;
        int tickbundle;
        double sum;

        float lastFPS;
};



#endif

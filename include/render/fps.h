#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED




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

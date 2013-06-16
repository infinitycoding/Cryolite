#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED



#include <SDL.h>



#define MAX_PROFILE_PLOTS 20

/********************************************************
 *                                                      *
 * Profiler-Module                                      *
 * ---------------                                      *
 *                                                      *
 * This module allows you to profile code, this means,  *
 * it will show you which part of the code takes which  *
 * part of the time.                                    *
 *                                                      *
 * Author: Peter Hösch                                  *
 *                                                      *
 ********************************************************/


class Profiler
{

    public:

        Profiler();
        Profiler(Profiler *templ);
        virtual ~Profiler();

        void resetProfile();

        bool addProfilePlot();
        bool addFinalProfilePlot();

        bool saveProfile(const char *filename);

    private:

        unsigned int getActualTime();


        unsigned int lastAddTime;
        unsigned int allTicks;

        unsigned int actualProfilePlot;
        unsigned int highestProfilePlot;
        unsigned int profilePlots[MAX_PROFILE_PLOTS];


};


#endif

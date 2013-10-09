#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED



#include <SDL.h>


#define STANDART_MAX_PROFILE_PLOTS 20


typedef unsigned int ticks;



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
        Profiler(unsigned int profilePlotNumber);
        virtual ~Profiler();

        void resetProfile();

        bool addProfilePlot();
        bool addFinalProfilePlot();

        bool saveProfile(const char *filename);


    protected:

        ticks getActualTime();


        ticks lastAddTime;
        ticks allTicks;

        unsigned int actualProfilePlot;
        unsigned int highestProfilePlot;

        unsigned int numOfProfilePlots;
        ticks *profilePlots;


};


#endif

#include <profiler.h>


// The standart constructor.
// Set's all counter variables to zero and sets the time to the actual time.

Profiler::Profiler()
{
    resetProfile();
}


// The copy-constructor.
// Copy's all variables to the new object.

Profiler::Profiler(Profiler *templ)
{
    lastAddTime = templ->lastAddTime;
    allTicks = templ->allTicks;

    actualProfilePlot = templ->actualProfilePlot;
    highestProfilePlot = templ->highestProfilePlot;

    memcpy(profilePlots, templ->profilePlots, sizeof(profilePlots));
}


// The destructor.
// Every class should have an destructor.

Profiler::~Profiler()
{

}


// This function sets the class to the state it was after creation.

void Profiler::resetProfile()
{
    lastAddTime = getActualTime();
    allTicks = 0;

    actualProfilePlot = 0;
    highestProfilePlot = 0;

    memset(profilePlots, 0, sizeof(profilePlots));
}


// Add's a profile plot at the actual location.
// It returns false if there was an error, true otherwise.

bool Profiler::addProfilePlot()
{
    unsigned int actualTime = getActualTime();
    unsigned int timeDifference = actualTime - lastAddTime;

    if(!(actualProfilePlot > MAX_PROFILE_PLOTS))
        profilePlots[actualProfilePlot] += timeDifference;
    else
        return false;

    allTicks += timeDifference;

    lastAddTime = actualTime;
    actualProfilePlot++;

    return true;
}


// Add's the last profile plot at the actual location.
// It is only needed in loops.
// It returns false if there was an error, true otherwise.

bool Profiler::addFinalProfilePlot()
{
    bool failed = addProfilePlot();

    highestProfilePlot = actualProfilePlot-1;
    actualProfilePlot = 0;

    return failed;
}


// This functionn saves the generated profile in a file.
// You need to give the filename to it.
// It returns false if there was an error, true otherwise.

bool Profiler::saveProfile(const char *filename)
{
    FILE *savefile;
    unsigned int counter;

    if((savefile = fopen(filename, "w")) == NULL)
        return false;

    fprintf(savefile, "Gesamt : %u : 100%%\n", allTicks);

    for(counter = 0; counter <= highestProfilePlot; counter++)
        fprintf(savefile, "%u : %u : %g%%\n", counter, profilePlots[counter], 100 * ((float)profilePlots[counter] / allTicks));

    if(!fclose(savefile))
        return false;

    return true;
}


// This is an intern function, it's only reason of existing is to make the
// profiler-class independant of SDL without big changes.

unsigned int Profiler::getActualTime()
{
    return SDL_GetTicks();
}

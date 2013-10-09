#include <optimize/profiler.h>


// The zero constructor.
// Set's all counter variables to zero and sets the time to the actual time.
// The maximal profile plot number is a default one.

Profiler::Profiler()
{
    profilePlots = new ticks[STANDART_MAX_PROFILE_PLOTS];
    numOfProfilePlots = STANDART_MAX_PROFILE_PLOTS;

    resetProfile();
}


// The standart constructor.
// Set's all counter variables to zero and sets the time to the actual time.
// The maximal profile plot number is given as a parameter.

Profiler::Profiler(unsigned int profilePlotNumber)
{
    profilePlots = new ticks[profilePlotNumber];
    numOfProfilePlots = profilePlotNumber;

    resetProfile();
}


// The destructor.
// Every class should have an destructor.

Profiler::~Profiler()
{
    delete[] profilePlots;
}


// This function sets the class to the state it was after creation.

void Profiler::resetProfile()
{
    lastAddTime = getActualTime();
    allTicks = 0;

    actualProfilePlot = 0;
    highestProfilePlot = 0;

    memset(profilePlots, 0, sizeof(ticks) * numOfProfilePlots);
}


// Add's a profile plot at the actual location.
// It returns false if there was an error, true otherwise.

bool Profiler::addProfilePlot()
{
    ticks actualTime = getActualTime();
    ticks timeDifference = actualTime - lastAddTime;

    if(!(actualProfilePlot > numOfProfilePlots))
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

ticks Profiler::getActualTime()
{
    return SDL_GetTicks();
}

#include <lua/script.h>
#include <optimize/profiler.h>



NEWBEGIN(newProfiler)
    unsigned int parameter;

    switch(getargc())
    {
        case 1:
            CONSTRUCT();
            addInstance(Profiler *, new Profiler());
        break;

        case 2:
            CHECK(isnumber(1))
                getarg(parameter=(unsigned int)LDBL());
            ELSE
                lerror("\nnew(profiler): invalid type of argument; expected one number.\n");
            CHECKEND

            CONSTRUCT();
            addInstance(Profiler *, new Profiler(parameter));
        break;

        default:
            lerror("\nnew(profiler): invalid number of arguments; expected 1 or 2; got %d.\n", getargc());
        break;
    }
NEWEND(profiler)


CBEGIN(resetProfiler)
    CHECK(getargc() != 1)
        lerror("\nreset(profiler): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND

    (*getInstance(Profiler **, "profiler"))->resetProfile();
CEND(0)


CBEGIN(addP)
    CHECK(getargc() != 1)
        lerror("\naddPlot(profiler): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND

    bool success = (*getInstance(Profiler **, "profiler"))->addProfilePlot();
CEND(1, LBOOL(success))


CBEGIN(addFinalP)
    CHECK(getargc() != 1)
        lerror("\naddFinalPlot(profiler): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND

    bool success = (*getInstance(Profiler **, "profiler"))->addFinalProfilePlot();
CEND(1, LBOOL(success))


CBEGIN(saveProfiler)
    char *filename = NULL;

    CHECK(getargc() != 2)
        lerror("\nsave(profiler): invalid number of arguments; expected 2; got %d.\n", getargc());
    CHECKEND

    CHECK(isstring(1))
        getarg(filename=LSTR());
    ELSE
        lerror("\nsave(profiler): invalid type of argument; expected one string.\n");
    CHECKEND

    bool success = (*getInstance(Profiler **, "profiler"))->saveProfile(filename);
CEND(1, LBOOL(success))


reg profilerReg[]
{
    {"new", newProfiler},
    {"reset", resetProfiler},
    {"addPlot", addP},
    {"addFinalPlot", addFinalP},
    {"save", saveProfiler},
    {NULL, NULL}
};

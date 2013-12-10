#include <lua/script.h>
#include <shader.h>


#include <cstring>


NEWBEGIN(newShader)
    char *arg1 = NULL;
    char *arg2 = NULL;

    switch(getargc())
    {
        case 1:
            CONSTRUCT();

            addInstance(Shader, Shader());
        break;

        case 3:
            CHECK(isstring(1) && isstring(2))
                getarg(arg2=LSTR(); arg1=LSTR());
            ELSE
                lerror("\nnew(shader): invalid types of arguments; expected two strings.\n");
            CHECKEND

            CONSTRUCT();

            addInstance(Shader, Shader(arg1, arg2));
        break;

        default:
            lerror("\nnew(shader): invalid number of arguments; expected 1 or 3; got %d.\n", getargc());
        break;
    }
NEWEND(Shader)


CBEGIN(loadS)
    char *file = NULL;
    char *ltype = NULL;
    ShaderType cpptype = undefined;

    CHECK(getargc() != 1)
        lerror("\nloadShader(shader): invalid number of arguments; expected 3; got %d.\n", getargc());
    CHECKEND

    CHECK(isstring(1) && isstring(2))
        getarg(ltype=LSTR(); file=LSTR());
    ELSE
        lerror("\nloadShader(shader): invalid types of arguments; expected two strings.\n");
    CHECKEND

    CHECK(!strncmp(ltype, "vertexShader", sizeof("vertexShader")))
        cpptype = vertexShader;
    ELSEIF(!strncmp(ltype, "fragmentShader", sizeof("fragmentShader")))
        cpptype = fragmentShader;
    ELSE
        lerror("\nloadShader(shader): invalid argument number two; expected \"vertexShader\" or \"fragmentShader\".\n");
    CHECKEND
CEND(1, LBOOL(getInstance(Shader)->loadShader(file, cpptype)))


CBEGIN(makeS)
    CHECK(getargc() != 1)
        lerror("\nmake(shader): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND
CEND(1, LBOOL(getInstance(Shader)->make()))


CBEGIN(activateS)
    CHECK(getargc() != 1)
        lerror("\nactivate(shader): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND
CEND(1, LBOOL(getInstance(Shader)->activate()))


CBEGIN(deactivateS)
    CHECK(getargc() != 1)
        lerror("\ndeactivate(shader): invalid number of arguments; expected 1; got %d.\n", getargc());
    CHECKEND

    getInstance(Shader)->deactivate();
CEND(0)



reg shaderReg[]
{
    {"new", newShader},
    {"loadShader", loadS},
    {"make", makeS},
    {"activate", activateS},
    {"deactivate", deactivateS},
    {NULL, NULL}
};

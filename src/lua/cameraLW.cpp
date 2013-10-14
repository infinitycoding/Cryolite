#include <lua/script.h>
#include <camera.h>
#include <iostream>

#define CLASS camera

using namespace std;
/*

NEWBEGIN(newcamera)
    if(getargc() > 2)
        return luaL_error(L,"invalid number of arguents %d",getargc());

    double *x = addInstance(double);
    *x = 20;
NEWEND(CLASS)


CBEGIN(getcamposition)
    cout<<*((double *)luaL_checkudata(L, 0, "Camera"))<<endl;
    //lua_pop(L,1);
    //cout<<*getInstance(double*,"Camera")<<endl;
    //cout<<*getInstance(double*,"Camera")<<endl;
    return 0;
CEND


luaL_Reg cameraTable[]
{
    {"new", newcamera},
    {"getPosition", getcamposition},
    {NULL, NULL}
};
*/

#include <luaWrapper.h>



using namespace std;



LUASkript::LUASkript()
{
    initLUA();
}


LUASkript::LUASkript(const char *skriptname)
{
    initLUA();

    loadSkript(skriptname);
}


LUASkript::~LUASkript()
{
    lua_close(lState);
}


void LUASkript::initLUA()
{
    lState = luaL_newstate();
    luaL_openlibs(lState);
}


bool LUASkript::loadSkript(const char *skriptname)
{
    if (luaL_loadfile(lState, skriptname))
    {
        cerr << "the skript " << skriptname << " could not be loaded." << endl;
        cerr << lua_tostring(lState, -1) << endl;
        lua_pop(lState,1);
        return false;
    }

    return true;
}


bool LUASkript::runSkript()
{
    if (lua_pcall(lState,0, LUA_MULTRET, 0))
    {
        cerr << "an error has occured during the execution of some lua skript" << endl;
        cerr << lua_tostring(lState, -1) << endl;
        lua_pop(lState,1);
        return false;
    }

    return true;
}


double LUASkript::insertDoubleVar(const char *varname, double value)
{
    lua_pushnumber(lState, value);
    lua_setglobal(lState, varname);
    return value;
}


double LUASkript::getDoubleVar(const char *varname)
{
    lua_getglobal(lState, varname);
    double result = lua_tonumber(lState, -1);
    lua_pop(lState, 1);
    return result;
}

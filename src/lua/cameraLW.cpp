#include <lua/script.h>
#include <camera.h>


NEWBEGIN(newCamera)
    switch(getargc())
    {
        case 1:
            CONSTRUCT();
            addInstance(Camera *, new Camera());
        break;

        case 2:
        break;
    };
NEWEND(camera)




reg cameraReg[]
{
    {"new", newCamera},
    {NULL, NULL}
};

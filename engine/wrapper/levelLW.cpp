#include <lua/script.h>
#include <level.h>


CLASS
    FUNCTION(new_scene,addInstance(Level,Level()),1,true)
    FUNCTION(add_object,VOID getInstance(Level)->addObject(getInstance(Object)),2,istobjecttype(Object,ARG0) && istobjecttype(Level,ARG1))
    FUNCTION(add_cam,VOID getInstance(Level)->addCam(getInstance(Camera)),2,istobjecttype(Camera,ARG0) && istobjecttype(Level,ARG1))
    FUNCTION(render_scene,VOID getInstance(Level)->render(),1,istobjecttype(Level))
    FUNCTION(get_fps, LDBL(getInstance(Level)->fps->get()),1,istobjecttype(Level))

    ASSOCIATION(Level)
        ALIAS(new_scene,"new")
        ALIAS(add_object,"addObject")
        ALIAS(add_cam,"addCam")
        ALIAS(render_scene,"render")
        ALIAS(get_fps,"getFPS")
    ENDASSOCIATION
ENDCLASS
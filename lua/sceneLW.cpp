#include <lua/script.h>
#include <scene.h>


CLASS
    FUNCTION(new_scene,addInstance(Scene,Scene()),1,true)
    FUNCTION(add_object,VOID getInstance(Scene)->addObject(getInstance(Object)),2,istobjecttype(Object,ARG0) && istobjecttype(Scene,ARG1))
    FUNCTION(add_cam,VOID getInstance(Scene)->addCam(getInstance(Camera)),2,istobjecttype(Camera,ARG0) && istobjecttype(Scene,ARG1))
    FUNCTION(render_scene,VOID getInstance(Scene)->render(),1,istobjecttype(Scene))
    FUNCTION(get_fps, LDBL(getInstance(Scene)->fps->get()),1,istobjecttype(Scene))

    ASSOCIATION(Scene)
        ALIAS(new_scene,"new")
        ALIAS(add_object,"addObject")
        ALIAS(add_cam,"addCam")
        ALIAS(render_scene,"render")
        ALIAS(get_fps,"getFPS")
    ENDASSOCIATION
ENDCLASS




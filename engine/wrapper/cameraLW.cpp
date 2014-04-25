#include <lua/script.h>
#include <camera.h>



CLASS
    FUNCTION(new_camera, addInstance(Camera, Camera(NULL,vector(0,0,0),vector(0,0,0),1,10,90,0,0,480,640)), 1, true)

    FUNCTION(set_viewport_pos, VOID getInstance(Camera)->setViewportPos(LINT(), LINT()), 3, istype(int, ARG0) && istype(int, ARG1))
    FUNCTION(set_viewport_dim, VOID getInstance(Camera)->setViewportDim(LINT(), LINT()), 3, istype(int, ARG0) && istype(int, ARG1))
    FUNCTION(set_local_position, VOID getInstance(Camera)->localPosition.setvalue(LDBL(),LDBL(),LDBL()), 4, istype(int, ARG0) && istype(int, ARG1) && istype(int, ARG2) && istobjecttype(Camera));
    FUNCTION(set_fov, VOID getInstance(Camera)->fov=LDBL(), 2, istype(float, ARG0));

    FUNCTION(get_viewport_pos, LRET(2, Camera *c = getInstance(Camera); LINT(c->x); LINT(c->y)) , 1, istobjecttype(Camera))
    FUNCTION(get_viewport_dim, LRET(2, Camera *c = getInstance(Camera); LINT(c->height); LINT(c->width)), 1, istobjecttype(Camera))
    FUNCTION(get_local_position, LDAT(vector, getInstance(Camera)->localPosition), 1, istobjecttype(Camera))
    FUNCTION(get_position, LDAT(vector, getInstance(Camera)->getPosition()), 1, istobjecttype(Camera))
    FUNCTION(get_fov, LDBL(getInstance(Camera)->fov), 1, istobjecttype(Camera));


    ASSOCIATION(Camera)
        ALIAS(new_camera, "new")
        ALIAS(set_viewport_pos, "setViewportPos")
        ALIAS(set_viewport_dim, "setViewportDim")
        ALIAS(set_local_position, "setLocalPosition")
        ALIAS(set_fov, "setFOV")
        ALIAS(get_viewport_pos, "getViewportPos")
        ALIAS(get_viewport_dim, "getViewportDim")
        ALIAS(get_local_position, "getLocalPosition")
        ALIAS(get_position, "getPosition")
        ALIAS(get_fov, "getFOV")
    ENDASSOCIATION
ENDCLASS


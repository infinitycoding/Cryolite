#include <lua/script.h>
#include <light.h>


CLASS
    FUNCTION(new_lamp,addInstance(Lamp,Lamp()),1,true)
    FUNCTION(set_amb,VOID getInstance(Lamp)->setAmbientLight(LDBL(),LDBL(),LDBL(),LDBL()),5,(istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2) && istype(float,ARG3)))
    FUNCTION(set_dif,VOID getInstance(Lamp)->setDiffuseLight(LDBL(),LDBL(),LDBL(),LDBL()),5,(istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2) && istype(float,ARG3)))
    FUNCTION(set_spec,VOID getInstance(Lamp)->setSpecularLight(LDBL(),LDBL(),LDBL(),LDBL()),5,(istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2) && istype(float,ARG3)))
    FUNCTION(set_dir,VOID getInstance(Lamp)->setDirection(vector(LDBL(),LDBL(),LDBL())),4,(istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2)))
    FUNCTION(set_pos,VOID getInstance(Lamp)->setPosition(vector(LDBL(),LDBL(),LDBL())),4,(istype(float,ARG0) && istype(float,ARG1) && istype(float,ARG2)))
    FUNCTION(update_lamp,VOID getInstance(Lamp)->refreshPosition(),1,true)
    FUNCTION(activat_lamp, VOID getInstance(Lamp)->activate(),1,true)
    FUNCTION(deactivate_lamp, VOID getInstance(Lamp)->deactivate(),1,true)
    FUNCTION(dir_lamp, VOID getInstance(Lamp)->directed(LBOOL()),2,true)
    FUNCTION(is_dir,LRET(1); LDBL(getInstance(Lamp)->isDirected()),1,true)
    FUNCTION(set_exp, VOID getInstance(Lamp)->setExponent(LDBL()),2,istype(float,ARG0))
    FUNCTION(set_cut, VOID getInstance(Lamp)->setCutOf(LDBL()),2,istype(float,ARG0))
    FUNCTION(set_const_att, VOID getInstance(Lamp)->setConstAttenaution(LDBL()),2,istype(float,ARG0))
    FUNCTION(set_lin_att, VOID getInstance(Lamp)->setLinAttenaution(LDBL()),2,istype(float,ARG0))
    FUNCTION(set_quad_att, VOID getInstance(Lamp)->setQuadAttenaution(LDBL()),2,istype(float,ARG0))
    FUNCTION(std_light, VOID getInstance(Lamp)->setStandart(),1,true)
    FUNCTION(refresh_light, VOID getInstance(Lamp)->refresh(),1,true)

    ASSOCIATION(Lamp)
        ALIAS(new_lamp,"new")
        ALIAS(set_amb,"setAmb")
        ALIAS(set_dif,"setDiff")
        ALIAS(set_spec,"setSpec")
        ALIAS(set_dir,"setDir")
        ALIAS(set_pos,"setPos")
        ALIAS(update_lamp,"updatePos")
        ALIAS(activat_lamp,"enable")
        ALIAS(deactivate_lamp,"disable")
        ALIAS(dir_lamp,"setDir")
        ALIAS(is_dir,"isDir")
        ALIAS(set_exp,"setExp")
        ALIAS(set_cut,"setCutof")
        ALIAS(set_const_att,"setConstAtt")
        ALIAS(set_lin_att,"setLinAtt")
        ALIAS(set_quad_att,"setQuadAtt")
        ALIAS(std_light,"setDefault")
        ALIAS(refresh_light,"refresh")

    ENDASSOCIATION

ENDCLASS

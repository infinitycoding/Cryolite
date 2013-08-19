#ifndef PHYSICSPROPERTY_H
#define PHYSICSPROPERTY_H

#include <vector.h>

class PhysicsProperty
{
    public:
        PhysicsProperty(bool gravity, float constant, float mass, vector anchor);
        virtual ~PhysicsProperty();

        bool gravityEnabled;

        float mass;
        float g;

        vector rotationAnchor;

        vector ds;
        vector dv;

        vector ds_prev;
        vector dv_prev;

        vector w;
        vector dw;

        vector w_prev;
        vector dw_prev;

        vector tick_acceleration;
        vector tick_angular;

        void update();

        void addForce(vector v);
        void addAngularForce(vector w);
        void resetForces();
        void changeAnchor(vector newAnchor);

        vector getV();
        vector getA();
        vector getW();
        vector getDW();

};

#endif // PHYSICSPROPERTY_H

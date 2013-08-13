#include "PhysicsProperty.h"

PhysicsProperty::PhysicsProperty(bool gravity, float constant, float m, vector anchor)
{
    this->gravityEnabled = gravity;

    this->mass = m;
    this->g = constant;

    this->rotationAnchor = anchor;

    this->ds = vector();
    this->dv = vector();

    this->ds_prev = vector();
    this->dv_prev = vector();

    this->w = vector();
    this->dw = vector();

    this->w_prev = vector();
    this->dw_prev = vector();
}

PhysicsProperty::~PhysicsProperty()
{

}



void PhysicsProperty::update()
{
    if(!(tick_acceleration.x == 0 && tick_acceleration.y == 0 && tick_acceleration.z == 0))
    {
        ds_prev = ds;
        dv_prev = dv;
    }

    if(!(tick_angular.x == 0 && tick_angular.y == 0 && tick_angular.z == 0))
    {
        w_prev = w;
        dw_prev = dw;
    }

    tick_acceleration += mass * g * vector(0, -1, 0);

    dv = (tick_acceleration.len() / mass) * tick_acceleration.unifyc();

    ds = ds_prev + dv;

    dw = tick_angular;

    w = w_prev + dw;

    resetForces();

}



void PhysicsProperty::addForce(vector v)
{
    tick_acceleration.addc(v);
}

void PhysicsProperty::addAngularForce(vector w)
{
    tick_angular.addc(w);
}

void PhysicsProperty::resetForces()
{
    tick_acceleration.null();
    tick_angular.null();
}

void PhysicsProperty::changeAnchor(vector newAnchor)
{
    this->rotationAnchor = newAnchor;
}



vector PhysicsProperty::getV()
{
    return ds;
}

vector PhysicsProperty::getA()
{
    return dv;
}

vector PhysicsProperty::getW()
{
    return w;
}

vector PhysicsProperty::getDW()
{
    return dw;
}

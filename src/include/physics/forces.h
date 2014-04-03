#ifndef FORCES_H_INCLUDED
#define FORCES_H_INCLUDED



#include <vector.h>



typedef vector force_t;



// Force types to implement:
// - gravitation (point)
// - supporting force
// - friction
// - centripetal force
// - viscosity
// - pressure
// - constant forces        #finished



enum forceBasicType
{
    simpleForce,
    dependingForce,
    opposingForce,
    complexForce,
    otherForce
};


enum forceType
{
    simple = simpleForce,
    depending = dependingForce,
    opposing = opposingForce,
    complex = complexForce,
    other = otherForce,
    constantForce = simpleForce,
    centripetalForce = dependingForce,
    pointGravitation = dependingForce,
    supportingForce = opposingForce,
    friction = opposingForce,
    viscosity = opposingForce,
    pressure = complexForce
};



class Force
{
    public:
        Force();
        virtual ~Force();

        virtual forceType type();
};


class SimpleForce : public Force
{
    public:
        SimpleForce();
        SimpleForce(force_t startForce);
        virtual ~SimpleForce();

        virtual forceType type();

        virtual force_t setBaseForce(force_t newForce);
        virtual force_t getBaseForce();

        virtual force_t getForce();

    protected:
        force_t baseForce;
};


class DependingForce : public Force
{
    public:
        DependingForce();
        virtual ~DependingForce();

        virtual forceType type();
};


class OpposingForce : public Force
{
    public:
        OpposingForce();
        virtual ~OpposingForce();

        virtual forceType type();
};


class ComplexForce : public Force
{
    public:
        ComplexForce();
        virtual ~ComplexForce();

        virtual forceType type();
};


class ConstantForce : public SimpleForce
{
    public:
        ConstantForce();
        ConstantForce(force_t startForce);
        virtual ~ConstantForce();

        virtual forceType type();

        virtual force_t setBaseForce(force_t newForce);
        virtual force_t getBaseForce();

        virtual force_t getForce();
};


class CentripetalForce : public DependingForce
{

};


class PointGravitation : public DependingForce
{

};


class SupportingForce : public OpposingForce
{

};


class Friction : public OpposingForce
{

};


class Viscosity : public OpposingForce
{

};


class Pressure : public ComplexForce
{

};



#endif

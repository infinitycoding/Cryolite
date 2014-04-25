#include <physics/forces.h>



Force::Force()
{

}


Force::~Force()
{

}


forceType Force::type()
{
    return other;
}



SimpleForce::SimpleForce()
{
    baseForce = vector();
}


SimpleForce::SimpleForce(force_t startForce)
{
    baseForce = startForce;
}


SimpleForce::~SimpleForce()
{

}


forceType SimpleForce::type()
{
    return simple;
}


force_t SimpleForce::setBaseForce(force_t newForce)
{
    return (baseForce = newForce);
}


force_t SimpleForce::getBaseForce()
{
    return baseForce;
}


force_t SimpleForce::getForce()
{
    return vector();
}



DependingForce::DependingForce()
{

}


DependingForce::~DependingForce()
{

}


forceType DependingForce::type()
{
    return depending;
}



OpposingForce::OpposingForce()
{

}


OpposingForce::~OpposingForce()
{

}


forceType OpposingForce::type()
{
    return opposing;
}



ComplexForce::ComplexForce()
{

}


ComplexForce::~ComplexForce()
{

}


forceType ComplexForce::type()
{
    return complex;
}



ConstantForce::ConstantForce()
{

}


ConstantForce::ConstantForce(force_t startForce) : SimpleForce(startForce)
{

}


ConstantForce::~ConstantForce()
{

}


forceType ConstantForce::type()
{
    return constantForce;
}


force_t ConstantForce::setBaseForce(force_t newForce)
{
    return (baseForce = newForce);
}


force_t ConstantForce::getBaseForce()
{
    return baseForce;
}


force_t ConstantForce::getForce()
{
    return baseForce;
}

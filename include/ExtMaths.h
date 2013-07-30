#ifndef EXTMATH_H
#define EXTMATH_H

enum Fkttype
{
    none = 0, potential = 1, trigonometric, exponential, logaritmic
};
class Funct
{
    public:

    Funct(Fkttype initTyp, double initBase, double initFmodul);

    double calculate(double Xvalue);
    void integrate();
    void derive();

    Fkttype Typ;
    double Base, Fmodul;

};



#endif

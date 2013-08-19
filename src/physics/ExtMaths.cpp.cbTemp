#include <ExtMaths.h>
#include <math.h>

using namespace std;


const double e = exp(1);

Funct::Funct(Fkttype initTyp, double initBase, double initFmodul)
{
    Typ = initTyp;
    Base = initBase;
    Fmodul = initFmodul;
    if(!Fmodul)Typ = none;
}

double Funct::calculate(double Xvalue)
{
    switch(Typ)
    {
        case none : return 0;break;
        case potential : return Fmodul * pow(Xvalue, Base);break;
        case trigonometric : switch(static_cast<int>(Base))
                            {
                                case 0 : return Fmodul * sin(Xvalue);break;
                                case 1 : return Fmodul * cos(Xvalue);break;
                                case 2 : return Fmodul * asin(Xvalue);break;
                                case 3 : return Fmodul * acos(Xvalue);break;
                            };break;
        case exponential : return Fmodul * pow(Base, Xvalue);break;
        case logaritmic : return Fmodul * log10(Xvalue)/log10(Base);break;
    }
    return 0;
}


void Funct::derive()
{
    switch(Typ)
    {
        case none : return;
        case potential :{
                        Fmodul = Fmodul * Base;
                        Base-- ;
                        if(!Fmodul)Typ = none;
                        };break;
        case trigonometric : switch(static_cast<int>(Base))
                            {
                                case 0 : Base = 1;break;
                                case 1 :{
                                        Base =0;
                                        Fmodul = -Fmodul;
                                        };break;
                              /*case 2 :
                                case 3 :*/
                            };break;
        case exponential :{
                          Fmodul = Fmodul * log(Base);
                          };break;
        case logaritmic  :{/*wip*/};break;
    };
}

void Funct::integrate()
{
    switch(Typ)
    {
        case none : return;
        case potential : {if (Base != 1){
                            ++Base;
                            Fmodul = Fmodul / Base;
                        }
                        else Typ = logaritmic;
                        };break;
        case trigonometric : switch(static_cast<int>(Base))
                            {
                                case 0 :
                                    {
                                        Base = 1;
                                        Fmodul = - Fmodul;
                                    };
                                case 1 :
                                    {
                                        Base = 0;
                                    };
                              /*case 2 :
                                case 3 : */
                            };break;
        case exponential :
                        {
                            Fmodul = Fmodul / log(Base);
                        };break;
        case logaritmic : {/*WIP*/};break;
    };
}

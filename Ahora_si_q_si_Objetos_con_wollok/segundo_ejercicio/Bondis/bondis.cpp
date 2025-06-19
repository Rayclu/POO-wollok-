#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <ctime>

#include "paradas.cpp"
using namespace std;

class bondi
{
    private:
        const int MaxPasajeros = 150;
        const int VelocicadMaxima = 120;
        const int CapacidadTanque = 200;
        bool LimitePasajeros;

    public:
        bondi(/* args */);
        ~bondi();
};

bondi::bondi(/* args */)
{
}

bondi::~bondi()
{
}

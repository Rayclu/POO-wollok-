#ifndef LANZADOR_H
#define LANZADOR_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include "babosas.h"
#include <variant>
#include <unistd.h>

using namespace std;

class lanzador{
    private:
        string arm; // Arma del usr
        string species; // Especie elegida por el usr.
        vector<string> PossibleArms = {"Pistol", "Shotgun", "DoubleShoot", "minigun", "Sniper"};
        vector<string> PossibelSpecies = {"Human", "Topo", "Troll", "Flajelo"};
        babosa *nextSlug; // Proxima babosa a dispararse.
        void relectArm(); 
        
    public:
        string name; // Nombre que se puso el usr
        int health; // Vida del usr, por ahora está como un dato más, la idea es que luego pueda bajar con cada disparo recibido
        friend  ostream& operator<<(ostream& os, const lanzador& l);
        int evasivness = 5; // porcentaje de esquivacion.
        vector<babosa*> arsenal; // Babosas del usr.
        lanzador(
            vector<babosa*> arsenal,
            string name,
            string arm,
            string species
         );
        int charge();
        bool ChargedSlug;
        pair<int, bool> disparar();
        ~lanzador();
};




#endif
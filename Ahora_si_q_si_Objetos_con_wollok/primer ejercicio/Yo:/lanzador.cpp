#include <vector>
#include <iostream>
#include <string>
#include "babosas.h"
#include <unistd.h> // Para la función sleep
#include <variant>
using namespace std;

class lanzador{
    private:
        string name; // Nombre que se puso el usr
        string arm; // Arma del usr
        string species; // Especie elegida por el usr.
        vector<string> PossibleArms = {"Pistol", "Shotgun", "DoubleShoot", "minigun", "Sniper"};
        vector<string> PossibelSpecies = {"Human", "Topo", "Troll", "Flajelo"};
        babosa *nextSlug; // Proxima babosa a dispararse.
        void relectArm(); 
        
    public:
        int health; // Vida del usr, por ahora está como un dato más, la idea es que luego pueda bajar con cada disparo recibido
        friend  ostream& operator<<(ostream& os, const lanzador& l);
        vector<babosa*> arsenal; // Babosas del usr.
        lanzador(
            vector<babosa*> arsenal,
            string name,
            string arm,
            string species
         );
        void charge();
        bool ChargedSlug;
        pair<int, bool> disparar();
        ~lanzador();
};

ostream& operator<<(ostream& os, const lanzador& l) {
    /*
    Metodo que UNICAMENTE está hecho para pruebas, o sea, sobrecarga el 'cout' para poder mostrar el objeto en la terminal.
    La idea es que luego se pueda mostrar el arsenal con el que se cuenta, pero ya la comuniocacion es posible pues compíla y recibe las ba-
    bosas hardcodeadas, proximo objetivo que se ingresen mediante terminal.
    */
    os << "Nombre: " << l.name << "\n";
    os << "Especie: " << l.species << "\n";
    os << "Arma: " << l.arm << "\n";
    os << "Vida: " << l.health << "\n";
    os << "Arsenal:\n";
    return os;
}

lanzador:: lanzador(
    vector<babosa*> arsenal,
    string name,
    string arm,
    string species
) {
    this->arsenal = arsenal;
    this->name = name;
    this->arm = arm;
    this->nextSlug = nullptr;
    this->species = species; 
    if (this->species == "Human"){
            this->health = 100;
            if(this->arm == "minigun" || this->arm == "Sniper"){
                cout << "El humano no puede usar minigun o snipers, se le asignará una pistola" << endl;
                this->relectArm();
            }
    } else if (this->species == "Topo"){
            this->health = 80;
            if(this->arm == "DoubleShoot" || this->arm == "Minigun"){
                cout << "El topo no puede usar este arma, se le asignará un francotirador" << endl;
                this->relectArm();
            }
    } else if(this->species == "Troll"){
            this->health = 150;
            if(this->arm == "Pistol" || this->arm == "Doubleshoot"){
                cout << "El troll no puede usar pistola, se le asignará una escopeta" << endl;
                this->relectArm();
            }
        } else{
            this->health = 170;
            if(this->arm != "minigun"){
                cout << "El flajelo solo puede usar la minigun, se le asignará la misma" << endl;
                this->arm = "minigun";
            
            }
        }

}
void lanzador::relectArm(){
    if(this->species == "Human"){
        cout << "Elija un nuevo arma <0:pistol, 1:Doubleshoot>" <<endl;
        int arm;
        cin >> arm;
        switch (arm){
        case 0:
            this->arm = "pistol";
            break;
        case 1: 
            this->arm = "Doubleshoot";
            break;
        default: 
            cout << "sos bolud@? ARMA INVALIDA" << endl;
            break;
        }
    }else if ( this->species == "Troll" ){
        cout << "Elija un nuevo arma <0:minigun, 1:shotgun>" <<endl;
        int arm;
        cin >> arm;
        switch (arm){
        case 0:
            this->arm = "Minigun";
            break;
        case 1: 
            this->arm = "Shotgun";
            break;
        default: 
            cout << "sos bolud@? ARMA INVALIDA" << endl;
            break;
        }
    }else if ( this->species == "Topo" ){
        cout << "Elija un nuevo arma <0:sniper, 1:pistol, 2:Doubleshoot>" <<endl;
        int arm;
        cin >> arm;
        switch (arm){
        case 0:
            this->arm = "Sniper";
            break;
        case 1: 
            this->arm = "Pistol";
            break;
        case 2:
            this->arm = "Doubleshoot";
            break; 
        default: 
            cout << "sos bolud@? ARMA INVALIDA" << endl;
            break;
        }
    }
    
}
void lanzador::charge() {
    cout << "Cargando el arma..." << endl;
    sleep(3);
    if(!this->arsenal.empty()){
        this->nextSlug = this->arsenal.front();
        this->arsenal.erase(this->arsenal.begin());
    }else{
        cout << "No hay mas babosas en el arsenal, Fin." << endl;
    }
    this->ChargedSlug = true;
    cout << "Arma cargada!" << endl;
}

pair<int, bool> lanzador::disparar(){
    charge();
    if(this->nextSlug == nullptr) return {-1, false};
    int assert = rand() % 101;
    bool usrHitTheShoot = assert <= 50 ? true : false ; 
    cout << "Que quieres hacer, atacar, defender o utilidades <0,1 o 2 respectivamente>" << endl;
    int mov;
    cin >> mov;
    pair<string, int> mate;
    switch (mov){
        case 0:
            mate = this->nextSlug->Ataques();
            break;
        case 1:
            mate = this->nextSlug->Defensa();
             
            break;
        case 2:
            mate = this->nextSlug->MovUtilidad();
            break;
        
        default:
            cout << "Tipo de movimiento invalido" << endl;
            break;
        }
    
    
    return {0, usrHitTheShoot};
}

lanzador::~lanzador() {
    for (babosa* slug : this->arsenal) {
        delete slug;
    }
    if (this->nextSlug != nullptr) {
        delete this->nextSlug;
    }
}

int main(int argc, char const *argv[]){ 
    // Los  argumentos de esta funcion no se usan pues la declaré con la plantilla
    // y ya venían implementados, y al quitarlos tira error, debo
    // ver que está pasando con eso xDD. 

    //%%%%%%%%%%%%%%%%%%%%%%%%_Arsenal 1_%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    vector<babosa*> arsenal = {
        new babosa(true, "Inferno", 150,
            vector<pair<string, int>>{
                    {"Fireball", 100},
                    {"Firestorm", 200},
                    {"Flame Burst", 150}
            },
            vector<pair<string, int>>{
                    {"Wall of fire", 40}
            },
            vector<pair<string, int>>{
                    {"Fly", 10000000}
            }
        ),
        new babosa(false, "arañita", 59,
            vector<pair<string, int>>{
                    {"Trampaña", 0},
                    {"AracniCeguera", 200},
            },
            vector<pair<string, int>>{
                    {"inmovilizar", 60}
            },
            vector<pair<string, int>>{
                    {"Columpio Aracnido", 20000000}
            }
        ),
        new babosa(false, "Jules", 150,
            vector<pair<string, int>>{
                    {"Trueno", 150},
                    {"Cortocircuito", 500}
            },
            vector<pair<string, int>>{
                    {"Destello", 40}
            },
            vector<pair<string, int>>{
                    {"Electricidad", 100}
            }
        )
    };
 
    // Lanzador 1 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    lanzador EliShane( 
        arsenal, "Eli Shane", "pistol", "Human"
    );
    //------------------------------------------Babosa4
    babosa InfernoNormal(
        false, "Inferno", 150,
        vector<pair<string, int>>{
                {"Fireball", 100},
                {"Firestorm", 200},
                {"Flame Burst", 150}
        },
        vector<pair<string, int>>{
                {"Wall of fire", 40}
        },
        vector<pair<string, int>>{
                {"Fly", 10000000}
        }
    );
    //------------------------------------------Babosa5
    babosa AracniredMalvada(
        true, "arañita", 59,
        vector<pair<string, int>>{
                {"Trampaña", 0},
                {"AracniCeguera", 200}
        },
        vector<pair<string, int>>{
                {"inmovilizar", 60}
        },
        vector<pair<string, int>>{
                {"Columpio Aracnido", 20000000}
        }
    );
    //------------------------------------------Babosa6
    babosa ElectroshcokMalvada(
        true, "Jules", 150,
        vector<pair<string, int>>{
                {"Trueno", 150},
                {"Cortocircuito", 500}
        },
        vector<pair<string, int>>{
                {"Destello", 40}
        },
        vector<pair<string, int>>{
                {"Electricidad", 100}
        }
    );
    //%%%%%%%%%%%%%%%%%%%%%%%%_Arsenal 2_%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    vector<babosa*> arsenal2 = {
        new babosa(false, "Inferno", 150,
            vector<pair<string, int>>{
                    {"Fireball", 100},
                    {"Firestorm", 200},
                    {"Flame Burst", 150}
            },
            vector<pair<string, int>>{
                    {"Wall of fire", 40}
            },
            vector<pair<string, int>>{
                    {"Fly", 10000000}
            }
        ),
        new babosa(true, "arañita", 59,
            vector<pair<string, int>>{
                    {"Trampaña", 0},
                    {"AracniCeguera", 200},
            },
            vector<pair<string, int>>{
                    {"inmovilizar", 60}
            },
            vector<pair<string, int>>{
                    {"Columpio Aracnido", 20000000}
            }
        ),
        new babosa(true, "Jules", 150,
            vector<pair<string, int>>{
                    {"Trueno", 150},
                    {"Cortocircuito", 500}
            },
            vector<pair<string, int>>{
                    {"Destello", 40}
            },
            vector<pair<string, int>>{
                    {"Electricidad", 100}
            }
        )
    };
    // Lanzador 2 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    lanzador Pronto(
        arsenal2, "Pronto", "Sniper", "Topo"
    );
        // Imprimir lanzador
    cout << EliShane << endl;

    // if(EliShane.ChargedSlug){
    //     EliShane.disparar();
    // }else if(EliShane.arsenal.empty()){
    //     EliShane.health = 0;
    // }

    // Imprimir una babosa específica
    //cout << *arsenal[0] << endl;

    cout << Pronto << endl;
    //cout << *arsenal2[0] << endl;
    do{
        
        int FirstShoot = rand() % 2;
        
        if(FirstShoot == 1){
            pair<int, bool> res = Pronto.disparar();
           // res.second ? EliShane.health-= damage : null;
        }
    } while ( EliShane.health >= 1 && Pronto.health >= 1 );
    
    return 0; // Aviso que el programa se ejecutó correctamente.
}

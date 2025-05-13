#include <vector>
#include <iostream>
#include <string>
#include "babosas.h"
#include <unistd.h> // Para la función sleep
#include <variant>
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
int lanzador::charge() {
    cout << "Cargando el arma..." << endl;
    sleep(3);
    if(!this->arsenal.empty()){
        this->nextSlug = this->arsenal.front();
        this->arsenal.erase(this->arsenal.begin());
    }else{
        cout << "No hay mas babosas en el arsenal, Fin." << endl; 
        int endOfProgram = -1;
        return endOfProgram;
    }
    this->ChargedSlug = true;
    cout << "Arma cargada!" << endl;
    return 0;
}

pair<int, bool> lanzador::disparar(){
    int res_charge = charge();
    if (res_charge != 0) return {-2, false};
    if(this->nextSlug == nullptr) return {-1, false};
    int assert = this->species == "Human" ? rand() % 101 : (this->species == "Flajelo" || this->species == "Troll" ? rand()% 200 : rand() % 75 );
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
    
    
    return {mate.second, usrHitTheShoot};
}

lanzador::~lanzador() {
    for (babosa* slug : this->arsenal) {
        delete slug;
    }
    if (this->nextSlug != nullptr) {
        delete this->nextSlug;
    }
}

int endingVersus(lanzador& lanzador1, lanzador& lanzador2){
    int health_1 = lanzador1.health; int health_2 = lanzador2.health;
    if (health_1 < health_2) return 1;
    if (health_2 < health_2) return 2;
    return -1;
}
int main(int argc, char const *argv[]){ 
    // Los  argumentos de esta funcion no se usan pues la declaré con la plantilla
    // y ya venían implementados, y al quitarlos tira error, debo
    // ver que está pasando con eso xDD. 

    //%%%%%%%%%%%%%%%%%%%%%%%%_Arsenal 1_%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    vector<babosa*> arsenal = {
        new babosa(true, "Inferno", rand()%210,
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
        new babosa(false, "arañita", rand() % 210,
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
        new babosa(false, "Jules", rand() % 210,
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
        false, "Inferno", rand() % 210,
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
        true, "arañita", rand() % 210,
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
        true, "Jules", rand() %210,
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
        new babosa(false, "Inferno", rand() % 210,
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
        new babosa(true, "arañita", rand() % 210,
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
    // Imprimir una babosa específica
    //cout << *arsenal[0] << endl;

    cout << Pronto << endl;
    //cout << *arsenal2[0] << endl;
    do{
        
        int FirstShoot = rand() % 2;
        cout << FirstShoot << "\n" << endl;
        int evasivness = rand() % 10;
        if(FirstShoot == 1){ // Dispara pronto, Eli pierde vida si es que no consigue esquivar
            pair<int, bool> res = Pronto.disparar(); // desenpaqueto lo devuelto por el metodo disparar (pair<int, bool>)
            if (res.first == -2) {
                cout << "A" << Pronto.name << "no le quedan babosas que disparar. Fin" << endl;
                break;

            };
           // Debug _________________________________________________________________________________________________________________________________
            // string out = res.second ? "Acierto \0" : "Fallo \0"; // verifico que se haya acertado el disparo.
            // cout << "El resultado el disparo fué: " << out << "\nCon un resultado de: "<< res.second << endl; // Imprimo el resultado
            //_____________________________________________________________________________________________________________________________________
            if(res.second){ 
                if(evasivness <= EliShane.evasivness ){ // Si la evasion es menor a el entero definida en la propidad
                    EliShane.health -= res.first; // Prota1 pierde vida
                    cout << "La vida de Eli bajó a:" << EliShane.health << endl; // Muestro por terminal a cuanto bajo la vida
                } else {
                    cout << "El disparo fué esquivado..." << endl;
                }
                // cout << Pronto.health << endl;
                
            }
        }else{ // viceversa
            pair<int, bool> res = EliShane.disparar(); 
            if (res.first == -2) {
                cout << "A " << EliShane.name << " no le quedan babosas que disparar. Fin" << endl;
                break;
            };
            if(res.second){
                if( evasivness <= Pronto.evasivness){
                    Pronto.health -= res.first;
                    cout << "La vida de Pronto bajó a:" << Pronto.health << endl;
                } else {
                    cout << "El disparo fué esquivado" << endl;
                }
            }
            
        }
    }while( EliShane.health >= 1 && Pronto.health >= 1 );
    int winner = endingVersus(Pronto, EliShane);
    switch (winner){
        case 1:
            cout << "Pronto gana." << endl;
            return 0;
    
        case 2: 
            cout << "Eli gana." << endl;
            return 0; 
        default:
            cout << "Empate" << endl;
            return -1; // xD
    }
    
    
    //return 0; // Aviso que el programa se ejecutó correctamente.
}
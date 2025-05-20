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
    /**
     * Constructor. 
     */

    this->arsenal = arsenal; // vector en el que se guardarán las babosas disponibles
    this->name = name; // nombre del usr
    this->arm = arm; // arma elegida
    this->nextSlug = nullptr; // Babosa a disparar
    this->species = species; // Especie que se ha elegido, topoide, humano, trol, etc.

    if (this->species == "Human"){  // ** Caracteristicas del humano ** || Probable sub-objeto
            this->health = 100; 
            if(this->arm == "minigun" || this->arm == "Sniper"){
                cout << "El humano no puede usar minigun o snipers, se le asignará una pistola" << endl;
                this->relectArm();
            }
    } else if (this->species == "Topo"){  //  ** Caracteristicas del topo ** || Probable sub-objeto
            this->health = 80;
            if(this->arm == "DoubleShoot" || this->arm == "Minigun"){
                cout << "El topo no puede usar este arma, se le asignará un francotirador" << endl;
                this->relectArm();
            }
    } else if(this->species == "Troll"){  // ** Caracteristicas del trol ** || sub-objeto.
            this->health = 150;
            if(this->arm == "Pistol" || this->arm == "Doubleshoot"){
                cout << "El troll no puede usar pistola, se le asignará una escopeta" << endl;
                this->relectArm();
            }
    } else{  //  ** Caracteristicas del flajelo **  || sub-objeto
            this->health = 170;
            if(this->arm != "minigun"){
                cout << "El flajelo solo puede usar la minigun, se le asignará la misma" << endl;
                this->arm = "minigun";
            
            }
        }
}
 
void lanzador::relectArm(){ 
    //  **Funcion para reasignar el arma del lanzador si es que es 
    //  *incompatible con el mismo
    if(this->species == "Human"){
        cout << "Elija un nuevo arma <0:pistol, 1:Doubleshoot>" <<endl; 
        int arm;
        cin >> arm; //  pedir una de las armas dadas a elegir
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
        cout << "Elija un nuevo arma <0:sniper, 1:pistol, 2:Doubleshoot>" << endl;
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

    if(!this->arsenal.empty()){ // si el arsenal no está vacío inserto una nueva babosa en el cargador
        this->nextSlug = this->arsenal.front();
        this->arsenal.erase(this->arsenal.begin()); // y la elimino del arsenal :) .

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
    /**
     * Esta funcion dispara a la babosa como tal, su resultado es un conjunto entre un 
     * entero y un booleano pues el primero refiere a el daño hecho y el segundo si el
     * tiro debió de impactar en el rival. 
     * Cabe aclarar que se puden tnerexepciones como que por ejemplo no queden babosas en
     * el arsenal, en esos casos se devuelve -2 indicando este posible caso.
    */

    int res_charge = charge();
    if (res_charge != 0) return {-2, false}; // Si no quedan babosas. 
    if(this->nextSlug == nullptr) return {-1, false}; // Si se produjo un error interno.

    /**
     * Rangos en los que puede caer el numero de apuntado del usr (si supera los 50 no se lo considera como acertado) 
     * topo : 0, 75,
     * flajelo : 0, 200
     * troll : 0, 200
     * humano : 0, 100
     */
    
    int assert = this->species == "Human" ? rand() % 101 : (
        this->species == "Flajelo" || this->species == "Troll" ? rand()% 201 : rand()% 76
    ); // Segun la especie, asigno un chance de acertar el disparo

    bool usrHitTheShoot = assert <= 50 ? true : false ; 
    cout << "Que quieres hacer, atacar, defender o utilidades <0,1 o 2 respectivamente>" << endl;
    
    int mov; 
    cin >> mov; // input
    pair<string, int> mate; // variable en la que se guardará la data del disparo proveniente de la babosa
    switch (mov){ // posibles casos de uso.
        case 0:
            cout << "Se hará un movimiento ofensivo." << endl;
            mate = this->nextSlug->Ataques();
            break;
        case 1:
            cout << "Se hará un movimiento defensivo." << endl;
            mate = this->nextSlug->Defensa();
             
            break;
        case 2:
            cout << "Se hará un movimiento de utilidad no espere hacer daño." << endl;
            mate = this->nextSlug->MovUtilidad();
            break;
        
        default:
            cout << "Tipo de movimiento invalido" << endl;
            break;
    }
    cout << "Daño:" <<  mate.second << endl;
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
                {"Trampaña", 100},
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
                    {"Trampaña", 100},
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
        // cout << FirstShoot << "\n" << endl;
        int evasivness = rand() % 10;
        //  ----------------------------------------------------  Dispara pronto, Eli pierde vida ------------------
        if(FirstShoot == 1){ 
            cout << "###########################" << "\n" << "Dispara pronto pierde vida Eli: " << endl;
            pair<int, bool> res = Pronto.disparar(); // desenpaqueto lo devuelto por el metodo disparar (pair<int, bool>)
            if(res.first == 0){
                cout << "Mala suerte. Tu ataquee justamente, no hace daño xD" << endl;
            }
            if (res.first == -2) {
                cout << "A" << Pronto.name << "no le quedan babosas que disparar. Fin" << endl;
                break;

            };
           
            cout << "debug:" << "\n" << "\t Esquivado:\n\t\t" << evasivness << endl;
            if(res.second){ 
                if(evasivness <= EliShane.evasivness ){ // Si la evasion es menor a el entero definida en la propidad
                    cout << "debug:" << "\n" << "\t Res_disparo (Pronto ataca):\n\t\t" << res.first << endl;
                    EliShane.health -= res.first; // Prota1 pierde vida
                    cout << "La vida de Eli bajó a:" << EliShane.health << endl; // Muestro por terminal a cuanto bajo la vida
                } else {
                    cout << "El disparo fué esquivado..." << endl;
                }
                // cout << Pronto.health << endl;
                
            }
        }else{ // viceversa
            cout << "###########################" << "\n" << "Dispara Eli, pierde vida Pronto: " << endl;

            pair<int, bool> res = EliShane.disparar(); 
            if (res.first == -2) {
                cout << "A " << EliShane.name << " no le quedan babosas que disparar. Fin" << endl;
                break;
            };
            cout << "debug:" << "\n" << "\t Acierto (Pronto):\n\t\t" << res.second << endl;
            if(res.second){
                if( evasivness <= Pronto.evasivness){
                    Pronto.health -= res.first;
                    cout << "debug:" << "\n" << "\t Res_disparo (Eli ataca):\n\t\t" << res.first << endl;

                    cout << "La vida de Pronto bajó a:" << Pronto.health << endl;
                } else {
                    cout << "El disparo fué esquivado" << endl;
                }
            }
            
        }
    }while( EliShane.health >= 1 && Pronto.health >= 1 && !Pronto.arsenal.empty() && !EliShane.arsenal.empty() );
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

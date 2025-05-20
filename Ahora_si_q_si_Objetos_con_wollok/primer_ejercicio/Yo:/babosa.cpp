#include <vector>
#include <string>
//#include <map>
#include <malloc.h>
#include <cstdlib> // Para rand()
#include <stdio.h>
#include <iostream>

using namespace std;
/*typedef struct {
            string nombre;
            vector<pair<string, int>> attack_moves;
            vector<pair<string, int>> defense_moves;
            vector<pair<string, int>> utilities; // Corregido: utilities
            int speed;
            bool isEvil;
        } Slug;*/

class babosa {
    private:
        string nombre;
        vector<pair<string, int>> attack_moves; // Movimientos de ataque
        vector<pair<string, int>> defense_moves; // Movimientos de defensa
        vector<pair<string, int>> utilities; // Movimientos de utilidad
        int speed; // Velocidad de la babosa
        bool isEvil; // Indica si la babosa es malvada o no

        pair<string, int> GetRandomMove(int PlusMove,const vector<pair<string, int>> &moves);
        
        
    public:
        static constexpr int VELOCIMORPHISMO = 120; // Velocidad que necesitan las babosas para transformarse
        static constexpr int MEGAMORPHISMO = 200; // Velocidad que necesitan las babosas para sufrir la megamorfosis
        babosa(
            bool isEvil, string slugName,int speed,
            vector<pair<string, int>> attack_moves,
            vector<pair<string, int>> defense_moves,
            vector<pair<string, int>> utilities
        );
        pair<string, int> Disparo(const vector<pair<string, int>> move);
        pair<string, int> Ataques();
        pair<string, int> Defensa();
        pair<string, int> MovUtilidad();
        //babosa& operator=(const babosa& other);
        ~babosa();
};

babosa::babosa(bool isEvil, string slugName, int speed,
            vector<pair<string, int>> attack_moves,
            vector<pair<string, int>> defense_moves,
            vector<pair<string, int>> utilities
        ) {
    this->nombre = slugName;
    this->attack_moves = attack_moves;
    this->defense_moves = defense_moves;
    this->utilities = utilities;
    this->speed = speed;
    this->isEvil = isEvil;
}


babosa::~babosa(){
}

pair<string, int> babosa::GetRandomMove(int PlusMove,const vector<pair<string, int>> &moves){
    if (moves.empty()) return {"", -1};
    int options = moves.size();
    int Idx = rand() % options;

    return {moves[Idx].first, moves[Idx].second * PlusMove};

}


pair<string, int> babosa::Disparo (const vector<pair<string, int>> move) {
    if (this->nombre == "spoiled") return {"",-1}; // Si la babosa es una estropeada no se transformará por más velocidad que tome
    if (this->speed >= this->VELOCIMORPHISMO) {
        if (!move.empty()) {
            if (this->speed > this->MEGAMORPHISMO & this->isEvil == true) return GetRandomMove(3, move);
            if (this->speed > this->MEGAMORPHISMO & this->isEvil == false) return GetRandomMove(2, move);
            if (this->isEvil == true) return GetRandomMove(2, move);
           return GetRandomMove(1, move); // Disparo exitoso
        }
    }
    return {"Fallo", 0}; // No alcanza la velocidad mínima
}

pair <string, int> babosa::Ataques() {
    if (this->attack_moves.empty()) return {"",-1};
    return this->Disparo(this->attack_moves);
}

pair <string, int> babosa::Defensa() {

    if (this->defense_moves.empty()) return {"", -1};    
    return this->Disparo(this->defense_moves);
}

pair <string, int> babosa::MovUtilidad() {
    if (this->utilities.empty()) return {"", -1};
    return this->Disparo(this->utilities);
}

/*
int main() { // Testeo del funcionamiento de la clase
     babosa Inferno(true, "Inferno", 150,
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
     int mov = rand() % 3;

     //cout << "La opcion obtenida es:" << mov <<endl;
     pair<string, int> res;
     switch (mov) {
         case 0:
             printf("Se hará un ataque.\n\t");
             res = Inferno.Ataques();
             break;
         case 1:
             printf("Se hará una defensa.\n\t");
             res = Inferno.Defensa();
             break;
         case 2:
             printf("Se hará un movimiento de utilidad.\n\t");
             res = Inferno.MovUtilidad();
             break;
         default:
             break;
     }
     if (res.second != -1) {
        cout << "The result is: " << res.first << res.second << endl;
    } else {
         printf("No se puede disparar\n");
     }

     return 0;
 }
*/
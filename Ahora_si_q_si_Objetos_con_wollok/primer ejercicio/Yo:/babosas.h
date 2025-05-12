#ifndef BABOSAS_H
#define BABOSAS_H
#include <vector>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class babosa {
    private:
        string nombre;
        vector<pair<string, int>> attack_moves;
        vector<pair<string, int>> defense_moves;
        vector<pair<string, int>> utilities;
        int speed;
        bool isEvil;

    public:
        static constexpr int VELOCIMORPHISM = 120;
        static constexpr int MegaMorphism = 200;
        pair<string, int> GetRandomMove(int PlusMove,const vector<pair<string, int>> &moves);
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
        babosa& operator=(const babosa& other);
        ~babosa();
        //friend ostream& operator<<(ostream& os, const babosa& b);
};
#endif
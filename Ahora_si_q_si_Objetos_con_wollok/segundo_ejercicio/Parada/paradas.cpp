#include <vector>
#include "../queue.h"
#include "../pepe.h"
using namespace std;

class paradas
{
private:
        int id;
        ColaEspera* ColaPasajeros;
        void NuevoPasajero();
public:
        paradas(int id) {this->id = id;}
        ~paradas() {}
};
void paradas::NuevoPasajero()
{
    if(this->ColaPasajeros->front != 0 || this->ColaPasajeros->rear == -1) initialize(this->ColaPasajeros);
    int priority = rand()%2;
    crear(priority);
    
}
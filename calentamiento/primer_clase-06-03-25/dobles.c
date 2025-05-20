#include <stdio.h>
#include <a.out.h>


int doble(int num){
    printf("El doble del número proporcionado es:\n %d", num=num*2);
    return 0;
}
int cuadruple(int num){
    printf("\nEl cuadruple del número proporcionado es: \n %d \n", num=num*4);
    return 0;
}
int main(){
    
    int num;
    printf("Ingrese un número: \t");
    scanf("%d", &num);
    int NumDoble = doble(num);
    int NumCuadruple = cuadruple(num);
    
    return 0;
}

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>

using namespace std;
int main(int argc, char const *argv[])
{   
    int i = 0;
    srand((unsigned)time(0));
    while (i <= 3){
        int newNumb = rand() % 100;
        cout << newNumb << endl;
        i++;
    }

    return 0;
}



 
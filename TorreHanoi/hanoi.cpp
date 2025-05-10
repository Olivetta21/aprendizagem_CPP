#include <iostream>
#include <math.h>
#include <stdlib.h> /* for atoi() */
using namespace std;


int calcule(int A){
    for (int i = 1; i <= A; i++){
        if (A % (int)pow(2, i) != 0){
            return A - pow(2, i-1);
        }
    }
    return -9999;
}



int main() {
    int n = 3 ;
    int from, to, k ;

    for(k=1; k < (1 << n); k++) {
        /* obtem haste origem */
        from = (calcule(k))%3 ;

        /* obtem haste destino */
        to   = ((k|(k-1))+1)%3 ;

        /* descreve o movimento */
        printf("Mova disco de %d para %d\n", from, to) ;
    }

    return 0;
}

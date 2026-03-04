// Paul Carlu - Malo Martin

#include <stdio.h>
#include <stdlib.h>

void (int nbneel,float** matelem, float* vecelem, float** MatElem, float* SMbrElem){



    for(int j=0; j<nbneel; j++){
        for(int i=0;i<nbneel;i++){
            MatElem[j][i] = matelem[j][i];
        }
    }

    for(int j=0; j<nbneel; j++){
            SMbrElem[j] = vecelem[j];
        }
}
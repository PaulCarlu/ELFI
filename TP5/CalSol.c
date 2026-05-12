/* 
Paul Carlu - Malo Martin 
Université de Rennes 
Master 1 CSM
Module - Elements finis
*/

#include <stdio.h>
#include <stdlib.h>
#include "solex.h"

void CalSol(int NbLign, float** coord, float* UEX) {
    // Calcul de la solution exacte à l'aide de la fonction solex
    for(int i=0;i<NbLign;i++){
        UEX[i] = solex(coord[i]);
    }
}
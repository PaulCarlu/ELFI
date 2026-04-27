#include <stdio.h>
#include <stdlib.h>
#include "solex.h"

void CalSol(int NbLign, float** coord, float* UEX) {

    for(int i=0;i<NbLign;i++){
        UEX[i] = solex(coord[i]);
    }
    
}
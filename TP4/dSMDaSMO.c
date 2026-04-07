// Paul Carlu - Malo Martin

#include <stdio.h>
#include <stdlib.h>
#include "../TP3/tp3_prof/forfun.h"


void dSMDaSMO(int NbLign,int* AdPrCoefLi,int* NumColD,int* AdSuccLi,float* MatriceD,float* SecMembre,
                int* NumDLDir,float* ValDLDir,float* MatriceO,int* NumColO){

    cdesse_(&NbLign,AdPrCoefLi,NumColD,AdSuccLi,MatriceD,SecMembre,NumDLDir,ValDLDir,AdPrCoefLi,NumColO,
            MatriceO,SecMembre);

}
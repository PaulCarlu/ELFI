/* 
Paul Carlu - Malo Martin 
Université de Rennes 
Master 1 CSM
Module - Elements finis
*/

#include <stdio.h>
#include <stdlib.h>
#include "../TP3/tp3_prof/forfun.h"


void dSMDaSMO(int NbLign,int* AdPrCoefLi,int* NumColD,int* AdSuccLi,float* MatriceD,float* SecMembre,
                int* NumDLDir,float* ValDLDir,float* MatriceO,int* NumColO){

    // Appel de cdesse pour passer de la SMD à la SMO
    cdesse_(&NbLign,AdPrCoefLi,NumColD,AdSuccLi,MatriceD,SecMembre,NumDLDir,ValDLDir,AdPrCoefLi,NumColO,
            MatriceO,SecMembre);

}
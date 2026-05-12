/* 
Paul Carlu - Malo Martin 
Université de Rennes 
Master 1 CSM
Module - Elements finis
*/

#include <stdio.h>
#include <stdlib.h>

void dSMOaPR(int NbLign, int* AdPrCoefLi, int* NumCol, float* Matrice, int* Profil, float* MatProf) {
    // DiagProf
    for(int i=0;i<NbLign;i++){
        MatProf[i]=Matrice[i];
    }

    int indx, NbNNLi;
    int NextAd = 0;
    for(int i=0; i<NbLign-1; i++) {
        // Nombre d'élément non nul sur la ligne
        NbNNLi = AdPrCoefLi[i+1] - AdPrCoefLi[i];

        Profil[i] = NextAd+1;
        indx = AdPrCoefLi[i]-1;

        // Remplissage de tous les éléments non nul de la ligne exepté le dernier + zéros 
        for(int j=0; j<NbNNLi-1; j++) {
            MatProf[NbLign + NextAd] = Matrice[NbLign + indx + j];
            NextAd = NextAd + NumCol[indx + j+1] - NumCol[indx + j];
        }
        // Dernier élément non nul sur la ligne
        if(NbNNLi != 0){
            MatProf[NbLign + NextAd] = Matrice[NbLign + indx + NbNNLi-1];
            NextAd = NextAd + i+2 - NumCol[indx + NbNNLi-1];
        }
    }
    // Element imaginaire
    Profil[NbLign-1] = NextAd+1;
}
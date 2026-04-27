#include <stdio.h>
#include <stdlib.h>

void dSMOaPR(int NbLign, int* AdPrCoefLi, int* NumCol, float* Matrice, int* Profil, float* MatProf) {
    
    for(int i=0;i<NbLign;i++){
        MatProf[i]=Matrice[i];
    }


    int indx;
    int NextAd = 0;
    int NbNNLi;
    for(int i=0; i<NbLign; i++) {
        NbNNLi = AdPrCoefLi[i+1] - AdPrCoefLi[i];
        Profil[i] = NextAd+1;
        indx = AdPrCoefLi[i]-1;
        for(int j=0; j<NbNNLi-1; j++) {
            MatProf[NbLign + NextAd] = Matrice[NbLign + indx + j];
            NextAd = NextAd + NumCol[indx + j+1] - NumCol[indx + j];
        }
        if(NbNNLi != 0){
            MatProf[NbLign + NextAd] = Matrice[NbLign + indx + NbNNLi-1];
            NextAd = NextAd + i+2 - NumCol[indx + NbNNLi-1];
        }
    }
    Profil[NbLign] = NextAd;
}
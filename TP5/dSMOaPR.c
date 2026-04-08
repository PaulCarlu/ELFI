#include <stdio.h>
#include <stdlib.h>

void dSMOaPR(int NbLign, int* AdPrCoefLi, int* NumCol, float* Matrice, int* Profil, float* MatProf) {
    
    int NextAd = 0;
    int NbNNLi;
    for(int i=0; i<NbLign; i++) {
        NbNNLi = AdPrCoefLi[i+1] - AdPrCoefLi[i];
        Profil[i] = NextAd+1;
        for(int j=0; j<NbNNLi; j++) {
            MatProf[NbLign + NbNNLi] = Matrice[NbLign + AdPrCoefLi[i] + j];
            NextAd = NextAd + NumCol[AdPrCoefLi[i] + j+1] - NumCol[AdPrCoefLi[i] + j];
        }
        if(NbNNLi != 0){
            MatProf[NbLign + NbNNLi] = Matrice[NbLign + AdPrCoefLi[i] + NbNNLi-1];
            NextAd = NextAd + i+1 - NumCol[AdPrCoefLi[i] + NbNNLi-1];
        }
    }
}
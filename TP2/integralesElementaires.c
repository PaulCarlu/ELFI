
   // Carlu Paul - Martin Malo
//
#include <stdlib.h>
#include <stdio.h>

void W(int nbneel, float *Fbase, float eltdif, float cofvar, float *vecelm) {
    /*
    Calcul de 
        FOMEGA*Fbase_i
    et 
        FN*Fbase_i
    où FOMEGA et FN sont rerésentées par cofvar
    
    En entrée :
    - nbneel : nombre de noeuds de l'élément
    - Fbase : vecteur des valeurs des fontions de base au point de quadrature courant
    - eltdif : élément différentiel multiplié par le poids de quadrature
    - cofvar : valeur du coefficient variable (fonction à intégrer calculée en l'image
               par FK du point de quadrature courant)
    - vecelm : vecteur élémentaire de masse à actualiser
    En sortie :
    - vecelm : vecteur élémentaire de masse actualisée
    */
    for (int i=0; i<nbneel; i++) {
        vecelm[i] = vecelm[i] + eltdif*cofvar*Fbase[i];
    }
}

void WW(int nbneel, float *Fbase, float eltdif, float cofvar, float **matelm) {
    /*
    Calcul de 
        A00*Fbase_i*Fbase_j
    et 
        BN*Fbase_i*Fbase_j
    où A00 et BN sont rerésentées par cofvar
    
    En entrée :
    - nbneel : nombre de noeuds de l'élément
    - Fbase : vecteur des valeurs des fontions de base au point de quadrature courant
    - eltdif : élément différentiel multiplié par le poids de quadrature
    - cofvar : valeur du coefficient variable (fonction à intégrer calculée en l'image
               par FK du point de quadrature courant)
    - matelm : matrice élémentaire de masse à actualiser
    En sortie :
    - matelm : matrice élémentaire de masse actualisée
    */
    float coeff;
    for (int i=0; i<nbneel; i++) {
        coeff = eltdif*cofvar*Fbase[i];
        for (int j=0; j<nbneel; j++) {
            matelm[i][j] = matelm[i][j] + coeff*Fbase[j];
        }
    }
}

void ADWDW() {
    
}
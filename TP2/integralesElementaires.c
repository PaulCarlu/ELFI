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

void ADWDW(int nbneel, float **DerParFbase, float eltdif, float **cofvar, float **matelm) {
    /*
    Calcul de 
        somme sur alpha,beta : 
            cofvar[alpha][beta] * dérivé Fbase[i] par rapport à alpha * dérivé Fbase[j] par rapport à beta

    En entrée :
    - nbneel : nombre de noeuds de l'élément
    - DerParFbase : matrice des coefficients : transpose((grad Fbase[i](xk))) * colonne alpha(inverse(JacFK(xk)))
                    où alpha=1,2 ; xk est un point de quadrature et i varie selon le nombre de noeud sur l'élément de référence
    - eltdif : élément différentiel multiplié par le poids de quadrature
    - cofvar : matrice des coefficients variables (fonction à intégrer calculée en l'image
               par FK du point de quadrature courant)
    - matelm : matrice élémentaire de masse à actualiser
    En sortie :
    - matelm : matrice élémentaire de masse actualisée
    */
    for (int i=0; i<nbneel; i++) {
        for (int j=0; j<nbneel; j++) {
            matelm[i][j] = matelm[i][j] + cofvar[0][0]*DerParFbase[i][0]*DerParFbase[j][0]*eltdif;
            matelm[i][j] = matelm[i][j] + cofvar[1][0]*DerParFbase[i][1]*DerParFbase[j][0]*eltdif;
            matelm[i][j] = matelm[i][j] + cofvar[0][1]*DerParFbase[i][0]*DerParFbase[j][1]*eltdif;
            matelm[i][j] = matelm[i][j] + cofvar[1][1]*DerParFbase[i][1]*DerParFbase[j][1]*eltdif;
        }
    }
}
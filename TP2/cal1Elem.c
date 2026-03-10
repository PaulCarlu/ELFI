// Paul Carlu - Malo Martin

#include <stdio.h>
#include <stdlib.h>
#include "processCalcElementaires.h"

void cal1Elem(int nbneel, int nRefDom, int nbRefD0, int numRefD0, int nbRefD1, int numRefD1, int nbRefF1, int numRefF1, int typEL,
              float** coorEl, int nbaret, int** nRefArEl, float** MatElem, float* SMbrElem, int* NuDElem, int* uDElem){
  
  /* MatElem et SMbrElem */
  float matelm[nbneel][nbneel];
  float vecelm[nbneel];
  // Appel de intElem pour remplir matelm et vecelm
  intElem(nbneel,coorEl,matelm,vecelm);

  for(int i=0; i<nbneel; i++) {
    for(int j=0; j<nbneel; j++) {
      MatElem[i][j] = matelm[i][j];
    }
    SMbrElem[i] = vecelm[i];
  }

  /* NuDElem et uDElem */
  for(int i=0; i<nbneel; i++) {
    NuDElem[i] = 0;
    uDElem[i] = 0;
  }
}

void impCalEl(int K, int typEl, int nbneel, float **MatElem, float *SMbrElem,
              int *NuDElem, float *uDElem) {
/************************************************************************
  Imprime les resultats de la matrice et du second membre elementaires
  ainsi que les conditions Dirichlet en chaque noeud
  et les valeurs des conditions Dirichlet non homogene
 
*** Arguments *** 
   K        : Numero de l'element
   typEl    : Numero de type de l'element
   nbneel   : Nombre de noeuds de l'element
   MatElem  : Matrice elementaire de dimensions (nbneel,nbneel)
   SMbrElem : Second membre elementaire de dimension nbneel
   NuDElem  : Tableau de reperage des noeuds porteurs de conditions de Dirichlet
   uDElem   : Tableau des valeurs de blocage
              pour les noeuds Dirichlet non homogene
************************************************************************/
  int i, j;
  printf("\n");
  printf(" ELEMENT=%3d    DE TYPE=%5d    NB NOEUDS=%2d\n", K,typEl,nbneel);
  printf(" NuDElem   uDElem    SMbrElem    MatElem\n");
  for (i=0; i < nbneel; i++) {
    printf(" %6d %10.4e %10.4e", NuDElem[i],uDElem[i],SMbrElem[i]);
    for (j=0; j <= i; j++) { printf(" %10.4e", MatElem[i][j]); }
    printf("\n");
  }
}

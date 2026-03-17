// Paul Carlu - Malo Martin

#include <stdio.h>
#include <stdlib.h>
#include "processCalcElementaires.h"
#include "fonctionsUtilitaires.h"
#include "../TP1/allocmat.h"
#include "fonctionsDef.h"

void cal1Elem(int nbneel, int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1, int nbRefF1, int* numRefF1, int typEl,
              float** coorEl, int nbaret, int* nRefArEl, float** MatElem, float* SMbrElem, int* NuDElem, float* uDElem){
  
  /* MatElem et SMbrElem */
  float **matelm = allocmatFLOAT(nbneel,nbneel);
  float vecelm[nbneel];
  for(int i=0; i<nbneel; i++) {
    for(int j=0; j<nbneel; j++) {
      matelm[i][j] = 0;
    }
    vecelm[i] = 0;
  }
  // Appel de intElem pour remplir matelm et vecelm
  intElem(typEl,coorEl,matelm,vecelm);

  for(int i=0; i<nbneel; i++) {
    for(int j=0; j<nbneel; j++) {
      MatElem[i][j] = matelm[i][j];
    }
    SMbrElem[i] = vecelm[i];
  }

  /* NuDElem et uDElem */
  for(int i=0; i<nbneel; i++) {
    NuDElem[i] = 1;
    uDElem[i] = 0;
  }
  
  /* Initialisation des variables nécessaire pour la boucle */
  int numPnts_Naret[2];
  float **mataret = allocmatFLOAT(2,2);
  float vecaret[2];
  for(int i=0; i<2;i++) {
    mataret[i][0] = 0;
    mataret[i][1] = 0;
    vecaret[i] = 0;
  }
  float **coorAr = allocmatFLOAT(2,2);

  /* Boucle sur les arêtes de l'élément courant */
  for(int i=0;i<nbaret;i++){
    numNaret(typEl,i+1,numPnts_Naret);
    // Attribution des conditions de Dirichlet homogène suivant les arêtes
    for(int j=0;j<nbRefD0;j++){
      if(nRefArEl[i]==numRefD0[j]){
        NuDElem[numPnts_Naret[0]-1] = 0;
        NuDElem[numPnts_Naret[1]-1] = 0;
      }
    }
    // Attribution des conditions de Dirichlet non homogène suivant les arêtes
    for(int j=0;j<nbRefD1;j++){
      if(nRefArEl[i]==numRefD1[j]){
        NuDElem[numPnts_Naret[0]-1] = -1;
        uDElem[numPnts_Naret[0]-1] = UD(coorEl[numPnts_Naret[0]-1]);
        NuDElem[numPnts_Naret[1]-1] = -1;
        uDElem[numPnts_Naret[1]-1] = UD(coorEl[numPnts_Naret[1]-1]);
      }
    }
    // Calcul avec intAret sur les arêtes avec condition de Neumann/Fourier
    for(int j=0; j<nbRefF1; j++) {
      if(nRefArEl[i] == numRefF1[j]){
        selectPts(2,numPnts_Naret,coorEl,coorAr); // A voir si jamais avec le prof pour la façon dont est fait numNaret
        intAret(coorAr,mataret,vecaret);
        // MatElem
        MatElem[numPnts_Naret[0]-1][numPnts_Naret[0]-1] += mataret[0][0];
        MatElem[numPnts_Naret[0]-1][numPnts_Naret[1]-1] += mataret[0][1];
        MatElem[numPnts_Naret[1]-1][numPnts_Naret[0]-1] += mataret[1][0];
        MatElem[numPnts_Naret[1]-1][numPnts_Naret[1]-1] += mataret[1][1];
        // SMbrElem
        SMbrElem[numPnts_Naret[0]-1] += vecaret[0];
        SMbrElem[numPnts_Naret[1]-1] += vecaret[1];
      }
    }
  }

  freematFLOAT(matelm);
  freematFLOAT(mataret);
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

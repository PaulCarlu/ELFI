// Paul Carlu - Malo Martin

#include <stdio.h>
#include <stdlib.h>
#include "../TP2/cal1Elem.h"
#include "../TP2/fonctionsUtilitaires.h"
#include "tp3_prof/forfun.h"

void Assemblage(int typEl, int nbtng, int nbtel, int nbneel, int nbaret,int** nRefAr, int **ngnel,float **coord,
                float **MatElem, float **coorEl,float* SMbrElem,int* NuDElem,float* uDElem,
                int nRefDom,int nbRefD0,int* numRefD0, int nbRefD1,int* numRefD1, int nbRefF1,int* numRefF1,
                int* NumDLDir, float* ValDLDir,float* SecMembre, float* Matrice, int* AdPrCoefLi, int* NumCol, int* AdSuccLi ){

    int *nRefArEl;
    int nbcoef = nbtng*2*((typEl==1)?8:6);
    float* DiagMat = calloc(nbtng,sizeof(float));
    float* LowMat = malloc(nbcoef*sizeof(float));
    int NextAd = 1;
    int I, J, Itilde, Jtilde;

    for(int i=0; i<nbtng; i++) {
        NumDLDir[i] = i+1;
    }

    for (int K=0; K < nbtel; K++) {
        // Assignation des valeurs pour la fonction cal1Elem
        for (int i=0; i<nbneel; i++) {
            for (int j=0; j<nbneel; j++) {
                MatElem[i][j] = 0;
            }
            SMbrElem[i] = 0;
        }
        selectPts(nbneel,ngnel[K],coord,coorEl);
        nRefArEl = nRefAr[K];

        // Appel de cal1Elem
        cal1Elem(nbneel,nRefDom,nbRefD0,numRefD0,nbRefD1,numRefD1,nbRefF1,numRefF1,typEl,coorEl,nbaret,
                nRefArEl,MatElem,SMbrElem,NuDElem,uDElem);
        // Appel de impCalEl pour vérifier les calculs
        impCalEl(K+1,typEl,nbneel,MatElem,SMbrElem,NuDElem,uDElem);
        
        // Boucle incrémentation ValDLDir et NumDLDir
        for(int i=0;i<nbneel;i++){
            // On fait le choix de commencer l'indentation de I et J avec 1
            I = ngnel[K][i];

            for(int j=0;j<i;j++){   
                J = ngnel[K][j];

                // Changement de I et J si nécessaire
                Itilde = (I<J)?J:I;
                Jtilde = (I<J)?I:J;

                if (NextAd<nbcoef){
                    assmat_(&Itilde,&Jtilde,&MatElem[i][j],AdPrCoefLi,NumCol,AdSuccLi,LowMat,&NextAd);
                }
                else printf("\nTaille de LowMat sous estimée\n");
            }
            
            if (NuDElem[i] == 0) {
                NumDLDir[I-1] = 0;
                ValDLDir[I-1] = 0;
            } else if (NuDElem[i] == -1 && NumDLDir[I-1] != 0) {
                // Les noeuds de Dirichlet homogène passe en priorité
                NumDLDir[I-1] = -I;
                ValDLDir[I-1] = uDElem[i];
            }
            DiagMat[I-1] += MatElem[i][i];
            SecMembre[I-1] += SMbrElem[i];
        }
   
    }

    for(int i=0;i<nbtng;i++){
        Matrice[i] = DiagMat[i];
    }

    for(int i=0;i<nbcoef;i++){
        Matrice[i+nbtng] = LowMat[i];
    }

    free(DiagMat);
    free(LowMat);
}
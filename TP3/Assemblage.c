// Paul Carlu - Malo Martin

#include <stdio.h>
#include <stdlib.h>
#include "../TP2/cal1Elem.h"
#include "../TP2/fonctionsUtilitaires.h"

    

void Assemblage(int typEl, int nbtng, int nbtel, int nbneel, int nbaret,int** nRefAr, int **ngnel,float **coord,
                float **MatElem, float **coorEl,float* SMbrElem,int* NuDElem,float* uDElem,
                int nRefDom,int nbRefD0,int* numRefD0, int nbRefD1,int* numRefD1, int nbRefF1,int* numRefF1,
                int* NumDLDir, float* ValDLDir,float* SecMembre, float* Matrice, int* AdPrCoefLi, int* NumCol, int* AdSuccLi ){

    int *nRefArEl;
    int nbcoef = nbtng*2*((typEl==1)?8:6);
    float* DiagMat = calloc(nbtng,sizeof(float));
    float* LowMat = malloc(nbcoef*sizeof(float));
    int* NextAd = &LowMat[0];

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
        
        

        
        // Boucle incrémentation ValDLDir et NumDLDir
        for(int i=0;i<nbneel;i++){

            // On fait le choix de commencer l'indentation de I et J avec 1
            int I = ngnel[K][i];

            for(int j=0;j<i;j++){   
                int J = ngnel[K][j];
                assmat_((I<J)?J:I,(I<J)?I:J,MatElem[i][j],AdPrCoefLi,NumCol,AdSuccLi,LowMat,NextAd);
            }


            NumDLDir[I-1] = NuDElem[i]*I;
            ValDLDir[I-1] = uDElem[i];
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
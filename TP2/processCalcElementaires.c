// Paul Carlu - Malo Martin
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonctionsUtilitaires.h"
#include "fonctionsDef.h"
#include "integralesElementaires.h"
#include "../TP1/allocmat.h"

void intElem(int t,float** coorEl, float **matelm, float *vecelm){
    // Nombre de noeuds géométrique
    int nbneel;
    if (t==1){nbneel=4;}
    else if (t==2){nbneel=3;}
    else if (t==3){nbneel=2;}

    // Points et poids de quadrature
    int q = valq(t);
    float omegaquad[q];
    int dim = (t==3)?1:2;
    float **xquad = allocmatFLOAT(q,dim);
    ppquad(t,omegaquad,xquad);

    // Initialisation avant la boucle
    float Fbase_x[nbneel], FK_x[2], det, eltdif, cofvarW;
    float **DerFbase_x = allocmatFLOAT(nbneel,2);
    float **JacFK_x = allocmatFLOAT(2,2);
    float **InvJacFK_x = allocmatFLOAT(2,2);
    float **cofvarADWDW = allocmatFLOAT(2,2);
    float **DerParFbase = allocmatFLOAT(nbneel,2);
    
    for (int i=0;i<q;i++){
        // Fonctions de base et dérivées
        calFbase(t,xquad[i],Fbase_x);
        calDerFbase(t,xquad[i],DerFbase_x);
        
        // Point de quadrature courant dans l'élément courant
        transFK(nbneel, coorEl, Fbase_x, FK_x);

        // Jacobienne et son inverse
        matJacob(dim, nbneel, coorEl, DerFbase_x, JacFK_x);
        invertM2x2(JacFK_x,InvJacFK_x,&det);

        eltdif = fabs(det)*omegaquad[i];

        // Appel de W
        cofvarW = FOMEGA(xquad[i]);
        W(nbneel,Fbase_x,eltdif,cofvarW,vecelm);

        // Appel de WW
        cofvarW = A00(xquad[i]);
        WW(nbneel,Fbase_x,eltdif,cofvarW,matelm);

        // Appel de ADWDW
        cofvarADWDW[0][0] = A11(xquad[i]); cofvarADWDW[0][1] = A12(xquad[i]);
        cofvarADWDW[1][0] = A12(xquad[i]); cofvarADWDW[1][1] = A22(xquad[i]);
        for(int i=0;i<nbneel;i++){
            DerParFbase[i][0] = DerFbase_x[i][0]*InvJacFK_x[0][0] + DerFbase_x[i][1]*InvJacFK_x[1][0];
            DerParFbase[i][1] = DerFbase_x[i][0]*InvJacFK_x[0][1] + DerFbase_x[i][1]*InvJacFK_x[1][1];
        }
        ADWDW(nbneel,DerParFbase,eltdif,cofvarADWDW,matelm);
    }
    freematFLOAT(xquad);
    freematFLOAT(DerFbase_x);
    freematFLOAT(JacFK_x);
    freematFLOAT(InvJacFK_x);
    freematFLOAT(cofvarADWDW);
    freematFLOAT(DerParFbase);
}
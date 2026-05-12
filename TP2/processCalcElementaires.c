/* 
Paul Carlu - Malo Martin 
Université de Rennes 
Master 1 CSM
Module - Elements finis
*/

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
    float poids[q];
    int dim = (t==3)?1:2;
    float **points = allocmatFLOAT(q,dim);
    ppquad(t,poids,points);

    // Initialisation avant la boucle
    float Fbase_x[nbneel], FK_x[2], det, eltdif, cofvarW;
    float **DerFbase_x = allocmatFLOAT(nbneel,2);
    float **JacFK_x = allocmatFLOAT(2,2);
    float **InvJacFK_x = allocmatFLOAT(2,2);
    float **cofvarADWDW = allocmatFLOAT(2,2);
    float **DerParFbase = allocmatFLOAT(nbneel,2);
    
    for (int i=0;i<q;i++){
        // Fonctions de base et dérivées
        calFbase(t,points[i],Fbase_x);
        calDerFbase(t,points[i],DerFbase_x);
        
        // Point de quadrature courant dans l'élément courant
        transFK(nbneel, coorEl, Fbase_x, FK_x);

        // Jacobienne et son inverse
        matJacob(dim, nbneel, coorEl, DerFbase_x, JacFK_x);
        invertM2x2(JacFK_x,InvJacFK_x,&det);

        eltdif = fabs(det)*poids[i];

        // Appel de W
        cofvarW = FOMEGA(FK_x);
        W(nbneel,Fbase_x,eltdif,cofvarW,vecelm);

        // Appel de WW
        cofvarW = A00(FK_x);
        WW(nbneel,Fbase_x,eltdif,cofvarW,matelm);

        // Appel de ADWDW
        cofvarADWDW[0][0] = A11(FK_x); cofvarADWDW[0][1] = A12(FK_x);
        cofvarADWDW[1][0] = A12(FK_x); cofvarADWDW[1][1] = A22(FK_x);
        for(int i=0;i<nbneel;i++){
            DerParFbase[i][0] = DerFbase_x[i][0]*InvJacFK_x[0][0] + DerFbase_x[i][1]*InvJacFK_x[1][0];
            DerParFbase[i][1] = DerFbase_x[i][0]*InvJacFK_x[0][1] + DerFbase_x[i][1]*InvJacFK_x[1][1];
        }
        ADWDW(nbneel,DerParFbase,eltdif,cofvarADWDW,matelm);
    }
    freematFLOAT(points);
    freematFLOAT(DerFbase_x);
    freematFLOAT(JacFK_x);
    freematFLOAT(InvJacFK_x);
    freematFLOAT(cofvarADWDW);
    freematFLOAT(DerParFbase);
}

void intAret(int refArete, float** coorAr, float **mataret, float *vecaret){

    // Nombre de noeuds géométrique
    int nbneel = 2;
    int typEl = 3;

    // Points et poids de quadrature
    int q = 3 ;
    float poids[q];
    float** points = allocmatFLOAT(q,1);
    ppquad(typEl,poids,points);

    // Initialisation avant la boucle
    float Fbase_x[nbneel], FK_x[2], det, eltdif, cofvar;
    float **DerFbase_x = allocmatFLOAT(nbneel,2);
    float **JacFK_x = allocmatFLOAT(2,2);
    float normeJaFk_x;
    
    for (int i=0;i<q;i++){
        // Fonctions de base et dérivées
        calFbase(typEl,points[i],Fbase_x);
        calDerFbase(typEl,points[i],DerFbase_x);
        
        // Point de quadrature courant dans l'élément courant
        transFK(nbneel, coorAr, Fbase_x, FK_x);

        // Jacobienne et son inverse
        matJacob(1, nbneel, coorAr, DerFbase_x, JacFK_x);
        // Norme euclidienne de la Jacobienne
        normeJaFk_x = sqrt(JacFK_x[0][0]*JacFK_x[0][0] + JacFK_x[1][0]*JacFK_x[1][0]);

        eltdif = normeJaFk_x*poids[i];

        // Appel de W
        cofvar = FN(FK_x,refArete);
        W(nbneel,Fbase_x,eltdif,cofvar,vecaret);

        // Appel de WW
        cofvar = BN(FK_x);
        WW(nbneel,Fbase_x,eltdif,cofvar,mataret);
        
    }
    freematFLOAT(points);
    freematFLOAT(DerFbase_x);
    freematFLOAT(JacFK_x);
}
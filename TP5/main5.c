// Carlu Paul - Martin Malo
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../TP1/lecfima.h"
#include "../TP1/allocmat.h"
#include "../TP3/Assemblage.h"
#include "tp5_prof/forfun.h"
#include "../TP4/dSMDaSMO.h"
#include "dSMOaPR.h"
#include "CalSol.h"

int Domaine = 0;
int nucas = 0;
//extern float* a,b,c,d;  

int main() {
    // Demande des choix de l'utilisateur
    printf("Choisir le domaine d'étude (1 ou 2): ");
    scanf("%d",&Domaine);
    while(Domaine != 1 && Domaine != 2 ) {
        printf("Numéro de Domaine invalide (choisir 1 ou 2) : ");
        scanf("%d",&Domaine);
    }
    printf("Choisir le cas (1, 2 ou 3): ");
    scanf("%d",&nucas);
    while(nucas != 1 && nucas != 2 && nucas != 3) {
        printf("Numéro de cas invalide (choisir entre 1, 2 ou 3) : ");
        scanf("%d",&nucas);
    }
    int maillage = 0;
    printf("Choix du maillage (quadrangle : 1 | triangle : 2) : ");
    scanf("%d",&maillage);
    while(maillage != 1 && maillage != 2 ) {
        printf("Choix de maillage invalide (choisir 1 ou 2) : ");
        scanf("%d",&maillage);
    }
    char ficmai[30];
    int nbneel = 0;
    if (maillage == 1) {
        nbneel = 4;
    } else {
        nbneel = 3;
    }

    int IMPFCH = 1;
    printf("Choisir le 'n' dans fort.n, le fichier dans lequel apparaît les erreurs : ");
    scanf("%d",&IMPFCH);

    // Initialisation de toutes les variables pour la boucle for
    /* Notations :
        - typEl : type de l'élément géométrique
        - nbtng : nombre total de noeuds
        - nbtel : nombre total d'éléments
        - nbneel : nombre de noeuds sur un élément
        - nbaret : nombre d'arêtes sur un élément
        - coord : matrice de toutes les coordonnées
        - ngnel : matrice des numéros globaux des éléments
        - nRefAr : matrice des numéros de référence associés aux arrêtes
    */
    int typEl, nbtng, nbtel, nbaret;
    float **coord; 
    int **ngnel, **nRefAr;

    /* Notations :
        - nRefDom : numéro de référence des arêtes internes du domaine
        - nbRefD0, nbRefD1, nbRefF1 : nombre de valeurs contenues dans les différents vecteurs numRefD0, numRefD1 et numRefF1
        - numRefD0, numRefD1, numRefF1 : vecteurs des numéros de référence de chaque type
        ---> numRefD0 : Dirichlet homogène ; numRefD1 : Dirichlet non homogène ; numRefF1 : Fourier/Neumann
        - coorEl : coordonnées de l'élement sélectionné
        - nRefArEl : matrice des numéros de référence associés aux arrêtes de l'élement sélectionné
        - MatElem : matrice élémentaire
        - SMbrElem : vecteur du second membre élémentaire
        - NuDElem : vecteur des noeuds porteurs d'une condition de Dirichlet
        - uDElem : vecteurs des valeurs portées par ces noeuds avec une condition de Dirichlet
    */
    float **MatElem, **coorEl;
    float SMbrElem[nbneel], uDElem[nbneel];
    int NuDElem[nbneel];

    int nRefDom;
    int nbRefD0, nbRefF1, nbRefD1;
    int numRefD0[4], numRefD1[4], numRefF1[4];

    // Assemblage de la matrice
    int NbLign, nbcoef;
    int *NumDLDir, *AdPrCoefLi, *NumColD, *AdSuccLi;
    float *ValDLDir, *SecMembre, *MatriceD;

    int* NumColO;
    float* MatriceO;

    int dimProf;
    float* MatProf;
    int* Profil;

    float eps = (float) 1.0e-07;
    float *LowMatProf, *ld, *ll, *y, *U;

    float* UEX;

    // Boucle sur tous les fichiers du cas considéré
    for (int i=1; i<7; i++) {
        if (Domaine == 1) {
            if (maillage == 1) {
                sprintf(ficmai,"../maillage/d1q1/d1q1_%d",(int) pow(2,i));
            } else {
                sprintf(ficmai,"../maillage/d1t1/d1t1_%d",(int) pow(2,i));
            }
        } else {
            if (maillage == 1) {
                sprintf(ficmai,"../maillage/d2q1/d2q1_%d",(int) pow(2,i));
            } else {
                sprintf(ficmai,"../maillage/d2t1/d2t1_%d",(int) pow(2,i));
            }
        }
        printf("%s\n",ficmai);
        
        lecfima(ficmai,&typEl,&nbtng,&coord,&nbtel,&ngnel,&nbneel,&nbaret,&nRefAr);

        // Conditons aux bords
        /* Pour aller chercher les bords :
        - bord 1 = nRefAr[0][nbneel-1]
        - bord 2 = nRefAr[0][nbneel-2]
        - bord 3 = nRefAr[nbtel-1][nbneel-2]
        - bord 4 = nRefAr[nbtel-1][nbneel-1]
        */
       nRefDom = nRefAr[0][0];
        if (Domaine == 1) {
            switch (nucas)
            {
            case 1 :
                nbRefD0 = 4, nbRefD1 = 0, nbRefF1 = 0; 
                numRefD0[0] = nRefAr[0][nbneel-1];
                numRefD0[1] = nRefAr[0][nbneel-2];
                numRefD0[2] = nRefAr[nbtel-1][nbneel-2]; 
                numRefD0[3] = nRefAr[nbtel-1][nbneel-1];
                break;
            case 2 :
                nbRefD0 = 4, nbRefD1 = 0, nbRefF1 = 0; 
                numRefD0[0] = nRefAr[0][nbneel-1];
                numRefD0[1] = nRefAr[0][nbneel-2];
                numRefD0[2] = nRefAr[nbtel-1][nbneel-2]; 
                numRefD0[3] = nRefAr[nbtel-1][nbneel-1];
                break;
            case 3 :
                nbRefD0 = 0, nbRefD1 = 0, nbRefF1 = 4; 
                numRefF1[0] = nRefAr[0][nbneel-1];
                numRefF1[1] = nRefAr[0][nbneel-2];
                numRefF1[2] = nRefAr[nbtel-1][nbneel-2]; 
                numRefF1[3] = nRefAr[nbtel-1][nbneel-1];
                break;
            default:
                break;
            }
        } else {
            switch (nucas)
            {
            case 1 :
                nbRefD0 = 4, nbRefD1 = 0, nbRefF1 = 0; 
                numRefD0[0] = nRefAr[0][nbneel-1];
                numRefD0[1] = nRefAr[0][nbneel-2];
                numRefD0[2] = nRefAr[nbtel-1][nbneel-2]; 
                numRefD0[3] = nRefAr[nbtel-1][nbneel-1];
                break;
            case 2 :
                nbRefD0 = 4, nbRefD1 = 0, nbRefF1 = 0; 
                numRefD0[0] = nRefAr[0][nbneel-1];
                numRefD0[1] = nRefAr[0][nbneel-2];
                numRefD0[2] = nRefAr[nbtel-1][nbneel-2]; 
                numRefD0[3] = nRefAr[nbtel-1][nbneel-1];
                break;
            case 3 :
                nbRefD0 = 2, nbRefD1 = 0, nbRefF1 = 2; 
                numRefD0[0] = nRefAr[0][nbneel-1];
                numRefD0[1] = nRefAr[nbtel-1][nbneel-1];
                numRefF1[0] = nRefAr[0][nbneel-2];
                numRefF1[1] = nRefAr[nbtel-1][nbneel-2];
                break;
            default:
                break;
            }
        }
        MatElem = allocmatFLOAT(nbneel,nbneel);
        coorEl = allocmatFLOAT(nbneel,2);
        
        // Assemblage de la matrice
        NbLign = nbtng; // Nombre de noeuds géométriques
        nbcoef = nbtng*2*((typEl==1)?8:6);
        NumDLDir = malloc(NbLign*sizeof(int));
        ValDLDir = calloc(NbLign,sizeof(float));
        SecMembre = calloc(NbLign,sizeof(float));
        AdPrCoefLi = calloc(NbLign,sizeof(int));
        MatriceD = calloc((NbLign+nbcoef),sizeof(float));
        NumColD = calloc(nbcoef,sizeof(int));
        AdSuccLi = malloc(nbcoef*sizeof(int));
        
        Assemblage(typEl,nbtng,nbtel,nbneel,nbaret,nRefAr,ngnel,coord,MatElem,coorEl,SMbrElem,NuDElem,uDElem,nRefDom,
                    nbRefD0,numRefD0,nbRefD1,numRefD1,nbRefF1,numRefF1,NumDLDir,ValDLDir,SecMembre,MatriceD,AdPrCoefLi,
                    NumColD,AdSuccLi );

        //affsmd_(&NbLign,AdPrCoefLi,NumColD,AdSuccLi,MatriceD,SecMembre,NumDLDir,ValDLDir);
        
        nbcoef = AdPrCoefLi[NbLign-1]-1;
        NumColO = malloc(nbcoef*sizeof(int));
        MatriceO = calloc(NbLign+nbcoef,sizeof(float));

        dSMDaSMO(NbLign,AdPrCoefLi,NumColD,AdSuccLi,MatriceD,SecMembre,NumDLDir,ValDLDir,MatriceO,NumColO);

        //affsmo_(&NbLign,AdPrCoefLi,NumColO,MatriceO,SecMembre);

        dimProf = 0;
        for (int i=0; i<NbLign-1; i++) {
            if (AdPrCoefLi[i+1]-AdPrCoefLi[i]!=0){
                dimProf = dimProf + i+2 - NumColO[AdPrCoefLi[i]-1];
            }
        }

        MatProf = calloc(NbLign+dimProf,sizeof(float));
        Profil = malloc((NbLign)*sizeof(int));

        dSMOaPR(NbLign,AdPrCoefLi,NumColO,MatriceO,Profil,MatProf);
        
        /* Décomposition LLT
        Résolution :extern int nucas = 1;  
            L*Y = SecMembre
            LT*U = Y
        avec Y = LT*U
        */
        LowMatProf = MatProf + NbLign;
        ld = malloc(NbLign*sizeof(float));
        ll = malloc(dimProf*sizeof(float));
        y = malloc(NbLign*sizeof(float));
        U = malloc(NbLign*sizeof(float));

        ltlpr_(&NbLign,Profil,MatProf,LowMatProf,&eps,ld,ll);
        rsprl_(&NbLign,Profil,ld,ll,SecMembre,y);
        rspru_(&NbLign,Profil,ld,ll,y,U);
    
        // Calcul de la solution exacte
        UEX = malloc(NbLign*sizeof(float));
        CalSol(NbLign,coord,UEX);

<<<<<<< HEAD
    rsprl_(&NbLign,Profil,ld,ll,SecMembre,y);
    rspru_(&NbLign,Profil,ld,ll,y,U);
   
    // Calcul de la solution exacte
    float* UEX = malloc(NbLign*sizeof(float));
    CalSol(NbLign,coord,UEX);
    

    int IMPFCH = 10;
    affsol_(&NbLign,coord[0],U,UEX,&IMPFCH);
    
=======
        /*
        for(int i=0; i<NbLign; i++){
            printf("U[%d] = %.15f ; UEX[%d] = %.15f\n",i,U[i],i,UEX[i]);
        }
        */
        
        affsol_(&NbLign,coord[0],U,UEX,&IMPFCH);
    }
>>>>>>> 7eda4e7 (.)

    // Free des vecteurs et matrices
    freematFLOAT(MatElem);
    freematFLOAT(coord);
    freematINT(ngnel);
    freematINT(nRefAr);
    free(NumDLDir);
    free(ValDLDir);
    free(SecMembre);
    free(MatriceD);
    free(AdSuccLi);
    free(NumColD);
    free(AdPrCoefLi);
    free(MatriceO);
    free(NumColO);
    free(MatProf);
    free(Profil);
    free(ld);
    free(ll);
    free(y);
    free(U);
    free(UEX);
    return 0;
}

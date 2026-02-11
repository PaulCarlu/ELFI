// Carlu Paul - Martin Malo
//
#include <stdio.h>
#include <stdlib.h>
#include "allocmat.h"
#include "fonctionsUtilitaires.h"


int main(){


    //Test de ppquad dans le cas d'un carré

    int t = 1;
    float* romega = malloc(9*sizeof(float));
    float** rx = allocmatFLOAT(9,2);
    ppquad(t,romega,rx);

    // Affichage
    printf("Vecteur des poids de quadrature pour le quadrangle :\n");
    for(int k=0;k<9;k++){printf(" %f ", romega[k]);}

    printf("\n Coordonnées des points de quadrature pour le quadrangle :\n");
    printmatFloat(rx,9,2);

    // Free
    free(romega);
    freematFLOAT(rx);


    // Calcul des valeurs au point de coordonnées (1,1) par les fonctions de base de l'élément de réf
    float* x = malloc(2*sizeof(float));
    x[0]=1, x[1]=1;
    float* Fbase_x = malloc(4*sizeof(float));
    calFbase(t,x,Fbase_x);

    // Affichage
    printf("\n Valeurs des fonctions de base du quadrangle de référence au poitn de coordonnées (1,1) :\n");
    for(int k=0;k<4;k++){printf(" %f ", Fbase_x[k]);}


    // Calcul des valeurs au point de coordonnées (1,1) par les dérivées des fonctions de base de l'élément de réf
    float** d_Fbase_x = allocmatFLOAT(4,2);
    calDerFbase(t,x,d_Fbase_x);

    // Affichage
    printf("\n Valeurs des dérivées des fonctions de base du quadrangle de référence au poitn de coordonnées (1,1) :\n");
    printmatFloat(d_Fbase_x,4,2);
    

    // Calcul de l'image d'un élément de référence par la fonction FK
    int p = 3;
    float** a = allocmatFLOAT(4,2);
    a[0][0]=1,a[0][1]=0;
    a[1][0]=1,a[1][1]=1;
    a[2][0]=0,a[2][1]=1;
    a[3][0]=0,a[3][1]=0;
    float* FK_x = malloc(2*sizeof(float));
    transFK(p,a,Fbase_x,FK_x);

    // Affichage
    printf(" FK((1,1)) = %f %f\n",FK_x[0],FK_x[1]);


    // Calcul de l'image d'un élément de référence par la fonction d_FK
    int d = 2;
    float** JacFK = allocmatFLOAT(2,d);
    matJacob(d,p,a,d_Fbase_x,JacFK);

    // Affichage
    printf(" JacFK(x) : \n");
    printmatFloat(JacFK,2,d);


    // Inversion de la matrice homothétie de rapport 2
    float** A = allocmatFLOAT(2,2);
    float** InvA = allocmatFLOAT(2,2);
    float det;
    A[0][0]=2,A[0][1]=0;
    A[1][0]=0,A[1][1]=2;
    invertM2x2(A,InvA,&det);

    // Affichage
    printf("Inverse de l'homothétie de rapport 2 :\n");
    printmatFloat(InvA,2,2);
    printf("\n déterminant de A = %f",det);


    // Liste des numéros associés à une arrête sur l'élément de référence
    int* numPnts_aret3 = malloc(2*sizeof(int));
    int aret3 = 3;
    numNaret(t,aret3,numPnts_aret3);

    // Affichage
    printf("\n Les numéros locaux associés à l'arrête numéro 3 du quadrangle sont : %d %d \n",numPnts_aret3[0],numPnts_aret3[1]);


    // Sélection de coordonnées dans l'ensemble des coordonnées
    int nb = 2;
    int* num = malloc(2*sizeof(int));
    num[0]=3,num[1]=6;
    float** coorEns = allocmatFLOAT(10,2);
    for(int i=0;i<5;i++){
            coorEns[i][0]=0;
            coorEns[i][1]=1;
    }
    for(int i=5;i<10;i++){
            coorEns[i][0]=2;
            coorEns[i][1]=3;
    }
    float** coorSel = allocmatFLOAT(2,2);
    selectPts(nb,num,coorEns,coorSel);

    // Affichage
    printmatFloat(coorSel,2,2);

    // Free
    free(x);
    freematFLOAT(a);
    freematFLOAT(JacFK);
    free(FK_x);
    free(Fbase_x);
    freematFLOAT(d_Fbase_x);
    freematFLOAT(A);
    freematFLOAT(InvA);
    free(numPnts_aret3);
    free(num);
    freematFLOAT(coorEns);
    freematFLOAT(coorSel);

    return 0;
}
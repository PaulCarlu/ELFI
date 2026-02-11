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

    // Calcul des valeurs du points de coordonnées (1,1) par les fonctions de base de l'élément de réf
    float* x = malloc(2*sizeof(float));
    x[0]=1, x[1]=1;
    float* Fbase_x = malloc(4*sizeof(float));
    calFbase(t,x,Fbase_x);

    // Affichage
    printf("\n Valeurs des fonctions de base du quadrangle de référence au poitn de coordonnées (1,1) :\n");
    for(int k=0;k<4;k++){printf(" %f ", Fbase_x[k]);}
    free(x);
    free(Fbase_x);

    return 0;
}
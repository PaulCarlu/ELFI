// Carlu Paul - Martin Malo
//
// gcc allocmat.c maillage.c main.c -o executable
//
#include <stdio.h>
#include <stdlib.h>
#include "maillage.h"
#include "allocmat.h"

int main() {
    /* Création de 3 maillages */
    // 1er
    char* nomFichierDonnees = "donnees1.txt";
    char* nomFichierMaillage1 = "maillage1.txt";
    maillage(nomFichierDonnees,nomFichierMaillage1);
    // 2ème
    nomFichierDonnees = "donnees2.txt";
    char* nomFichierMaillage2 = "maillage2.txt";
    maillage(nomFichierDonnees,nomFichierMaillage2);
    // 3ème
    nomFichierDonnees = "donnees3.txt";
    char* nomFichierMaillage3 = "maillage3.txt";
    maillage(nomFichierDonnees,nomFichierMaillage3);

    /* Utilisation de la fonction lecfima + visualisation du maillage dans le terminal */
    int t,n,m,p,q;
    float **coord;
    int **ngnel, **nRefAr;
    // 1er
    lecfima(nomFichierMaillage1,&t,&n,&coord,&m,&ngnel,&p,&q,&nRefAr);
    printf("Maillage 1 :\n");
    visualisation(n,t,m,coord,ngnel,nRefAr);
    // 2ème
    lecfima(nomFichierMaillage2,&t,&n,&coord,&m,&ngnel,&p,&q,&nRefAr);
    printf("\nMaillage 2 :\n");
    visualisation(n,t,m,coord,ngnel,nRefAr);
    // 3ème
    lecfima(nomFichierMaillage3,&t,&n,&coord,&m,&ngnel,&p,&q,&nRefAr);
    printf("\nMaillage 3 :\n");
    visualisation(n,t,m,coord,ngnel,nRefAr);

    freematFLOAT(coord);
    freematINT(ngnel);
    freematINT(nRefAr);
    return 0;
}